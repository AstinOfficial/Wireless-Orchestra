#include <stdio.h> //for basic printf commands
#include <string.h> //for handling strings
#include "freertos/FreeRTOS.h" //for delay,mutexs,semphrs rtos operations
#include "esp_system.h" //esp_init funtions esp_err_t 
#include "esp_wifi.h" //esp_wifi_init functions and wifi operations
#include "esp_log.h" //for showing logs
#include "esp_event.h" //for wifi event
#include "nvs_flash.h" //non volatile storage


#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"


// Server settings
#define SERVER_IP "192.168.141.198 "
#define SERVER_PORT 8080


void tcp_client_task(void *pvParameters) {
    while (1) {
        struct sockaddr_in dest_addr;
        int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        if (sock < 0) {
            printf("\nUnable to create socket\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }

        dest_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(SERVER_PORT);

        printf("\nConnecting to %s:%d\n", SERVER_IP, SERVER_PORT);
        if (connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != 0) {
            printf("\nConnection failed\n");
            close(sock);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }


        //const char *message = "Hello from astin the boss!";
        // printf("\nSENDING THE MESSAGE :%s\n",message);
        // write(sock, message, strlen(message));

           const char *message = "60, 62, 64";
            printf("\nSENDING THE MESSAGE :%s\n",message);
            printf("NOTE SEND");
            write(sock, message, strlen(message));

       
        close(sock);
        printf("\nSENDED\n");

        vTaskDelay(5000 / portTICK_PERIOD_MS); // Send message every 5 seconds
    }
}





const char *ssid = "motorola";
const char *pass = "astinbiju44";
int retry_num=0;




static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data){
if(event_id == WIFI_EVENT_STA_START)
{
  printf("WIFI CONNECTING....\n");
}
else if (event_id == WIFI_EVENT_STA_CONNECTED)
{
  printf("WiFi CONNECTED\n");
  xTaskCreate(tcp_client_task, "tcp_client_task", 4096, NULL, 5, NULL);
}
else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
{
  printf("WiFi lost connection\n");
  if(retry_num<5){esp_wifi_connect();retry_num++;printf("Retrying to Connect...\n");}
}
else if (event_id == IP_EVENT_STA_GOT_IP)
{
  printf("Wifi got IP...\n\n");
}
}

void wifi_connection()
{
 
    esp_netif_init();
    esp_event_loop_create_default();     // event loop                   
    esp_netif_create_default_wifi_sta(); // WiFi station                      
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation); //     
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = "",
            .password = "",
            
           }
    
        };
    strcpy((char*)wifi_configuration.sta.ssid, ssid);
    strcpy((char*)wifi_configuration.sta.password, pass);    
    //esp_log_write(ESP_LOG_INFO, "Kconfig", "SSID=%s, PASS=%s", ssid, pass);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    // 3 - Wi-Fi Start Phase
    esp_wifi_start();
    esp_wifi_set_mode(WIFI_MODE_STA);
    // 4- Wi-Fi Connect Phase
    esp_wifi_connect();
    printf( "wifi_init_softap finished. SSID:%s  password:%s",ssid,pass);
    
}



void app_main(void)
{
nvs_flash_init();
wifi_connection();
    
}