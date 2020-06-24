#include <esp_log.h>
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include <esp_task_wdt.h>
#include "net.h"
#include "adau17x.h"

#define  TCP_PORT 8086
#define HEADER_SIZE 8
#define COMMAND_READ 0x0a
#define COMMAND_WRITE 0x0b



static const char *TAG="tcp_server";
static const char *taskName="tcp_server";
static TaskHandle_t taskHandle = NULL;


static esp_err_t execAdauWrite(uint16_t address,uint16_t length,int socket){
    uint8_t *buf = malloc(length);
//    ESP_LOGI(TAG,"Write. ddress %02X length %d",address,length);
    if(!buf) {
        ESP_LOGE(TAG,"Malloc error");
        return ESP_FAIL;
    }
    int bytesReceived = recv(socket, buf, length, 0);
    if (bytesReceived < 0) {
        ESP_LOGE(TAG, "Error occurred during receiving data: errno %d", errno);
        free(buf);
        return ESP_FAIL;
    } else if (bytesReceived == 0) {
        ESP_LOGW(TAG, "Client task: Connection closed");
        free(buf);
        return ESP_FAIL;
    } else if(bytesReceived != length) {
        ESP_LOGW(TAG, "Not enough data received (%d bytes, expected %d)",bytesReceived, length);
        free(buf);
        return ESP_FAIL;
    }
    esp_err_t result = adauWrite(address, buf, length);
//    esp_err_t result = ESP_OK;
    free(buf);
    return result;
}

esp_err_t execAdauRead(uint16_t address,uint16_t length,int socket){
  uint8_t *buf;
  bool success = true;
  buf = (uint8_t *)malloc(length+4);
  buf[0] = COMMAND_WRITE;
  buf[1] = (0x4 + length) >> 8;
  buf[2] = (0x4 + length) & 0xff;
  if(adauRead(address, buf + 4,  length) == ESP_OK)  
    buf[3] =  0;// код возврата
  else {
    buf[3] = 1;  
    success = false;
  }  
  size_t sent = send(socket, buf, 4 + length, 0);
  free(buf);
  if(sent != (4 + length)) {
      success = false;
      ESP_LOGE(TAG,"Error sending answer on Adau read command");
  }
  return success ?ESP_OK : ESP_FAIL;
}


static bool handleConnection(int socket){
    uint16_t len,addr;
    uint8_t header[8],command;
    int bytesReceived;
    while(1){
        bytesReceived = recv(socket, header, HEADER_SIZE, MSG_PEEK);
//        ESP_LOGI(TAG,"Bytes available %d",bytesReceived);
        if (bytesReceived < 0) {
            ESP_LOGE(TAG, "Client task: Error occurred during receiving: errno %d", errno);
            return false;
        } else if (bytesReceived == 0) {
            ESP_LOGW(TAG, "Client task: Connection closed");
            return false;
        } else { // Получены данные
//            ESP_LOGI(TAG,"Client task: Got packet size %d",bytesReceived); 
            if(bytesReceived < HEADER_SIZE)  continue;
            recv(socket, header, HEADER_SIZE, 0);
        	command = header[0];
        	len = (header[4] << 8) | header[5];
	        addr = (header[6] << 8) | header[7];
//            ESP_LOGI(TAG,"Request: cmd:%02x addr:%04X length: %04X",command,addr,len);
            if(command == COMMAND_READ) { // чтение из ADAU
                execAdauRead(addr,len,socket);
            } else execAdauWrite(addr,len,socket); 
            return true;
        }
    }
}

static void closeConnection(int socket) {
    shutdown(socket, 0);
    close(socket);
}
static void tcpServerTask(void *pvParameters)
{
    char addr_str[128];
    int addr_family;
    int ip_protocol;
    int sock = -1;

    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(TCP_PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);
    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (listen_sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }
    ESP_LOGI(TAG, "Socket created");

    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        goto CLEAN_UP;
    }
    ESP_LOGI(TAG, "Socket bound, port %d", TCP_PORT);

    err = listen(listen_sock, 1);
    if (err != 0) {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        goto CLEAN_UP;
    }

    while (1) {

        ESP_LOGI(TAG, "Socket listening");
        if(!wifiConnected()) goto CLEAN_UP;
        struct sockaddr_in6 source_addr; // Large enough for both IPv4 or IPv6
        uint addr_len = sizeof(source_addr);
        sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        if (sock  < 0) {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        // Convert ip address to string
        if (source_addr.sin6_family == PF_INET) {
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);
        } else if (source_addr.sin6_family == PF_INET6) {
            inet6_ntoa_r(source_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
        }
        ESP_LOGI(TAG, "Connection accepted ip address: %s", addr_str);
        while(handleConnection(sock)) {
            esp_task_wdt_reset();
        }
        closeConnection(sock);
        sock = -1;
    }

CLEAN_UP:
    if(sock >=0)
        closeConnection(sock);
    ESP_LOGI(TAG,"Server stopped");
    close(listen_sock);
    vTaskDelete(NULL);
    taskHandle = NULL;
}

static bool taskStarted(){
    if(taskHandle == NULL) return false;
    return true;
}

esp_err_t tcpServerStart(void){
    if(taskStarted()) {
        ESP_LOGE(TAG,"Start failed: task already started");    
        return ESP_FAIL;
    }    
    if(xTaskCreate(tcpServerTask, taskName, 4096, NULL, 5, &taskHandle ) != pdPASS) {
        ESP_LOGE(TAG,"Start failed: error creating task ");    
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t tcpServerStop(void){
    if(!taskStarted()) {
        ESP_LOGE(TAG,"Stop failed: task not started");    
        return ESP_FAIL;
    } 
//    closeConnection();   
    vTaskDelete(taskHandle);
    taskHandle = NULL;
    return ESP_OK;
}
