#ifndef SENSORSJSONMANAGER_H
#define SENSORSJSONMANAGER_H

#include <vector>
#include <string>
#include <QString>

#include "Sensors/AbstractSensor.h"
#include "AbstractSensorJsonManager.h"

namespace Sensors {
namespace Json {

class SensorsJsonManager: public AbstractSensorJsonManager
{

public:
    SensorsJsonManager(const std::string &fName);

    ~SensorsJsonManager() = default;

    //Implemento metodi di scrittura e caricamento file di sensori
    void saveOnJSonFile(const std::vector<Sensors::AbstractSensor*> *sensors) override;
    std::vector<AbstractSensor*>* openJSonFile() override;

    //Mostro messaggio di errore quando ho problemi con file
    void showErrorMessage(QString message);
};

}
}

#endif // SENSORSJSONMANAGER_H
