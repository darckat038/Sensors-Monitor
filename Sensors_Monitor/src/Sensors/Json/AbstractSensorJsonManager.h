#ifndef ABSTRACTJSONMANAGER_H
#define ABSTRACTJSONMANAGER_H

#include "Sensors/AbstractSensor.h"

#include <vector>
#include <string>

namespace Sensors {
namespace Json {

class AbstractSensorJsonManager
{

private:
    //File utilizzato
    std::string saveFileName;

public:
    AbstractSensorJsonManager(const std::string &fName);

    virtual ~AbstractSensorJsonManager() = default;

    std::string getSaveFileName() const;
    void setSaveFileName(const std::string &newFileName);

    //Metodi astratti per salvataggio e caricamento file di sensori
    virtual void saveOnJSonFile(const std::vector<Sensors::AbstractSensor*> *sensors) = 0;
    virtual std::vector<AbstractSensor*>* openJSonFile() = 0;

};

}
}

#endif // ABSTRACTJSONMANAGER_H
