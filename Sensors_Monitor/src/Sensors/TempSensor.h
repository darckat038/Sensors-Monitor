#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "AbstractSensor.h"
#include <string>
#include <vector>

namespace Sensors {

class TempSensor: public AbstractSensor
{
private:
    //Vettore con valori di temperatura
    std::vector<double> temperatureValues;
    //Valore massimo
    double maxVal;
    //Valore minimo
    double minVal;
public:
    //Costruttore standard
    TempSensor(unsigned int id, const std::string &name, const std::string &description = "");
    //Costruttore di copia
    TempSensor(const TempSensor& tSensor);

    ~TempSensor() = default;

    //Gestione attributi
    double getMaxVal() const;
    double getMinVal() const;
    const std::vector<double>* getVals() const;
    void setTemperatureValues(const std::vector<double> &newTemperatureValues);
    void setMaxVal(double newMaxVal);
    void setMinVal(double newMinVal);

    //Calcolo e generazione dati casuali
    void calcMaxMin();
    void generateRandomData() override;
    void updateData() override;

    //Gestione visitor
    virtual void accept(SensorVisitorI &sensorVisitInt) const final override;


};

}

#endif // TEMPSENSOR_H
