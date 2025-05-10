#include "HumidSensor.h"
#include <algorithm>    //std::generate & std::sort
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>

namespace Sensors {

    HumidSensor::HumidSensor(unsigned int id, const std::string &name, const std::string &description)
        : AbstractSensor(id, name, description)
    {
        generateRandomData();
    }

    HumidSensor::HumidSensor(const HumidSensor &hSensor)
        : AbstractSensor(hSensor.getId(), hSensor.getName(), hSensor.getDescription()), humidityValues(*(hSensor.getVals())), avgVal(hSensor.getAvg())
    {

    }

    double HumidSensor::getAvg() const
    {
        return avgVal;
    }

    const std::vector<double>* HumidSensor::getVals() const
    {
        return &humidityValues;
    }

    void HumidSensor::setHumidityValues(const std::vector<double> &newHumidityValues)
    {
        humidityValues = newHumidityValues;
    }

    void HumidSensor::setAvgVal(double newAvgVal)
    {
        avgVal = newAvgVal;
    }

    void HumidSensor::calcAvg()
    {
        if(!humidityValues.empty()) {
            double sum = 0;
            for(auto val: humidityValues) {
                sum += val;
            }
            avgVal = sum / humidityValues.size();
        }
    }

    void HumidSensor::generateRandomData() {
        humidityValues = std::vector<double>(15);
        //GENERAZIONE NUMERI CASUALI CON LIBRERIE C++
        std::random_device rd;            //The random seed
        std::mt19937 gen(rd());            //The Mersenne Twister engine
        std::uniform_real_distribution<double> dis(0, 100);         //Uniform Distribution from -50 to 100
        std::generate(humidityValues.begin(), humidityValues.end(), [&gen, &dis] { return dis(gen);});
        calcAvg();
    }

    void HumidSensor::accept(SensorVisitorI &sensorVisitInt) const
    {
        sensorVisitInt.visit(*this);
    }

    void HumidSensor::updateData()
    {
        generateRandomData();
        for(auto &obs : observers) {
            obs->notify(*this);
        }
    }

}
