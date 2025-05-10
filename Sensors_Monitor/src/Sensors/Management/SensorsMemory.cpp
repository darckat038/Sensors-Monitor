#include "SensorsMemory.h"
#include "Sensors/Json/SensorsJsonManager.h"

#include <stdexcept>           //std::out_of_range

namespace Sensors {
namespace Management {

    unsigned int SensorsMemory::currentAvailId = 0;

    SensorsMemory::SensorsMemory()
       : jsonManager(nullptr)
    {

    }

    SensorsMemory::~SensorsMemory()
    {
        //Elimino sensori all'interno della memoria
        for(auto &val : memory) {
            delete val.second;
        }
        for(auto &obs : observers) {
            obs->notifyDeletion();
        }
        delete jsonManager;
    }

    const std::map<unsigned int, Sensors::AbstractSensor*>* SensorsMemory::getMemoryConst() const
    {
        return &memory;
    }

    std::map<unsigned int, Sensors::AbstractSensor*>* SensorsMemory::getMemory()
    {
        return &memory;
    }

    void SensorsMemory::setMemory(const std::map<unsigned int, Sensors::AbstractSensor*> &newMemory)
    {
        memory = newMemory;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

    std::vector<AbstractSensor*>* SensorsMemory::getSensorsVector() const
    {
        std::vector<AbstractSensor*> *res = new std::vector<AbstractSensor*>();
        for(const auto &val : memory) {
            res->push_back(val.second);
        }
        return res;
    }

    bool SensorsMemory::isSaved()
    {
        return changesSaved;
    }

    void SensorsMemory::setSaved(bool saved)
    {
        changesSaved = saved;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

    void SensorsMemory::registerObserver(MemoryObserverI *memObsInt)
    {
        observers.push_back(memObsInt);
    }

    void SensorsMemory::unregisterObserver(MemoryObserverI *memObsInt)
    {
        observers.erase(std::find(observers.begin(), observers.end(), memObsInt));
    }

    Sensors::AbstractSensor* SensorsMemory::getSensor(unsigned int id)
    {
        Sensors::AbstractSensor* elem = nullptr;
        if (areThereSensors()) {
            try {
                elem = memory.at(id);
                return elem;
            } catch (const std::out_of_range& e) {
                return elem;
            }
        }
        return elem;

    }

    void SensorsMemory::addSensor(Sensors::AbstractSensor *aSensor)
    {
        aSensor->setId(currentAvailId);
        memory.insert({aSensor->getId(), aSensor});
        currentAvailId += 1;
        changesSaved = false;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

    Sensors::AbstractSensor* SensorsMemory::removeSensor(unsigned int id)
    {
        Sensors::AbstractSensor *elem = nullptr;
        if(areThereSensors()) {
            elem = memory.at(id);
            memory.erase(id);
        }
        changesSaved = false;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
        return elem;
    }

    bool SensorsMemory::areThereSensors()
    {
        return memory.empty() ? false : true;
    }

    const std::vector<std::string>* SensorsMemory::splitFilterString(std::string fString) const
    {
        std::vector<std::string> *res = new std::vector<std::string>();
        long unsigned int iPos = 0;
        while(iPos < fString.size()) {
            iPos = fString.find(" ");
            res->push_back(fString.substr(0, iPos));
            fString.erase(0, iPos+1);
        }
        return res;
    }

    const std::vector<Sensors::AbstractSensor*>* SensorsMemory::filterName(std::string fString) const
    {
        std::vector<Sensors::AbstractSensor*> *res;
        if(fString != "") {
            //Vale solo la prima parola presente, se ci sono spazi le altre
            //parole successive non vengono considerate
            res = new std::vector<Sensors::AbstractSensor*>();
            const std::vector<std::string>* stringsInFilter = splitFilterString(fString);
            for(const auto &mapVal : memory) {
                if(mapVal.second->getName().find(stringsInFilter->at(0)) != std::string::npos)
                    res->push_back(mapVal.second);
            }
            delete stringsInFilter;
        } else {
            res = getSensorsVector();
        }
        return res;
    }

    void SensorsMemory::saveOnJsonFile()
    {
        std::vector<Sensors::AbstractSensor*> *v = getSensorsVector();
        jsonManager->saveOnJSonFile(v);
        delete v;
        changesSaved = true;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

    void SensorsMemory::saveAsOnJsonFile(std::string fileName, bool saveOnOldFile)
    {
        /* CASISTICHE:
         * stesso file (non cambia niente)
         * salvataggio anche su file vecchio che però non esiste
         * salvataggio anche su file vecchio ed esiste
         * salvataggio solo su file nuovo
        */
        if(!jsonManager)
            jsonManager = new Sensors::Json::SensorsJsonManager(fileName);
        std::vector<Sensors::AbstractSensor*> *v = getSensorsVector();
        if(saveOnOldFile)
            jsonManager->saveOnJSonFile(v);
        if(fileName != getOpenFileName()) {
            jsonManager->setSaveFileName(fileName);
        }
        jsonManager->saveOnJSonFile(v);
        delete v;
        changesSaved = true;
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

    void SensorsMemory::openJsonFile(std::string fileName)
    {
        if(!jsonManager) {
            jsonManager = new Sensors::Json::SensorsJsonManager(fileName);
        } else {
            jsonManager->setSaveFileName(fileName);
        }
        std::vector<Sensors::AbstractSensor*> *res = jsonManager->openJSonFile();
        if(res != nullptr) {
            //Salvo sensori vecchi per eliminazione
            std::vector<Sensors::AbstractSensor*> *old = getSensorsVector();

            //Elimino memoria vecchia
            memory.clear();

            //Aggiungo nuovi sensori
            currentAvailId = 0;
            for(Sensors::AbstractSensor *val : *res) {
                //Inserisco sensore e segno id utilizzabile
                memory.insert({val->getId(), val});
                currentAvailId = currentAvailId <= val->getId() ? val->getId() + 1 : currentAvailId;
            }

            changesSaved = true;

            //Aggiorno observers
            for(auto &obs : observers) {
                obs->notify(*this);
            }

            //Se c'erano sensori vecchi li elimino
            if(!old->empty()) {
                for(auto &val : *old) {
                    delete val;
                }
            }
        }
    }

    std::string SensorsMemory::getOpenFileName()
    {
        if(jsonManager)
            return jsonManager->getSaveFileName();
        else
            return "";
    }

}
}
