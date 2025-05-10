#ifndef SENSORJSONPARSER_H
#define SENSORJSONPARSER_H

#include "Sensors/AbstractSensor.h"

#include <QJsonObject>

namespace Sensors {
namespace Json {

class SensorJsonParser
{

private:
    //Sensore costruito
    Sensors::AbstractSensor* mainSensor;

public:
    SensorJsonParser(QJsonObject jsonSensorData);

    Sensors::AbstractSensor* getMainSensor() const;

    //Costruisco sensore in base al tipo
    void buildTemp(QJsonObject jsonSensorData);
    void buildHumid(QJsonObject jsonSensorData);
    void buildMagnet(QJsonObject jsonSensorData);

};

}
}

#endif // SENSORJSONPARSER_H
