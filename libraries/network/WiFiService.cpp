#include "WiFiService.h"

#include <Arduino.h>
#include <WiFi.h>

WiFiService::WiFiService(const char* ssid, const char* password)
: ssid(ssid),
  password(password)
{

}

void WiFiService::connect()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (!isConnected()) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

bool WiFiService::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
