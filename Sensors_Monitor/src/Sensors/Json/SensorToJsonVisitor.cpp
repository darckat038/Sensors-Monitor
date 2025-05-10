#include <QJsonArray>

#include "SensorToJsonVisitor.h"
#include "Sensors/MagneticData.h"

namespace Sensors {
namespace Json {



    SensorToJsonVisitor::SensorToJsonVisitor()
    : infoObject(nullptr)
    {

    }

    QJsonObject *SensorToJsonVisitor::getInfoObject() const
    {
        return infoObject;
    }

    void SensorToJsonVisitor::visit(const Sensors::TempSensor &tempSensor)
    {
        infoObject = new QJsonObject();

        //Tipo sensore
        (*infoObject)["Type"] = "Temp";

        //Array di valori
        QJsonArray dataValues;
        for(const double &val : *(tempSensor.getVals())) {
            dataValues.push_back(val);
        }

        //Unione finale dati
        (*infoObject)["TempValues"] = dataValues;
        //Campi dati specifici
        (*infoObject)["MaxVal"] = tempSensor.getMaxVal();
        (*infoObject)["MinVal"] = tempSensor.getMinVal();
    }

    void SensorToJsonVisitor::visit(const Sensors::HumidSensor &humidSensor)
    {
        infoObject = new QJsonObject();

        //Tipo sensore
        (*infoObject)["Type"] = "Humid";

        //Array di valori
        QJsonArray dataValues;
        for(const double &val : *(humidSensor.getVals())) {
            dataValues.push_back(val);
        }

        //Unione finale dati
        (*infoObject)["HumidValues"] = dataValues;
        //Campi dati specifici
        (*infoObject)["AvgVal"] = humidSensor.getAvg();
    }

    void SensorToJsonVisitor::visit(const Sensors::MagnetSensor &magnetSensor)
    {
        infoObject = new QJsonObject();

        //Tipo sensore
        (*infoObject)["Type"] = "Magnet";

        //Array di valori
        QJsonArray dataValues;
        for(const Sensors::MagneticData &val : *(magnetSensor.getMagneticValues())) {
            QJsonObject dataObj;
            dataObj["X"] = val.getXval();
            dataObj["Y"] = val.getYval();
            dataObj["Z"] = val.getZval();
            dataValues.push_back(dataObj);
        }

        //Unione finale dati
        (*infoObject)["MagnetValues"] = dataValues;
        //Campi dati specifici
        QJsonObject lastDataVariationObj;
        lastDataVariationObj["X"] = magnetSensor.getLastMagneticDataVariation()->getXval();
        lastDataVariationObj["Y"] = magnetSensor.getLastMagneticDataVariation()->getYval();
        lastDataVariationObj["Z"] = magnetSensor.getLastMagneticDataVariation()->getZval();
        (*infoObject)["LastMagneticDataVariation"] = lastDataVariationObj;
        QJsonObject dataVarianceObj;
        dataVarianceObj["X"] = magnetSensor.getMagneticDataVariance()->getXval();
        dataVarianceObj["Y"] = magnetSensor.getMagneticDataVariance()->getYval();
        dataVarianceObj["Z"] = magnetSensor.getMagneticDataVariance()->getZval();
        (*infoObject)["MagneticDataVariance"] = dataVarianceObj;
    }

}
}
