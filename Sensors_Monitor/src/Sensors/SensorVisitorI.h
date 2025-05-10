#ifndef SENSORVISITORI_H
#define SENSORVISITORI_H

namespace Sensors {

//Su interfaccia usare class al posto di #include
//Dichiarazioni incomplete di classi
//IMPORTANTE INCLUDERE QUESTE DICHIARAZIONI INCOMPLETE NEL NAMESPACE
class TempSensor;
class HumidSensor;
class MagnetSensor;

class SensorVisitorI
{
public:
    //Metodi virtuali per visita sensore
    virtual void visit(const TempSensor &tempSensor) = 0;
    virtual void visit(const HumidSensor &humidSensor) = 0;
    virtual void visit(const MagnetSensor &magnetSensor) = 0;

    virtual ~SensorVisitorI() = default;
};

}

#endif // SENSORVISITORI_H
