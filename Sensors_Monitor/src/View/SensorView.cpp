#include "SensorView.h"

#include <QChart>
#include <QChartView>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Charts/SensorChartVisitor.h"

#include "View/Dialogs/EditSensorDialWindow.h"
#include "View/Dialogs/DeleteSensorDialWindow.h"

namespace View {

    SensorView::SensorView(Sensors::AbstractSensor *sensor, QWidget *parent)
    : QWidget{parent}, mainSensor(sensor), sensorInfo(nullptr), sensorChartViewer(nullptr)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout();

        //Parte intermedia con bottoni
        QHBoxLayout *upperButtonsLayout = new QHBoxLayout();
        QVBoxLayout *mainButtonsLayout = new QVBoxLayout();
        editButton = new QPushButton("Modifica", this);
        deleteButton = new QPushButton("Elimina", this);
        simButton = new QPushButton("Nuovi Dati", this);
        upperButtonsLayout->addWidget(editButton, 0, Qt::AlignRight);
        upperButtonsLayout->addWidget(deleteButton, 0, Qt::AlignLeft);
        mainButtonsLayout->addLayout(upperButtonsLayout);
        mainButtonsLayout->addWidget(simButton, 0, Qt::AlignHCenter);

        //Connessione con bottone per modifica sensore
        connect(editButton, &QPushButton::clicked, this, &SensorView::editButtonPressedSlot);

        //Connessione con bottone per eliminazione sensore
        connect(deleteButton, &QPushButton::clicked, this, &SensorView::deleteButtonPressedSlot);

        //Connessione con bottone per la generazione di nuovi dati
        connect(simButton, &QPushButton::clicked, this, &SensorView::simButtonPressedSlot);

        //Info sensore
        sensorInfo = new SensorInfo(mainSensor, this);

        //Settaggio bottoni e grafico
        if(!mainSensor) {
            editButton->setEnabled(false);
            deleteButton->setEnabled(false);
            simButton->setEnabled(false);
            sensorChartViewer = new QChartView(this);
        } else {
            mainSensor->registerObserver(this);
            Charts::SensorChartVisitor cVisitor;
            mainSensor->accept(cVisitor);
            sensorChartViewer = new QChartView(cVisitor.getChartWidget(), this);
            sensorChartViewer->setRenderHint(QPainter::Antialiasing, true);             //Utilizzato per migliorare l'aspetto del grafico
        }

        mainLayout->addWidget(sensorInfo);
        mainLayout->addLayout(mainButtonsLayout);
        mainLayout->addWidget(sensorChartViewer);

        this->setLayout(mainLayout);

    }

    SensorView::~SensorView()
    {
        //Quando cancello il widget, lo tolgo anche dagli observers del sensore di riferimento (se non nullptr)
        if(mainSensor)
            mainSensor->unregisterObserver(this);

    }

    const Sensors::AbstractSensor *SensorView::getMainSensorConst()
    {
        return mainSensor;
    }

    void SensorView::notify(Sensors::AbstractSensor &sensor)
    {
        //Aggiorno (cambio) il grafico presente in chartview eliminando quello vecchio
        sensorChartViewer->chart()->deleteLater();
        Charts::SensorChartVisitor cVisitor;
        sensor.accept(cVisitor);
        sensorChartViewer->setChart(cVisitor.getChartWidget());
        sensorChartViewer->update();
    }

    void SensorView::notifyDeletion()
    {
        mainSensor = nullptr;
    }

    void SensorView::editButtonPressedSlot()
    {
        Dialogs::EditSensorDialWindow *editWindow = new Dialogs::EditSensorDialWindow(mainSensor, this);
        editWindow->setWindowTitle("Modifica Sensore");
        //Questo permette di eliminare il dialog quando viene chiuso
        editWindow->setAttribute(Qt::WA_DeleteOnClose);
        editWindow->exec();
        //Indico che ci sono stati cambiamenti
        if(editWindow->result())
            emit unsavedChanges();
    }

    void SensorView::deleteButtonPressedSlot()
    {
        Dialogs::DeleteSensorDialWindow *deleteWindow = new Dialogs::DeleteSensorDialWindow(mainSensor, this);
        deleteWindow->setWindowTitle("Elimina Sensore");
        //Elimino il dialog quando quest'ultimo viene chiuso
        deleteWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(deleteWindow, &Dialogs::DeleteSensorDialWindow::deleteButtonPressed, this, &SensorView::deleteSensor);
        deleteWindow->exec();
    }

    void SensorView::simButtonPressedSlot()
    {
        mainSensor->updateData();
        emit unsavedChanges();
    }

}
