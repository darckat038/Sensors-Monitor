#ifndef SENSORTOJSONVISITOR_H
#define SENSORTOJSONVISITOR_H

#include <QJsonObject>

#include "Sensors/SensorVisitorI.h"
#include "Sensors/TempSensor.h"
#include "Sensors/HumidSensor.h"
#include "Sensors/MagnetSensor.h"

namespace Sensors {
namespace Json {

class SensorToJsonVisitor: public Sensors::SensorVisitorI
{

private:
    //Widget json costruito
    QJsonObject *infoObject;

public:
    SensorToJsonVisitor();

    QJsonObject *getInfoObject() const;

    //Implemento metodi astratti
    void visit(const Sensors::TempSensor &tempSensor) override;
    void visit(const Sensors::HumidSensor &humidSensor) override;
    void visit(const Sensors::MagnetSensor &magnetSensor) override;

};

}
}

#endif // SENSORTOJSONVISITOR_H
