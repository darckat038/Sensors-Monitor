#ifndef HUMIDSENSOR_H
#define HUMIDSENSOR_H

#include "AbstractSensor.h"
#include <string>
#include <vector>

namespace Sensors {

class HumidSensor: public AbstractSensor
{
private:
    //Vettore di valori umidità
    std::vector<double> humidityValues;
    //Media dei valori del vettore
    double avgVal;
public:
    //Costruttore Standard
    HumidSensor(unsigned int id, const std::string &name, const std::string &description);
    //Costruttore di Copia
    HumidSensor(const HumidSensor &hSensor);

    ~HumidSensor() = default;

    //Gestione attributi
    double getAvg() const;
    const std::vector<double>* getVals() const;
    void setHumidityValues(const std::vector<double> &newHumidityValues);
    void setAvgVal(double newAvgVal);


    //Calcolo e generazione dati casuali
    void calcAvg();
    void generateRandomData() override;
    void updateData() override;

    //Gestione visitor
    virtual void accept(SensorVisitorI &sensorVisitInt) const final override;

};

}

#endif // HUMIDSENSOR_H
