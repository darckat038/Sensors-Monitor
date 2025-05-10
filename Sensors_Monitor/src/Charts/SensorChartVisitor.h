#ifndef SENSORCHARTVISITOR_H
#define SENSORCHARTVISITOR_H

#include <QChart>

#include "Sensors/SensorVisitorI.h"
#include "Sensors/TempSensor.h"
#include "Sensors/HumidSensor.h"
#include "Sensors/MagnetSensor.h"

namespace Charts
{

class SensorChartVisitor: public Sensors::SensorVisitorI
{

private:

    //Widget che contiene il grafico
    QChart *sensorChart;

public:
    SensorChartVisitor();

    QChart* getChartWidget() const;

    //Implemento le dichiarazioni incomplete di SensorVisitorI
    void visit(const Sensors::TempSensor &tempSensor) override;
    void visit(const Sensors::HumidSensor &humidSensor) override;
    void visit(const Sensors::MagnetSensor &magnetSensor) override;

    ~SensorChartVisitor() = default;
};

}

#endif // SENSORCHARTVISITOR_H
