#include "blufi_server.hpp"
#include "blufi_example.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include <stdio.h>

extern "C" void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Wi-Fi initialization from original example
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ret = BlufiServer::instance().init();
    if (ret != ESP_OK) {
        BLUFI_ERROR("Blufi init failed: %s", esp_err_to_name(ret));
        return;
    }

    BLUFI_INFO("BLUFI VERSION %04x", esp_blufi_get_version());
}
