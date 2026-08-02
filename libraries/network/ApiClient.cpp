#include "ApiClient.h"

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "dto/apiResponse.h"
#include "dto/Device.h"

ApiClient::ApiClient(const char* serverUrl)
    : serverUrl(serverUrl)
{
}

ApiResponse ApiClient::createDevice(const Device& device)
{
    JsonDocument doc;

    doc["deviceName"] = device.name;
    doc["deviceDescription"] = device.description;
    doc["deviceFirmware"] = device.firmware;
    doc["deviceType"] = toString(device.type);

    return post(DEVICE_ENDPOINT, doc);
}

ApiResponse ApiClient::sendMeasurements(const MeasurementBatch &batch)
{
    JsonDocument doc;

    doc["deviceName"] = batch.deviceName;
    JsonArray measurements = doc.createNestedArray("measurements");

    for (const Measurement &measurement : batch.measurements)
    {
        JsonObject jsonMeasurement = measurements.createNestedObject();

        jsonMeasurement["sensorName"] = measurement.sensorName;
        jsonMeasurement["type"] = toString(measurement.type);
        jsonMeasurement["value"] = measurement.value;
    }

    #ifdef DEBUG
        for (const Measurement &measurement : batch.measurements)
    {
        Serial.print(measurement.sensorName);
        Serial.print(" | ");

        Serial.print(static_cast<int>(measurement.type));
        Serial.print(" | ");

        Serial.print(toString(measurement.type));
        Serial.print(" | ");

        Serial.println(measurement.value);
    }
    #endif
    
    return post(MEASUREMENT_ENDPOINT, doc);
}

ApiResponse ApiClient::parseResponse(
    int httpCode,
    const String& response)
{
    JsonDocument doc;

    if (deserializeJson(doc, response))
    {
        return {httpCode, false};
    }

    JsonArray commands = doc["commands"];

    if (commands.isNull() || commands.size() == 0)
    {
        return {httpCode, false};
    }

    JsonObject command = commands[0];

    return {
        httpCode,
        command["enabled"] | false
    };
}

ApiResponse ApiClient::post(
    const char* endPoint,
    const JsonDocument& doc)
{
    HTTPClient http;

    String json;
    serializeJson(doc, json);

    http.begin(String(serverUrl) + endPoint);
    http.addHeader("Content-Type", "application/json");

    int code = http.POST(json);

    String response = http.getString();

#ifdef DEBUG
    Serial.println("===== HTTP =====");
    Serial.print("URL: ");
    Serial.println(String(serverUrl) + endPoint);

    Serial.println("JSON:");
    Serial.println(json);

    Serial.print("HTTP: ");
    Serial.println(code);

    Serial.println("Response:");
    Serial.println(response);
    Serial.println("================");
#endif

    http.end();

    if (code <= 0)
    {
        return {code, false};
    }

    return parseResponse(code, response);
}

