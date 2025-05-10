#include "MagnetSensor.h"
#include <numeric>    //std::reduce

namespace Sensors {

    MagnetSensor::MagnetSensor(unsigned int id, const std::string &name, const std::string &description)
    : AbstractSensor(id, name, description)/*, lastMagneticData(nullptr),*/
    {
        generateRandomData();
    }

    MagnetSensor::MagnetSensor(const MagnetSensor &mSensor)
        : AbstractSensor(mSensor.getId(), mSensor.getName(), mSensor.getDescription()), magneticValues(*(mSensor.getMagneticValues())),
        lastMagneticDataVariation(*(mSensor.getLastMagneticDataVariation())), magneticDataVariance(*(mSensor.getMagneticDataVariance()))
    {

    }

    const std::vector<MagneticData>* MagnetSensor::getMagneticValues() const
    {
        return &magneticValues;
    }

    const MagneticData* MagnetSensor::getLastMagneticDataVariation() const
    {
        return &lastMagneticDataVariation;
    }

    const MagneticData* MagnetSensor::getMagneticDataVariance() const
    {
        return &magneticDataVariance;
    }

    void MagnetSensor::setMagneticValues(const std::vector<MagneticData> &newMagneticValues)
    {
        magneticValues = newMagneticValues;
    }

    void MagnetSensor::setLastMagneticDataVariation(const MagneticData &newLastMagneticDataVariation)
    {
        lastMagneticDataVariation = newLastMagneticDataVariation;
    }

    void MagnetSensor::setMagneticDataVariance(const MagneticData &newMagneticDataVariance)
    {
        magneticDataVariance = newMagneticDataVariance;
    }

    void MagnetSensor::calcLastMagneticDataVariation()
    {
        if(magneticValues.size() > 1) {
            MagneticData secondLastElement = *(magneticValues.end()-2);
            MagneticData lastElement = *(magneticValues.end()-1);
            lastMagneticDataVariation = (lastElement-secondLastElement);
        }
        else
            lastMagneticDataVariation = *(magneticValues.end()-1);

    }

    void MagnetSensor::calcMagneticDataVariance()
    {
        if(magneticValues.size() > 1) {

            //Calcolo media
            MagneticData meanVal(0,0,0);
            //meanVal = std::reduce(magneticValues.begin(), magneticValues.end(), 0.0) / magneticValues.size();
            for(auto it = magneticValues.begin(); it != magneticValues.end(); ++it) {
                meanVal = meanVal + (*it);
            }
            meanVal = meanVal / magneticValues.size();

            //Calcolo varianza
            MagneticData res(0,0,0);
            for(auto it = magneticValues.begin(); it != magneticValues.end(); ++it) {
                res = res + (((*it) - meanVal) * ((*it) - meanVal));
            }
            magneticDataVariance = (res / magneticValues.size());
        }
    }

    void MagnetSensor::generateRandomData()
    {
        magneticValues = std::vector<MagneticData>(15);
        for(auto it = magneticValues.begin(); it != magneticValues.end(); ++it) {
            it->generateRandomData();
        }
        // calcLastMagneticData();
        calcLastMagneticDataVariation();
        calcMagneticDataVariance();
    }

    void MagnetSensor::accept(SensorVisitorI &sensorVisitInt) const
    {
        sensorVisitInt.visit(*this);
    }

    void MagnetSensor::updateData()
    {
        generateRandomData();
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

}
