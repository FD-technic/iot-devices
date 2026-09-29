#ifndef TEMPERATURE_MANAGER_H
#define TEMPERATURE_MANAGER_H

#include <dto/MeasurementBatch.h>
#include <dto/ServerResponse.h>

struct LocalTemperatures {
    float inHeating = 50.0;
    float outHeating = 40.0;
    float inValve = 60.0;
    float waterHeater = 40.0;
};

struct Temperatures {
    LocalTemperatures local;
    RemoteTemperatures remote;
    TargetTemperatures target;
};

class TemperatureManager
{
public:
    void updateLocal(const MeasurementBatch& batch);
    void updateRemote(const ServerResponse& response);

    const Temperatures& getTemperatures() const;

private:
    Temperatures temperatures{};
};

#endif