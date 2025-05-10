#include "AbstractSensorJsonManager.h"

namespace Sensors {
namespace Json {

    AbstractSensorJsonManager::AbstractSensorJsonManager(const std::string &fName)
    : saveFileName(fName)
    {

    }

    std::string AbstractSensorJsonManager::getSaveFileName() const
    {
        return saveFileName;
    }

    void AbstractSensorJsonManager::setSaveFileName(const std::string &newFileName)
    {
        saveFileName = newFileName;
    }

}
}
