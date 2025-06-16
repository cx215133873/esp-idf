#include "blufi_server.hpp"
#include "blufi_example.h"
#include <string.h>

BlufiServer &BlufiServer::instance() {
    static BlufiServer server;
    return server;
}

esp_err_t BlufiServer::init() {
    return esp_blufi_host_and_cb_init(&callbacks_);
}

void BlufiServer::deinit() {
    esp_blufi_profile_deinit();
    esp_blufi_host_deinit();
}

void BlufiServer::eventCallback(esp_blufi_cb_event_t event, esp_blufi_cb_param_t *param) {
    switch (event) {
        case ESP_BLUFI_EVENT_INIT_FINISH:
            BLUFI_INFO("BLUFI init finish");
            esp_blufi_adv_start();
            break;
        case ESP_BLUFI_EVENT_DEINIT_FINISH:
            BLUFI_INFO("BLUFI deinit finish");
            break;
        case ESP_BLUFI_EVENT_BLE_CONNECT:
            BLUFI_INFO("BLUFI ble connect");
            esp_blufi_adv_stop();
            blufi_security_init();
            break;
        case ESP_BLUFI_EVENT_BLE_DISCONNECT:
            BLUFI_INFO("BLUFI ble disconnect");
            blufi_security_deinit();
            esp_blufi_adv_start();
            break;
        default:
            break;
    }
}

esp_blufi_callbacks_t BlufiServer::callbacks_ = {
    .event_cb = BlufiServer::eventCallback,
    .negotiate_data_handler = blufi_dh_negotiate_data_handler,
    .encrypt_func = blufi_aes_encrypt,
    .decrypt_func = blufi_aes_decrypt,
    .checksum_func = blufi_crc_checksum,
};

