#include "SensorJsonParser.h"

#include "Sensors/TempSensor.h"
#include "Sensors/HumidSensor.h"
#include "Sensors/MagnetSensor.h"

#include <QJsonArray>
#include <QString>

namespace Sensors {
namespace Json {

    SensorJsonParser::SensorJsonParser(QJsonObject jsonSensorData)
    : mainSensor(nullptr)
    {
        QString sensorType = jsonSensorData.value("Type").toString();
        if(sensorType == "Temp")
            buildTemp(jsonSensorData);
        else if(sensorType == "Humid")
            buildHumid(jsonSensorData);
        else if(sensorType == "Magnet")
            buildMagnet(jsonSensorData);
    }

    Sensors::AbstractSensor *SensorJsonParser::getMainSensor() const
    {
        return mainSensor;
    }

    void SensorJsonParser::buildTemp(QJsonObject jsonSensorData)
    {
        int id = jsonSensorData.value("Id").toInt();
        QString name = jsonSensorData.value("Name").toString();
        QString description = jsonSensorData.value("Description").toString();
        mainSensor = new Sensors::TempSensor(id, name.toStdString(), description.toStdString());

        QJsonArray jsonTempVal = jsonSensorData.value("TempValues").toArray();
        std::vector<double> tempVal;
        for(const QJsonValue &val : jsonTempVal) {
            tempVal.push_back(val.toDouble());
        }
        static_cast<Sensors::TempSensor*>(mainSensor)->setTemperatureValues(tempVal);

        double maxV = jsonSensorData.value("MaxVal").toDouble();
        double minV = jsonSensorData.value("MinVal").toDouble();
        static_cast<Sensors::TempSensor*>(mainSensor)->setMaxVal(maxV);
        static_cast<Sensors::TempSensor*>(mainSensor)->setMinVal(minV);

    }

    void SensorJsonParser::buildHumid(QJsonObject jsonSensorData)
    {
        int id = jsonSensorData.value("Id").toInt();
        QString name = jsonSensorData.value("Name").toString();
        QString description = jsonSensorData.value("Description").toString();
        mainSensor = new Sensors::HumidSensor(id, name.toStdString(), description.toStdString());

        QJsonArray jsonHumidVal = jsonSensorData.value("HumidValues").toArray();
        std::vector<double> humidVal;
        for(const QJsonValue &val : jsonHumidVal) {
            humidVal.push_back(val.toDouble());
        }
        static_cast<Sensors::HumidSensor*>(mainSensor)->setHumidityValues(humidVal);

        double avgV = jsonSensorData.value("AvgVal").toDouble();
        static_cast<Sensors::HumidSensor*>(mainSensor)->setAvgVal(avgV);

    }

    void SensorJsonParser::buildMagnet(QJsonObject jsonSensorData)
    {
        int id = jsonSensorData.value("Id").toInt();
        QString name = jsonSensorData.value("Name").toString();
        QString description = jsonSensorData.value("Description").toString();
        mainSensor = new Sensors::MagnetSensor(id, name.toStdString(), description.toStdString());

        QJsonArray jsonMagnetVal = jsonSensorData.value("MagnetValues").toArray();
        std::vector<Sensors::MagneticData> magnetVal;
        for(const QJsonValue &valRef : jsonMagnetVal) {
            QJsonObject val = valRef.toObject();
            double x = val.value("X").toDouble();
            double y = val.value("Y").toDouble();
            double z = val.value("Z").toDouble();

            magnetVal.push_back(MagneticData(x, y, z));
        }
        static_cast<Sensors::MagnetSensor*>(mainSensor)->setMagneticValues(magnetVal);

        QJsonObject lastMagnDataVar = jsonSensorData.value("LastMagneticDataVariation").toObject();
        double lastMagnDataVarX = lastMagnDataVar.value("X").toDouble();
        double lastMagnDataVarY = lastMagnDataVar.value("Y").toDouble();
        double lastMagnDataVarZ = lastMagnDataVar.value("Z").toDouble();
        static_cast<Sensors::MagnetSensor*>(mainSensor)->setLastMagneticDataVariation(MagneticData(lastMagnDataVarX, lastMagnDataVarY, lastMagnDataVarZ));

        QJsonObject magnDataVar = jsonSensorData.value("MagneticDataVariance").toObject();
        double magnDataVarX = magnDataVar.value("X").toDouble();
        double magnDataVarY = magnDataVar.value("Y").toDouble();
        double magnDataVarZ = magnDataVar.value("Z").toDouble();
        static_cast<Sensors::MagnetSensor*>(mainSensor)->setMagneticDataVariance(MagneticData(magnDataVarX, magnDataVarY, magnDataVarZ));
    }

}
}
