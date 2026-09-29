#include "TemperatureManager.h"

void TemperatureManager::updateLocal(const MeasurementBatch& batch)
{
    for (const auto& measurement : batch.measurements) {
        
        if ( measurement.sensorName == "inHeating") {
            temperatures.local.inHeating = measurement.value;
        }

        if ( measurement.sensorName == "outHeating") {
            temperatures.local.outHeating = measurement.value;
        }
        
        if ( measurement.sensorName == "inValve") {
            temperatures.local.inValve = measurement.value;
        }
        
        if ( measurement.sensorName == "waterHeater") {
            temperatures.local.waterHeater = measurement.value;
        }
    }
}

void TemperatureManager::updateRemote(const ServerResponse& response)
{
    temperatures.remote = response.remote;
    temperatures.target = response.target;
}

const Temperatures& TemperatureManager::getTemperatures() const
{
    return temperatures;
}


