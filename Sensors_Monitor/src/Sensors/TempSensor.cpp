#include "TempSensor.h"
#include <algorithm>    // std::min_element, std::max_element, std::generate
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>

namespace Sensors {

    TempSensor::TempSensor(unsigned int id, const std::string &name, const std::string &description)
        : AbstractSensor(id, name, description)
    {
        generateRandomData();

    }

    //Costruttore di copia
    TempSensor::TempSensor(const TempSensor& tSensor)
        : AbstractSensor(tSensor.getId(), tSensor.getName(), tSensor.getDescription()), temperatureValues(*(tSensor.getVals())), maxVal(tSensor.getMaxVal()), minVal(tSensor.getMinVal())
    {

    }

    double TempSensor::getMaxVal() const
    {
        return maxVal;
    }

    double TempSensor::getMinVal() const
    {
        return minVal;
    }

    const std::vector<double>* TempSensor::getVals() const
    {
        return &temperatureValues;
    }

    void TempSensor::setTemperatureValues(const std::vector<double> &newTemperatureValues)
    {
        temperatureValues = newTemperatureValues;
    }

    void TempSensor::setMaxVal(double newMaxVal)
    {
        maxVal = newMaxVal;
    }

    void TempSensor::setMinVal(double newMinVal)
    {
        minVal = newMinVal;
    }

    void TempSensor::calcMaxMin() {

        if(!temperatureValues.empty()) {
            // std::sort(temperatureValues.begin(), temperatureValues.end());
            // maxVal = *(temperatureValues.end()-1);
            // minVal = *(temperatureValues.begin());
            maxVal = *std::max_element(temperatureValues.begin(), temperatureValues.end());
            minVal = *std::min_element(temperatureValues.begin(), temperatureValues.end());
        }
        else {
            maxVal = 0;
            minVal = 0;
        }

    }

    void TempSensor::generateRandomData() {
        temperatureValues = std::vector<double>(15);
        //GENERAZIONE NUMERI CASUALI CON LIBRERIE C++
        std::random_device rd;            //The random seed
        std::mt19937 gen(rd());            //The Mersenne Twister engine
        std::uniform_real_distribution<double> dis(-50, 100);         //Uniform Distribution from -50 to 100
        std::generate(temperatureValues.begin(), temperatureValues.end(), [&gen, &dis] { return dis(gen);});
        calcMaxMin();
    }

    void TempSensor::accept(SensorVisitorI &sensorVisitInt) const
    {
        sensorVisitInt.visit(*this);

    }

    void TempSensor::updateData()
    {
        generateRandomData();
        for(auto &obs : observers) {
            obs->notify(*this);
        }

    }

}
