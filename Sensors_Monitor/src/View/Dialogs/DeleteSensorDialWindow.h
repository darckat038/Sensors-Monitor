#ifndef DELETESENSORDIALWINDOW_H
#define DELETESENSORDIALWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

#include "Sensors/AbstractSensor.h"

namespace View {
namespace Dialogs {

class DeleteSensorDialWindow : public QDialog
{
    Q_OBJECT

private:

    //Info Tipo Sensore
    QLabel *sensorType;

    //Informazioni generali
    QLabel *sensorName;
    QLabel *sensorDescription;

    //Bottoni
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    //Sensore di riferimento
    Sensors::AbstractSensor *mainSensor;

public:
    DeleteSensorDialWindow(Sensors::AbstractSensor *mSensor, QWidget *parent = nullptr);

    ~DeleteSensorDialWindow() = default;

    //Gestione attributi
    QString getSensorName() const;
    QString getSensorDescription() const;

signals:
    //Segnale per eliminare un sensore
    void deleteButtonPressed(Sensors::AbstractSensor *fSensor);

private slots:
    //Slot per eliminare un sensore
    void deleteButtonPressedSlot();

};

}
}

#endif // DELETESENSORDIALWINDOW_H
