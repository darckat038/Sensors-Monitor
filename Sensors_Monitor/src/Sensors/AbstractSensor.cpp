#include "AbstractSensor.h"
#include <algorithm>

namespace Sensors {

    //Costruttore standard
    AbstractSensor::AbstractSensor(unsigned int id, const std::string &name, const std::string &description)
    : id(id), name(name), description(description)
    {

    }

    //Costruttore di copia
    AbstractSensor::AbstractSensor(const AbstractSensor &aSensor)
        : id(aSensor.getId()), name(aSensor.getName()), description(aSensor.getDescription())
    {

    }

    AbstractSensor::~AbstractSensor()
    {
        //Imposto a nullptr tutti i puntatori a questo sensore
        for(auto &obs : observers) {
            obs->notifyDeletion();
        }
    }

    unsigned int AbstractSensor::getId() const
    {
        return id;
    }

    void AbstractSensor::setId(unsigned int newId)
    {
        id = newId;
    }

    std::string AbstractSensor::getName() const
    {
        return name;
    }

    void AbstractSensor::setName(const std::string &newName)
    {
        name = newName;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

    std::string AbstractSensor::getDescription() const
    {
        return description;
    }

    void AbstractSensor::setDescription(const std::string &newDescription)
    {
        description = newDescription;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

    void AbstractSensor::registerObserver(SensorObserverI *sensorObsInt)
    {
        observers.push_back(sensorObsInt);
    }

    void AbstractSensor::unregisterObserver(SensorObserverI *sensorObsInt)
    {
        observers.erase(std::find(observers.begin(), observers.end(), sensorObsInt));
    }

}



