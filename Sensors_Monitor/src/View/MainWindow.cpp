#include "MainWindow.h"

#include <QChart>
#include <QChartView>
#include <QLabel>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

#include "Sensors/TempSensor.h"
#include "Sensors/HumidSensor.h"
#include "Sensors/MagnetSensor.h"

namespace View {

    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, mainSplitter(nullptr), mainToolBar(nullptr), sensorsPanel(nullptr), sensorView(nullptr), sensorsMemory(nullptr)
    {
        //Memoria principale
        sensorsMemory = new Sensors::Management::SensorsMemory();

        //Toolbar
        mainToolBar = new ToolBar(this);
        mainToolBar->setMovable(false);
        this->addToolBar(mainToolBar);

        //Statubar
        mainStatusBar = new StatusBar(sensorsMemory, this);
        this->setStatusBar(mainStatusBar);

        //Splitter Principale
        mainSplitter = new QSplitter(this);

        //Parte Sinistra
        sensorsPanel = new SensorsPanel(sensorsMemory, mainSplitter);

        //Sensori di prova
        // sensorsMemory->addSensor(new Sensors::TempSensor(0, "Temp0", "temp"));
        // sensorsMemory->addSensor(new Sensors::HumidSensor(0, "Humid0", "humid"));
        // sensorsMemory->addSensor(new Sensors::MagnetSensor(0, "Magnet0", "magnet"));
        // sensorsMemory->addSensor(new Sensors::TempSensor(0, "Temp1", "temp"));
        // sensorsMemory->addSensor(new Sensors::HumidSensor(0, "Humid1", "humid"));
        // sensorsMemory->addSensor(new Sensors::MagnetSensor(0, "Magnet1", "magnet"));
        // sensorsMemory->addSensor(new Sensors::TempSensor(0, "Temp2", "temp"));
        // sensorsMemory->addSensor(new Sensors::HumidSensor(0, "Humid2", "humid"));
        // sensorsMemory->addSensor(new Sensors::MagnetSensor(0, "Magnet2", "magnet"));
        // sensorsMemory->addSensor(new Sensors::TempSensor(0, "Temp3", "temp"));
        // sensorsMemory->addSensor(new Sensors::HumidSensor(0, "Humid3", "humid"));
        // sensorsMemory->addSensor(new Sensors::MagnetSensor(0, "Magnet3", "magnet"));

        //Parte Destra
        sensorView = new SensorView(nullptr, this);

        //Unisco le parti
        mainSplitter->addWidget(sensorsPanel);
        mainSplitter->addWidget(sensorView);

        //Per fare in modo che quando riduco fino al bordo, non scompaia
        mainSplitter->setChildrenCollapsible(false);

        setCentralWidget(mainSplitter);

        //Connessione per aggiunta sensore
        connect(sensorsPanel, &SensorsPanel::addSensor, this, &MainWindow::addSensorSlot);

        //Connessione per eliminazione sensore
        connect(sensorView, &SensorView::deleteSensor, this, &MainWindow::deleteSensorSlot);

        //Connessione per dati non salvati sensore
        connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::notSavedDataSlot);

        //Connessione per widget a sinistra premuto con info a destra
        connect(sensorsPanel, &SensorsPanel::sensorWidgetPressed, this, &MainWindow::showInfoAboutSensorSlot);

        //Connessione per salvataggio su file
        connect(mainToolBar, &ToolBar::saveFileButtonPressed, this, &MainWindow::saveOnJsonFile);

        //Connessione per salvataggio su file nuovo
        connect(mainToolBar, &ToolBar::saveFileAsButtonPressed, this, &MainWindow::saveAsJsonFile);

        //Connessione per caricamento da file
        connect(mainToolBar, &ToolBar::openFileButtonPressed, this, &MainWindow::openJsonFile);

        this->setWindowIcon(QIcon(":icons/windowIcon.svg"));

        this->setWindowTitle("Sensors Monitor");

    }    

    MainWindow::~MainWindow()
    {
        delete sensorsMemory;
    }

    void MainWindow::addSensorSlot(Sensors::AbstractSensor *fSensor) {
        sensorsMemory->addSensor(fSensor);
    }

    void MainWindow::deleteSensorSlot(Sensors::AbstractSensor *fSensor)
    {
        Sensors::AbstractSensor *s = sensorsMemory->removeSensor(fSensor->getId());
        //NOTA BENE: quando cancello sensore, imposto a nullptr tutti i puntatori a quest'ultimo
        //in modo da prevenire utilizzi
        delete s;
        //Cancello View
        sensorView->deleteLater();
        sensorView = new SensorView(nullptr, this);
        connect(sensorView, &SensorView::deleteSensor, this, &MainWindow::deleteSensorSlot);
        connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::notSavedDataSlot);
        mainSplitter->addWidget(sensorView);
    }

    void MainWindow::showInfoAboutSensorSlot(Sensors::AbstractSensor *mSensor)
    {
        //Ricreo solo se ho un sensore diverso
        if(sensorView->getMainSensorConst() != mSensor) {
            sensorView->deleteLater();
            sensorView = new SensorView(mSensor, this);
            connect(sensorView, &SensorView::deleteSensor, this, &MainWindow::deleteSensorSlot);
            connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::notSavedDataSlot);
            mainSplitter->addWidget(sensorView);
        }

        /* NOTA IMPORTANTE
         * quando elimino un widget, questo si elimina anche dal widget genitore,
         * quindi il widget genitore conterrà un widget in meno. Se voglio ricrearlo
         * e rimetterelo come figlio del widget genitore, devo riaggiungerlo a quest'ultimo.
        */
    }

    void MainWindow::saveOnJsonFile()
    {
        if(sensorsMemory->getOpenFileName() != "") {
            //Salvo su file
            sensorsMemory->saveOnJsonFile();
        }
        else {
            saveAsJsonFile();
        }
    }

    void MainWindow::openJsonFile()
    {
        QDir dirToStart(QCoreApplication::applicationDirPath());
        //Mi sposto due cartelle in alto
        dirToStart.cdUp();
        dirToStart.cdUp();
        //Ricavo il nome del file da cui caricare i sensori
        QString fileToOpenName = QFileDialog::getOpenFileName(this, "Open JSon File", dirToStart.absolutePath(), "*.json");
        if(fileToOpenName != "") {
            if(sensorsMemory->areThereSensors()) {
                if(showWarningMessageBox("<b>ATTENZIONE!</b><br>Se vengono trovati sensori<br>validi nel file, tutti i sensori<br>già presenti verranno eliminati.<br>Continuare?") == 0)
                    return;
            }
            //Faccio in modo di mostrare tutti i sensori del pannello laterale sinistro
            sensorsPanel->setFilterText("");

            //Carico da file
            sensorsMemory->openJsonFile(fileToOpenName.toStdString());

            //Cancello view sensore precedente
            sensorView->deleteLater();
            sensorView = new SensorView(nullptr, this);
            connect(sensorView, &SensorView::deleteSensor, this, &MainWindow::deleteSensorSlot);
            connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::notSavedDataSlot);
            mainSplitter->addWidget(sensorView);;
        }
    }

    void MainWindow::saveAsJsonFile()
    {
        QDir dirToStart(QCoreApplication::applicationDirPath());
        dirToStart.cdUp();
        dirToStart.cdUp();
        QString fileToSaveName = QFileDialog::getSaveFileName(this, "Save to JSon File", dirToStart.absolutePath(), "*.json");
        if(fileToSaveName != "") {
            //Controllo se c'è già un file su cui sto salvando
            QString openFileName = QString::fromStdString(sensorsMemory->getOpenFileName());
            if(openFileName != "" || sensorsMemory->areThereSensors()) {
                //Se c'è già un altro file aperto, avverto l'utente
                if(showWarningMessageBox("<b>ATTENZIONE!</b><br>I sensori verranno salvati SOLO sul nuovo file. Continuare?") == 0)
                    return;
            }
            //Salvo su nuovo file
            sensorsMemory->saveAsOnJsonFile(fileToSaveName.toStdString(), false);
        }
    }

    void MainWindow::notSavedDataSlot()
    {
        sensorsMemory->setSaved(false);
    }

    void MainWindow::closeEvent(QCloseEvent *event)
    {
        //Controllo salvataggi
        if(!sensorsMemory->isSaved()){
            //Se c'è materiale non salvato, avverto l'utente
            if(showWarningMessageBox("<b>ATTENZIONE!</b><br>Ci sono salvataggi non effettuati. Continuare?") == 1) {
                event->accept();
            }
            else {
                event->ignore();
            }
        }
    }

    int MainWindow::showWarningMessageBox(QString message)
    {
        QMessageBox *alertMessage = new QMessageBox(this);
        alertMessage->setIcon(QMessageBox::Warning);
        alertMessage->setText(message);
        alertMessage->setWindowTitle("Avviso");
        alertMessage->setAttribute(Qt::WA_DeleteOnClose);
        QPushButton *yesButton = new QPushButton("Ok", this);
        QPushButton *cancelButton = new QPushButton("Annulla", this);
        alertMessage->addButton(yesButton, QMessageBox::YesRole);
        alertMessage->addButton(cancelButton, QMessageBox::NoRole);
        alertMessage->setDefaultButton(yesButton);
        alertMessage->exec();
        if(alertMessage->clickedButton() == yesButton)
            return 1;
        else
            return 0;
    }

}









