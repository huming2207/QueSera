#ifndef QUESERA_QUESERAMAIN_H
#define QUESERA_QUESERAMAIN_H

#include "freertos/event_groups.h"
#include "esp_event_loop.h"

#define LOG_TAG "QueSeraMain"

// Global variables for WiFi connections
static EventGroupHandle_t wifiEventGroup;
static const int WIFI_CONNECTED_BIT = BIT0;
static int retryCount;

class QueSeraMain
{
    public:
        void start();

    private:
        static esp_err_t wifiConnectionEventHandler(void* ctx, system_event_t* event);
};


#endif //QUESERA_QUESERAMAIN_H
