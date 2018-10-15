#include <stdio.h>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "QueSeraMain.h"

void QueSeraMain::start()
{
    wifiEventGroup = xEventGroupCreate();
    retryCount = 0;

    tcpip_adapter_init();

    // Register WiFi event handler
    ESP_ERROR_CHECK(esp_event_loop_init(this->wifiConnectionEventHandler, nullptr));

    // Add WiFi configuration
    // So far I will use the hard-coded ones. It should read from NVS later.
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config =  {};
    memset(&wifi_config, 0, sizeof(wifi_config));
    std::strcpy((char*)wifi_config.sta.ssid, CONFIG_ESP_WIFI_SSID);
    std::strcpy((char*)wifi_config.sta.password, CONFIG_ESP_WIFI_PASSWORD);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(LOG_TAG, "WiFi PHY initialization finished.");
    ESP_LOGI(LOG_TAG, "Connecting to ap SSID: %s, Password:%s", CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD);
}

esp_err_t QueSeraMain::wifiConnectionEventHandler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
        case SYSTEM_EVENT_STA_START: {
            esp_wifi_connect();
            break;
        }

        case SYSTEM_EVENT_STA_GOT_IP: {
            ESP_LOGI(LOG_TAG, "We've got IP: %s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
            xEventGroupSetBits(wifiEventGroup, WIFI_CONNECTED_BIT);
            retryCount = 0;
            break;
        }

        case SYSTEM_EVENT_STA_DISCONNECTED: {
            if (retryCount < CONFIG_ESP_MAXIMUM_RETRY) {
                esp_wifi_connect();
                xEventGroupClearBits(wifiEventGroup, WIFI_CONNECTED_BIT);
                retryCount++;
                ESP_LOGI(LOG_TAG,"Retry %d time(s) to connect to the AP...", retryCount);
            }
            ESP_LOGI(LOG_TAG,"Failed to connect the AP!");
            break;
        }

        default:
            break;
    }

    return ESP_OK;
}

extern "C"
{
    void app_main(void);
}

void app_main()
{
    QueSeraMain queSeraMain;
    queSeraMain.start();
}

