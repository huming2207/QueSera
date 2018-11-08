#ifndef QUESERA_CALLOADER_H
#define QUESERA_CALLOADER_H

#include <string>
#include <esp_system.h>
#include <esp_http_client.h>

#define LOG_TAG "CalLoader"

extern const char google_root_cert_pem_start[] asm("_binary_google_root_cert_pem_start");
extern const char google_root_cert_pem_end[]   asm("_binary_google_root_cert_pem_end");

class CalLoader
{
    public:
        void parseEventFromUrl(const char *url);

    private:
        void replaceString(std::string &origString, const std::string &oldString, const std::string &newString);
        static esp_err_t httpEventHandler(esp_http_client_event_t *evt);
        void parseString(const char *buffer);
        time_t firstDtStart;
        time_t firstDtEnd;
        time_t secondDtStart;
        time_t secondDtEnd;
        std::string firstSummary;
        std::string secondSummary;
};

#endif //QUESERA_CALLOADER_H
