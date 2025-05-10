#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>
#include <QWidget>

#include "Sensors/Management/SensorsMemory.h"
#include "Sensors/Management/MemoryObserverI.h"

namespace View {

class StatusBar : public QStatusBar, public Sensors::Management::MemoryObserverI
{
    Q_OBJECT

private:
    //Indicatore file
    QLabel* fileStatusMessage;

    //Indicatore salvataggio
    QLabel* savingsStatusMessage;

    //Puntatore a memoria
    //Utilizzato per observer
    Sensors::Management::SensorsMemory* sensorMemory;

public:
    StatusBar(Sensors::Management::SensorsMemory* sMem, QWidget *parent = nullptr);

    ~StatusBar();

public:
    //Metodo di notifica
    void notify(Sensors::Management::SensorsMemory &sMemory);

    //Metodo di notifica eliminazione
    void notifyDeletion();
};

}

#endif // STATUSBAR_H
