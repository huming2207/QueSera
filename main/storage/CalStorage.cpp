#include "CalStorage.h"

#include <esp_err.h>
#include <esp_log.h>
#include <esp_spiffs.h>
#include <sys/unistd.h>

CalStorage::CalStorage()
{
    ESP_LOGI(LOG_TAG, "Mounting SPIFFS...");
    esp_vfs_spiffs_conf_t fsConf = {
            .base_path = "/spiffs",
            .partition_label = nullptr,
            .max_files = 3,
            .format_if_mount_failed = true
    };

    esp_err_t ret = esp_vfs_spiffs_register(&fsConf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(LOG_TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(LOG_TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(LOG_TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }

        // Crash the device when it fails to mount SPIFFS
        abort();
    }

    // If the cache file exists, remove the file
    if(access(CONFIG_ICAL_CACHE_PATH, F_OK) != -1) {
        ESP_LOGI(LOG_TAG, "Cache haven't been removed since last boot, now perform unlink to remove it...");
        unlink(CONFIG_ICAL_CACHE_PATH);
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(LOG_TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(LOG_TAG, "Partition size: total: %d, used: %d", total, used);
    }
}

CalStorage::~CalStorage()
{
    ESP_LOGI(LOG_TAG, "Un-mounting SPIFFS...");

    // If the cache file exists, remove the file
    if(access(CONFIG_ICAL_CACHE_PATH, F_OK) != -1) {
        ESP_LOGI(LOG_TAG, "Cache found, now perform unlink...");
        unlink(CONFIG_ICAL_CACHE_PATH);
    }

    // Un-mount SPIFFS
    ESP_ERROR_CHECK(esp_vfs_spiffs_unregister(nullptr));
}

bool CalStorage::appendCalBuffer(const char *buffer)
{
    return false;
}
