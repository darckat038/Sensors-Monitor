#ifndef SENSORSMEMORY_H
#define SENSORSMEMORY_H

#include "MemoryObserverI.h"
#include "Sensors/AbstractSensor.h"
#include "Sensors/Json/AbstractSensorJsonManager.h"

#include <map>
#include <vector>
#include <string>

namespace Sensors {
namespace Management {

class SensorsMemory
{
private:

    //Contatore per id
    static unsigned int currentAvailId;

    //Controllo salvataggio su file
    bool changesSaved = false;

    //Mappa dei sensori presenti in memoria
    std::map<unsigned int, Sensors::AbstractSensor*> memory;

    //Gestore file json
    Sensors::Json::AbstractSensorJsonManager *jsonManager;

    //Observers
    std::vector<MemoryObserverI*> observers;

public:
    SensorsMemory();

    ~SensorsMemory();

    //Metodi per gestire gli attributi della memoria
    const std::map<unsigned int, Sensors::AbstractSensor*>* getMemoryConst() const;
    std::map<unsigned int, Sensors::AbstractSensor*>* getMemory();
    void setMemory(const std::map<unsigned int, Sensors::AbstractSensor*> &newMemory);
    std::vector<Sensors::AbstractSensor*>* getSensorsVector() const;
    bool isSaved();
    void setSaved(bool saved = false);

    //Metodi per gestire gli observers
    void registerObserver(MemoryObserverI *memObsInt);
    void unregisterObserver(MemoryObserverI *memObsInt);

    //Metodi per gestire i sensori contenuti nella memoria
    Sensors::AbstractSensor* getSensor(unsigned int id);
    void addSensor(Sensors::AbstractSensor *aSensor);
    Sensors::AbstractSensor* removeSensor(unsigned int id);
    bool areThereSensors();

    //Metodi per filtrare la memoria
    const std::vector<std::string>* splitFilterString(std::string fString) const;
    const std::vector<Sensors::AbstractSensor*>* filterName(std::string nameF) const;

    //Metodi per operare sui file json
    void saveOnJsonFile();
    void saveAsOnJsonFile(std::string fileName, bool saveOnOldFile = false);
    void openJsonFile(std::string fileName);
    std::string getOpenFileName();
};

}
}

#endif // SENSORSMEMORY_H
