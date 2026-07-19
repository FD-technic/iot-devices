#include <Arduino.h>
#include<WiFi.h>
#include <HTTPClient.h>
#include "Config.h"

const int freq = 30;
const int sleeping = 10*1000;

double temperature = -200;

void connectWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);

    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Connected!");
    Serial.println("IP: ");
    Serial.println(WiFi.localIP());
}

void sendMessage() {
    HTTPClient http;

    http.begin(String(Config::SERVER_URL) + String(Config::Endpoint::DEVICE));
    http.addHeader("Content-Type", "application/json");

    String json = R"({
        "deviceId":"esp32-01",
        "deviceType":"IRRIGATION",
        "firmware":"v0.1",
        "payload":{
            "mainTemperature":26,
            "inputTemperature":35,
            "outputTemperature":12
        }
    })";

    int code = http.POST(json);

    Serial.print("HTTP code: ");
    Serial.println(code);

    if (code > 0) {
        String response = http.getString();

        Serial.println(response);
    }

    http.end();
}

void setup() {
    Serial.begin(115200);
    connectWiFi();
    pinMode(2, OUTPUT);
}

void readSensor() {
  temperature = 17;
}

void blink() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(2, HIGH);
    delay(freq);
    digitalWrite(2, LOW);
    delay(freq * 2);
  } 
}

void loop() {
    sendMessage();

    readSensor();
    Serial.println(temperature);
  
    blink();

    delay(sleeping);
}


