#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QIcon>
#include <QLabel>
#include <QWidget>
#include <QFrame>

#include "Sensors/AbstractSensor.h"
#include "Sensors/SensorObserverI.h"

namespace View {

class SensorWidget : public QFrame, public Sensors::SensorObserverI
{
    Q_OBJECT

private:
    //Info generali
    QLabel *nameLabel;
    QLabel *descriptionLabel;

    //Icona
    QWidget *iconWidget;

    //Sensore di riferimento
    Sensors::AbstractSensor* mainSensor;

public:

    SensorWidget(Sensors::AbstractSensor *sensor, QWidget *parent = nullptr);

    ~SensorWidget();

    //Gestione attributi
    const Sensors::AbstractSensor* getConstMainSensor() const;
    Sensors::AbstractSensor* getMainSensor();
    void setMainSensor(Sensors::AbstractSensor *newMainSensor);

    //Override quando widget viene premuto da mouse
    void mousePressEvent(QMouseEvent *event) override;

    //Metodo di notifica observer
    void notify(Sensors::AbstractSensor &sensor) override;

    //Metodo di notifica eliminazione observer
    void notifyDeletion() override;

signals:

    //Segnale per passare sensore di riferimento
    void mousePressed(Sensors::AbstractSensor*);
};

}

#endif // SENSORWIDGET_H
