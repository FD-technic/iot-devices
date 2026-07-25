#include "ApiClient.h"

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "dto/apiResponse.h"

ApiResponse apiResponse = {0, false};

ApiResponse ApiClient::sendMessage(const IrrigationPayload& payload, DeviceType type) {
    JsonDocument doc;
    
    doc["deviceId"] = Config::Endpoint::DEVICE;
    doc["deviceType"] = toString(type);
    doc["firmware"] = Config::Device::FIRMWARE;

    JsonObject jsonPayload = doc["payload"].to<JsonObject>();

    jsonPayload["mainTemperature"] = payload.mainTemperature;
    jsonPayload["inputTemperature"] = payload.inputTemperature;
    jsonPayload["outputTemperature"] = payload.outputTemperature;

    String json;
    serializeJson(doc, json);
    
    HTTPClient http;

    http.begin(String(Config::SERVER_URL) + String(Config::Endpoint::DEVICE));
    http.addHeader("Content-Type", "application/json");

    int code = http.POST(json);

    Serial.print("HTTP code: ");
    Serial.println(code);

    if (code > 0) {
        String response = http.getString();

        Serial.println(response);

        JsonDocument responseDoc;

        DeserializationError error = deserializeJson(responseDoc, response);

        if (error) {
            Serial.print("JSON error: ");
            Serial.println(error.c_str());
            return apiResponse;
        }
        
        JsonArray commands = responseDoc["commands"];
        JsonObject command = commands[0];


        const char* type = command["type"];
        const char* name = command["name"];
        bool led = command["enabled"];

        Serial.print("TYPE = ");
        Serial.println(type);
        Serial.print("NAME = ");
        Serial.println(name);
        Serial.print("LED = ");
        Serial.println(led);

        apiResponse = { code, command["enabled"] };
    
    }

    http.end();

    return apiResponse; 
}

ApiResponse ApiClient::sendTemperature(const TemperaturePayload& payload) {
    JsonDocument doc;
    
    doc["value"] = payload.value;
    doc["deviceName"] = payload.deviceName;
    
    String json;
    serializeJson(doc, json);
    
    HTTPClient http;

    http.begin(String(Config::SERVER_URL) + String(Config::Endpoint::MEASURE));
    http.addHeader("Content-Type", "application/json");

    Serial.println(json);
    int code = http.POST(json);

    Serial.print("HTTP code: ");
    Serial.println(code);

    if (code > 0) {
        String response = http.getString();

        Serial.println(response);

        JsonDocument responseDoc;

        DeserializationError error = deserializeJson(responseDoc, response);

        if (error) {
            Serial.print("JSON error: ");
            Serial.println(error.c_str());
            return apiResponse;
        }
        
        JsonArray commands = responseDoc["commands"];

        if (!commands.isNull() && commands.size() > 0) {
            JsonObject command = commands[0];

            const char* type = command["type"];
            const char* name = command["name"];
            bool led = command["enabled"];

            Serial.print("TYPE = ");
            Serial.println(type);
            Serial.print("NAME = ");
            Serial.println(name);
            Serial.print("LED = ");
            Serial.println(led);

            apiResponse = { code, command["enabled"] };
        } 
    }

    http.end();

    return apiResponse; 
}

ApiResponse ApiClient::createDevice(const String type) {
    JsonDocument doc;
    
    doc["deviceName"] = "Esp-32";
    doc["deviceDescription"] = "ESP with Dallas";
    doc["deviceFirmware"] = "v-0.0.1";
    doc["deviceType"] = type;

    JsonObject jsonPayload = doc["payload"].to<JsonObject>();

    String json;
    serializeJson(doc, json);
    
    HTTPClient http;

    http.begin(String(Config::SERVER_URL) + String(Config::Endpoint::DEVICE));
    http.addHeader("Content-Type", "application/json");
    Serial.print("JSON: ");
    Serial.println(json);
    int code = http.POST(json);

    Serial.print("HTTP code: ");
    Serial.println(code);

}