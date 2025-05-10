#ifndef SENSORINFOVISITOR_H
#define SENSORINFOVISITOR_H

#include <QWidget>

#include "Sensors/SensorVisitorI.h"
#include "Sensors/TempSensor.h"
#include "Sensors/HumidSensor.h"
#include "Sensors/MagnetSensor.h"

namespace View {

class SensorInfoVisitor: public Sensors::SensorVisitorI
{

private:
    //Tipo del sensore attuale
    QString sensorType;

    //Widget che contiene l'icona specifica
    QWidget *iconWidget;

    //Widget che contiene info specifiche
    QWidget *infoWidget;

public:
    //Lista dei tipi di sensori
    static std::vector<QString> sensorTypes;

    SensorInfoVisitor();

    //Gestione attributi
    QWidget* getIconWidget() const;
    QWidget* getInfoWidget() const;
    QString getSensorType() const;

    //Utilizzo le dichiarazioni incomplete di SensorVisitorI
    void visit(const Sensors::TempSensor &tempSensor) override;
    void visit(const Sensors::HumidSensor &humidSensor) override;
    void visit(const Sensors::MagnetSensor &magnetSensor) override;

    ~SensorInfoVisitor() = default;

};

}

#endif // SENSORINFOVISITOR_H

