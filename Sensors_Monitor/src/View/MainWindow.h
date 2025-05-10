#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SensorView.h"
#include "SensorsPanel.h"
#include "ToolBar.h"
#include "StatusBar.h"

#include <QLabel>
#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>

#include "Sensors/Management/SensorsMemory.h"

namespace View {

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    //Splitter Principale
    QSplitter *mainSplitter;

    //Toolbar
    ToolBar *mainToolBar;

    //Parte Sinistra
    SensorsPanel *sensorsPanel;

    //Parte Destra
    SensorView *sensorView;

    //Memoria sensori
    Sensors::Management::SensorsMemory *sensorsMemory;

    //Ridefinizione evento di chiusura
    void closeEvent(QCloseEvent *event) override;

    //Messaggio di avviso personalizzato
    int showWarningMessageBox(QString message);

    //Statusbar
    StatusBar *mainStatusBar;

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

signals:

private slots:

    //Slot per aggiunta ed eliminazione sensore
    void addSensorSlot(Sensors::AbstractSensor *fSensor);
    void deleteSensorSlot(Sensors::AbstractSensor *fSensor);

    //Slot per aggiornamento view
    void showInfoAboutSensorSlot(Sensors::AbstractSensor *mSensor);

    //Slot per lavorare su/con file json
    void saveOnJsonFile();
    void openJsonFile();
    void saveAsJsonFile();

    //Indico che ci sono dati non salvati
    void notSavedDataSlot();
};

}

#endif // MAINWINDOW_H
