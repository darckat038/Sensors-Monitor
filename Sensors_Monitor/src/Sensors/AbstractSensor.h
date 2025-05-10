#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "SensorObserverI.h"
#include "SensorVisitorI.h"

#include <vector>
#include <string>

namespace Sensors {

class AbstractSensor
{
private:
    //Id
    unsigned int id;
    //Nome
    std::string name;
    //Descrizione
    std::string description;

protected:
    std::vector<SensorObserverI*> observers;
public:
    //Costruttore Standard
    AbstractSensor(unsigned int id, const std::string &name, const std::string &description = "");
    //Costruttore di Copia
    AbstractSensor(const AbstractSensor& aSensor);

    virtual ~AbstractSensor();

    //Metodi per gestire gli attributi
    unsigned int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    void setId(unsigned int newId);
    void setName(const std::string &newName);
    void setDescription(const std::string &newDescription);

    //Gestione visitors
    virtual void accept(SensorVisitorI &sensorVisitInt) const = 0;

    //Gestione observers
    void registerObserver(SensorObserverI *sensorObsInt);
    void unregisterObserver(SensorObserverI *sensorObsInt);

    //Generazione dati casuali
    virtual void generateRandomData() = 0;
    virtual void updateData() = 0;

};

}

#endif // ABSTRACTSENSOR_H
