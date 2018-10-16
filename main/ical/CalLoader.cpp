#include <sstream>
#include <esp_log.h>
#include "CalLoader.h"



void CalLoader::replaceString(std::string &origString, const std::string &oldString, const std::string &newString)
{
    std::string::size_type pos = 0u;
    while((pos = origString.find(oldString, pos)) != std::string::npos) {
        origString.replace(pos, oldString.length(), newString);
        pos += newString.length();
    }
}

void CalLoader::parseEventFromUrl(const char *url)
{
    char *buffer = (char *)malloc(CONFIG_HTTP_RECV_BUFFER_SIZE + 1);
    if (buffer == nullptr) {
        ESP_LOGE(LOG_TAG, "Cannot malloc http receive buffer");
        return;
    }

    // Set the configuration with Google's root certificate
    esp_http_client_config_t config = {};
    config.url = url;
    config.event_handler = httpEventHandler;
    config.cert_pem = google_root_cert_pem_start;

    // Initialize and perform the request
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err;
    if ((err = esp_http_client_open(client, 0)) != ESP_OK) {
        ESP_LOGE(LOG_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        free(buffer);
        return;
    }

    // There is no content length in many major calendar service provider (e.g. Google Calendar and Allocate+)
    // so I'm not gonna use the way that the SDK example is using.
    int readLength = 0;
    while(readLength >= 0) {
        readLength = esp_http_client_read(client, buffer, CONFIG_HTTP_RECV_BUFFER_SIZE);
        ESP_LOGD(LOG_TAG, "Got data, length is %d bytes", readLength);
        parseString(buffer);
    }

    ESP_LOGI(LOG_TAG, "HTTP Stream reader Status = %d, content_length = %d",
             esp_http_client_get_status_code(client),
             esp_http_client_get_content_length(client));
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    free(buffer);
}

esp_err_t CalLoader::httpEventHandler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR: {
            ESP_LOGD(LOG_TAG, "Got error!");
            break;
        }

        case HTTP_EVENT_ON_CONNECTED: {
            ESP_LOGD(LOG_TAG, "Connection established!");
            break;
        }

        case HTTP_EVENT_HEADER_SENT: {
            ESP_LOGD(LOG_TAG, "Request headers has been sent!");
            break;
        }

        case HTTP_EVENT_ON_HEADER: {
            ESP_LOGD(LOG_TAG, "Got response header, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        }

        case HTTP_EVENT_ON_DATA: {
            ESP_LOGD(LOG_TAG, "Got response data section, length is %d bytes", evt->data_len);
            break;
        }

        case HTTP_EVENT_ON_FINISH: {
            ESP_LOGD(LOG_TAG, "Data transfer finished!");
            break;
        }

        case HTTP_EVENT_DISCONNECTED: {
            ESP_LOGD(LOG_TAG, "Server disconnected!");
            break;
        }
    }

    return ESP_OK;
}

void CalLoader::parseString(const char *buffer)
{
    std::string strBuffer(buffer);

    // Remove the Google-style string indent
    replaceString(strBuffer, "\n ", "\n");

    // Create string stream
    std::istringstream strStream(strBuffer);
    std::string currentLine;
    while(std::getline(strStream, currentLine)) {

    }
}
