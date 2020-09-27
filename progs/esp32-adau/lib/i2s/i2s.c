#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"
#include "freertos/task.h"
#include <math.h>




#define TEST_SAMPLE_RATE     (44100)
#define TEST_WAVE_FREQ_HZ    (100)
#define PI              (3.14159265)
#define TEST_SAMPLE_PER_CYCLE (TEST_SAMPLE_RATE/TEST_WAVE_FREQ_HZ)

void meandr(void)
{
    static bool state = false;
    int bits = 16;
    int *samples_data = malloc(((bits+8)/16)*TEST_SAMPLE_PER_CYCLE * 4);
    uint16_t i, sample_val;
    size_t i2s_bytes_write = 0;
    sample_val = state ? 0xffff :0;
    for(i = 0; i < TEST_SAMPLE_PER_CYCLE; i++) {
            samples_data[i] = (sample_val<<16) + sample_val;
    }
    i2s_write(0, samples_data, TEST_SAMPLE_PER_CYCLE*4, &i2s_bytes_write, 100);
    free(samples_data);
    state = !state;
}


void pila(void)
{
    int bits = 16;
    int *samples_data = malloc(((bits+8)/16)*TEST_SAMPLE_PER_CYCLE * 4);
    unsigned int i, sample_val;
    size_t i2s_bytes_write = 0;
    sample_val = 0;        
    for(i = 0; i < TEST_SAMPLE_PER_CYCLE; i++) {
            samples_data[i] = (sample_val) ;
            sample_val += 0x200;
    }
    i2s_write(0, samples_data, ((bits+8)/16)*TEST_SAMPLE_PER_CYCLE*4, &i2s_bytes_write, 100);
    free(samples_data);
}


void i2sTestInternalDac(void) {
    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN,   
        .sample_rate = 44100,
        .bits_per_sample = 16,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .dma_buf_count = 6,
        .dma_buf_len = 60,
        .intr_alloc_flags = 0,                                                  //Default interrupt priority
        .tx_desc_auto_clear = true                                              //Auto clear tx descriptor on underflow
    };
    i2s_driver_install(0, &i2s_config, 0, NULL);
    i2s_set_pin(0, NULL);
    i2s_set_sample_rates(0, 22050);
    while (1) {
        pila();
        vTaskDelay(1000/portTICK_RATE_MS);
    }


}

void i2sInit(int bckPin, int lrckPin, int dataPin) {
    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
        .sample_rate = 44100,
        .bits_per_sample = 16,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .dma_buf_count = 6,
        .dma_buf_len = 60,
        .intr_alloc_flags = 0,                                                  //Default interrupt priority
        .tx_desc_auto_clear = true                                              //Auto clear tx descriptor on underflow
    };


    i2s_driver_install(0, &i2s_config, 0, NULL);
    i2s_pin_config_t pin_config = {
        .bck_io_num = bckPin,
        .ws_io_num = lrckPin,
        .data_out_num = dataPin,
        .data_in_num = -1                                                       //Not used
    };
    i2s_set_pin(0, &pin_config);
#ifdef UNIT_TEST
    i2s_set_clk(0, TEST_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);
#endif    
}

