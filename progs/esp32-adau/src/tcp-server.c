#include <esp_log.h>
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "net.h"
#include "adau17x.h"

#define  TCP_PORT 8086
#define HEADER_SIZE 8
#define COMMAND_READ 0x0a
#define COMMAND_WRITE 0x0b



static const char *TAG="tcp_server";
static const char *taskName="tcp_server";
static TaskHandle_t taskHandle = NULL,clientTaskHandle=NULL;
static int clientSocket = 0;

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

void execAdauWrite(int address, uint8_t *buf, int length) {
    adauWrite(address, buf, length);
}


static void clientTask(void *pvParameters){
    int *saddr = (int *)pvParameters;
    int socket = *saddr;
    uint16_t len,addr;
    uint8_t header[8],command;
    int bytesReceived;
    uint8_t *buf;
    while(1){
        bytesReceived = recv(socket, header, HEADER_SIZE, MSG_PEEK);
//        ESP_LOGI(TAG,"Bytes available %d",bytesReceived);
        if (bytesReceived < 0) {
            ESP_LOGE(TAG, "Client task: Error occurred during receiving: errno %d", errno);
            break;
        } else if (bytesReceived == 0) {
            ESP_LOGW(TAG, "Client task: Connection closed");
            break;
        } else { // Получены данные
//            ESP_LOGI(TAG,"Client task: Got packet size %d",bytesReceived); 
            if(bytesReceived < HEADER_SIZE)  continue;
        	command = header[0];
        	len = (header[4] << 8) | header[5];
	        addr = (header[6] << 8) | header[7];
            ESP_LOGI(TAG,"Request: cmd:%02x addr:%04X length: %04X",command,addr,len);
            if(command == COMMAND_READ) { // чтение из ADAU
                recv(socket, header, HEADER_SIZE, 0);
                execAdauRead(addr,len,socket);
                continue;
            }  
            buf = (uint8_t *)malloc(len+HEADER_SIZE);
            bytesReceived = recv(socket, buf, len + HEADER_SIZE, MSG_PEEK);
            if(bytesReceived < (len+8)) {
                free(buf);
                continue;
            }    
            recv(socket, header, HEADER_SIZE, 0);
            recv(socket, buf, len, 0);
            execAdauWrite(addr,buf,len);
            free(buf);
        }
    }
    ESP_LOGI(TAG,"Connection closed");
    shutdown(socket, 0);
    close(socket);
    clientSocket = 0;
    vTaskDelete(NULL);
}

static void closeConnection(void) {
    if(!clientTaskHandle) return;
    if(clientSocket == 0) return;
    ESP_LOGI(TAG,"Close connection");
    vTaskDelete(clientTaskHandle);
    shutdown(clientSocket, 0);
    close(clientSocket);
    clientSocket = 0;
}
static void tcpServerTask(void *pvParameters)
{
    char addr_str[128];
    int addr_family;
    int ip_protocol;


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
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
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
        closeConnection();
        clientSocket = sock;
        xTaskCreate(clientTask,"client_task", 2048,&clientSocket,2,&clientTaskHandle);
    }

CLEAN_UP:
    if(clientSocket >=0) closeConnection();
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
    closeConnection();   
    vTaskDelete(taskHandle);
    return ESP_OK;
}
