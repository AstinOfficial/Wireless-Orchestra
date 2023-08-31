#include<driver/gpio.h>
#include <rom/gpio.h>
#include<freertos/FreeRTOS.h>
#include <freertos/task.h>


#define LED_PIN 13


void ledON() {
  printf("LED ON");
  gpio_set_level(LED_PIN,0);
}

void ledOFF() {
  printf("LED OFF");
  gpio_set_level(LED_PIN,1);
}


void led_blink(void *pvParameters)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);


    while(1){
        ledON();
        vTaskDelay(1000/portTICK_PERIOD_MS);

        ledOFF();
        vTaskDelay(1000/portTICK_PERIOD_MS);


        
    }



}


void app_main() {


xTaskCreate(&led_blink,"LED_BLINK",512,NULL,5,NULL);



}