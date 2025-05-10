#ifndef MAGNETSENSOR_H
#define MAGNETSENSOR_H

#include "AbstractSensor.h"
#include "MagneticData.h"
#include <vector>
#include <string>

namespace Sensors {

class MagnetSensor: public AbstractSensor
{
private:
    //Vettore con valori dei campi magnetici
    std::vector<MagneticData> magneticValues;
    //Ultima variazione
    MagneticData lastMagneticDataVariation;
    //Varianza
    MagneticData magneticDataVariance;
public:
    //Costruttore standard
    MagnetSensor(unsigned int id, const std::string &name, const std::string &description = "");
    //Costruttore di copia
    MagnetSensor(const MagnetSensor &mSensor);

    ~MagnetSensor() = default;

    //Gestione attributi
    const std::vector<MagneticData>* getMagneticValues() const;
    const MagneticData* getLastMagneticDataVariation() const;
    const MagneticData* getMagneticDataVariance() const;
    void setMagneticValues(const std::vector<MagneticData> &newMagneticValues);
    void setLastMagneticDataVariation(const MagneticData &newLastMagneticDataVariation);
    void setMagneticDataVariance(const MagneticData &newMagneticDataVariance);

    //Calcolo e generazione dati casuali
    void calcLastMagneticDataVariation();
    void calcMagneticDataVariance();
    void generateRandomData() override;
    void updateData() override;

    //Gestione visitor
    virtual void accept(SensorVisitorI &sensorVisitInt) const final override;

};

}

#endif // MAGNETSENSOR_H
