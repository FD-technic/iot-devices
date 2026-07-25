#include "WifiService.h"

#include <Arduino.h>
#include <WiFi.h>
#include "Config.h"

void WifiService::connect() {
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);

    while (isConnected()) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

bool WifiService::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
