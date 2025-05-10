#ifndef EDITSENSORDIALWINDOW_H
#define EDITSENSORDIALWINDOW_H

#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QTextEdit>
#include <QLabel>

#include "Sensors/AbstractSensor.h"

namespace View {
namespace Dialogs {

class EditSensorDialWindow : public QDialog
{
    Q_OBJECT

private:

    //Info Tipo Sensore
    QLabel *sensorType;

    //Modifica informazioni
    QLineEdit *sensorName;
    QTextEdit *sensorDescription;

    //Bottoni
    QPushButton *editButton;
    QPushButton *cancelButton;

    //Sensore di riferimento
    Sensors::AbstractSensor *mainSensor;

    //Avviso policy
    QLabel *policyWarn;

public:
    EditSensorDialWindow(Sensors::AbstractSensor *mSensor, QWidget *parent = nullptr);

    ~EditSensorDialWindow() = default;

    //Gestione attributi
    QString getSensorName() const;
    QString getSensorDescription() const;

private slots:
    //Slot per la modifica di un sensore
    void editButtonPressedSlot();

    //Slot per rilevare aggiornamento nome
    void nameInputChangedSlot(const QString &innerText);
};

}
}

#endif // EDITSENSORDIALWINDOW_H
