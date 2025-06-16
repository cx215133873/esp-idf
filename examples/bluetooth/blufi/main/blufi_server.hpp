#pragma once

extern "C" {
#include "esp_blufi_api.h"
}

class BlufiServer {
public:
    static BlufiServer &instance();
    esp_err_t init();
    void deinit();

private:
    BlufiServer() = default;
    static void eventCallback(esp_blufi_cb_event_t event, esp_blufi_cb_param_t *param);
    static esp_blufi_callbacks_t callbacks_;
};

