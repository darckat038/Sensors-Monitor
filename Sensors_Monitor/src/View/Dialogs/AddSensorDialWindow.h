#ifndef ADDSENSORDIALWINDOW_H
#define ADDSENSORDIALWINDOW_H

#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>

#include "Sensors/AbstractSensor.h"

namespace View {
namespace Dialogs {

class AddSensorDialWindow : public QDialog
{
    Q_OBJECT

private:

    //Scelta Sensore
    QComboBox *sensorType;

    //Inserimento informazioni
    QLineEdit *sensorName;
    QTextEdit *sensorDescription;

    //Bottoni
    QPushButton *addButton;
    QPushButton *cancelButton;

    //Avviso policy
    QLabel *policyWarn;

public:
    AddSensorDialWindow(QWidget *parent = nullptr);

    ~AddSensorDialWindow() = default;


    //Gestione attributi
    QString getSensorName() const;
    QString getSensorDescription() const;

signals:
    //Segnale per aggiungere un sensore
    void addButtonPressed(Sensors::AbstractSensor *fSensor);

private slots:
    //Slot per aggiungere un sensore
    void addButtonPressedSlot();

    //Slot per rilevare aggiornamento tipo di sensore
    void sensorTypeSelectionChangedSlot(const int index);

    //Slot per rilevare aggiornamento nome
    void nameInputChangedSlot(const QString &innerText);
};

}
}

#endif // ADDSENSORDIALWINDOW_H
