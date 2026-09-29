#include "ApiClient.h"

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

void ApiClient::sendPeripheralStatus(const PeripheralStatus& status)
{
    JsonDocument doc;

    doc["deviceName"] = status.deviceName;
    doc["heatingMode"] = heatingModeToString(status.heatingMode);
    doc["valveDirection"] = valveDirectionToString(status.valveDirection);
    doc["heatingPump"] = status.heatingPump;
    doc["waterHeaterPump"] = status.waterHeaterPump;

    post((String(DEVICE_ENDPOINT) + "/status").c_str(), doc);
}

ApiResponse ApiClient::parseResponse(
    int httpCode,
    const String& response)
{
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, response);

    if (error)
    {
        return {
            httpCode,
            false,
            {}
        };
    }

    ApiResponse result;

    result.httpCode = httpCode;
    
    const char* heatingMode = doc["heatingMode"] | "OFF";

    if (strcmp(heatingMode, "DAY") == 0)
    {
        result.data.heatingMode = HeatingMode::DAY;
    }
    else if (strcmp(heatingMode, "NIGHT") == 0)
    {
        result.data.heatingMode = HeatingMode::NIGHT;
    }
    else if (strcmp(heatingMode, "MANUAL") == 0)
    {
        result.data.heatingMode = HeatingMode::MANUAL;
    }
    else
    {
        result.data.heatingMode = HeatingMode::OFF;
    }

    // REMOTE
    result.data.remote.outdoor =
        doc["temperatures"]["outdoor"] | 15.0;

    result.data.remote.indoor =
        doc["temperatures"]["indoor"] | 21.0;

    // TARGETS
    result.data.target.room =
        doc["targets"]["room"] | 21.0;

    result.data.target.heatingHysteresis =
        doc["targets"]["heatingHysteresis"] | 5.0;

    result.data.target.waterHeatingHysteresis =
        doc["targets"]["waterHeatingHysteresis"] | 3.0;

    result.data.target.waterHeater =
        doc["targets"]["waterHeater"] | 60.0;

    // MANUAL
    result.data.manual.heatingPump =
        doc["manual"]["heatingPump"] | false;

    result.data.manual.waterHeaterPump =
        doc["manual"]["waterHeaterPump"] | false;

    const char* direction = doc["manual"]["valveDirection"] | "STOP";

    if (strcmp(direction, "UP") == 0)
    {
        result.data.manual.valveDirection = ValveDirection::UP;
    }
    else if (strcmp(direction, "DOWN") == 0)
    {
        result.data.manual.valveDirection = ValveDirection::DOWN;
    }
    else
    {
        result.data.manual.valveDirection = ValveDirection::STOP;
    }    

    return result;
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
        return {
            code,
            false,
            {}
        };
    }

    return parseResponse(code, response);
}

