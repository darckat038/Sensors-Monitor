#ifndef SENSOROBSERVERI_H
#define SENSOROBSERVERI_H

namespace Sensors {

class AbstractSensor;

class SensorObserverI
{
public:
    virtual ~SensorObserverI() = default;

    //Metodo di notifica
    virtual void notify(AbstractSensor& sensor) = 0;

    //Metodo di notifica eliminazione
    virtual void notifyDeletion() = 0;

};

}

#endif // SENSOROBSERVERI_H
