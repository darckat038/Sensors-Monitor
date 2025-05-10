#ifndef SENSORINFO_H
#define SENSORINFO_H

#include <QWidget>
#include <QLabel>

#include "Sensors/AbstractSensor.h"
#include "Sensors/SensorObserverI.h"

namespace View {

class SensorInfo : public QWidget, public Sensors::SensorObserverI
{
    Q_OBJECT

private:
    //Sensore di riferimento per il visitor
    Sensors::AbstractSensor *mainSensor;

    //Campi comuni
    QLabel *sensorName;
    QLabel *sensorDescription;

    //Campi specifici
    QWidget *iconWidget;
    QWidget *infoWidget;

public:
    SensorInfo(Sensors::AbstractSensor *aSensor, QWidget *parent = nullptr);

    ~SensorInfo();

    //Metodo di notifica observer
    void notify(Sensors::AbstractSensor &sensor) override;

    //Metodo di notifica eliminazione observer
    void notifyDeletion() override;

signals:
};

}

#endif // SENSORINFO_H
