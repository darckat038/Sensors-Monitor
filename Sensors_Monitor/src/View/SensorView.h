#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include "SensorInfo.h"

#include <QChartView>
#include <QPushButton>
#include <QWidget>

#include "Sensors/AbstractSensor.h"

namespace View {

class SensorView : public QWidget, public Sensors::SensorObserverI
{
    Q_OBJECT

private:

    //Sensore di riferimento
    Sensors::AbstractSensor *mainSensor;

    //Info del sensore
    SensorInfo *sensorInfo;

    //Bottoni
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *simButton;

    //Grafico del sensore
    QChartView *sensorChartViewer;

public:
    SensorView(Sensors::AbstractSensor *sensor = nullptr, QWidget *parent = nullptr);

    ~SensorView();

    //Gestione attributi
    const Sensors::AbstractSensor* getMainSensorConst();

    //Metodo di notifica tramite observer
    void notify(Sensors::AbstractSensor &sensor) override;

    //Metodo di notifica eliminazione
    void notifyDeletion() override;

signals:
    //Segnale eliminazione sensore
    void deleteSensor(Sensors::AbstractSensor *fSensor);

    //Segnale per indicare elementi da salvare
    void unsavedChanges();

private slots:
    //Slot bottone modifica sensore premuto
    void editButtonPressedSlot();

    //Slot bottone eliminazione sensore premuto
    void deleteButtonPressedSlot();

    //Slot bottone aggiornamento dati sensore premuto
    void simButtonPressedSlot();
};

}

#endif // SENSORVIEW_H
