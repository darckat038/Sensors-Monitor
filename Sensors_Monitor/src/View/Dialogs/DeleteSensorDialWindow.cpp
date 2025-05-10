#include "DeleteSensorDialWindow.h"
#include "View/SensorInfoVisitor.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Sensors/TempSensor.h"
#include "Sensors/HumidSensor.h"
#include "Sensors/MagnetSensor.h"


namespace View {
namespace Dialogs {

    DeleteSensorDialWindow::DeleteSensorDialWindow(Sensors::AbstractSensor *mSensor, QWidget *parent)
    : QDialog{parent}, sensorType(nullptr), sensorName(nullptr), sensorDescription(nullptr), deleteButton(nullptr), cancelButton(nullptr), mainSensor(mSensor)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout();
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        //Info tipo di sensore
        QHBoxLayout *typeLayout = new QHBoxLayout();
        QLabel *sensorTypeLabel = new QLabel("Tipo: ",this);
        sensorType = new QLabel(this);
        SensorInfoVisitor sVisitor;
        mainSensor->accept(sVisitor);
        delete sVisitor.getIconWidget();
        delete sVisitor.getInfoWidget();
        sensorType->setText(sVisitor.getSensorType());
        sensorType->setStyleSheet("font-style: italic");

        typeLayout->addWidget(sensorTypeLabel);
        typeLayout->addWidget(sensorType, 0, Qt::AlignRight);

        //Riga modifica nome
        QHBoxLayout *nameLayout = new QHBoxLayout();
        QLabel *sensorNameLabel = new QLabel("Nome: ", this);
        sensorName = new QLabel(this);
        sensorName->setText(QString::fromStdString(mainSensor->getName()));
        nameLayout->addWidget(sensorNameLabel);
        nameLayout->addWidget(sensorName);

        //Riga modifica descrizione
        QHBoxLayout *descriptionLayout = new QHBoxLayout();
        QLabel *sensorDescriptionLabel = new QLabel("Descrizione: ", this);
        sensorDescription = new QLabel(this);
        sensorDescription->setText(QString::fromStdString(mainSensor->getDescription()));
        descriptionLayout->addWidget(sensorDescriptionLabel, 0, Qt::AlignTop);
        descriptionLayout->addWidget(sensorDescription);

        //Creazione e settaggio bottoni
        deleteButton = new QPushButton("Elimina", this);
        cancelButton = new QPushButton("Annulla", this);
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addWidget(deleteButton);

        //Connessioni bottoni
        //Connessione con slot per confermare eliminazione
        connect(deleteButton, &QPushButton::clicked, this, &DeleteSensorDialWindow::deleteButtonPressedSlot);
        //Connessione per chiusura dialog
        connect(deleteButton, &QPushButton::clicked, this, &DeleteSensorDialWindow::close);
        connect(cancelButton, &QPushButton::clicked, this, &DeleteSensorDialWindow::close);

        //Aggiunta finale delle varie parti
        mainLayout->addWidget(new QLabel("Vuoi eliminare il sensore avente questi dati?", this), 0, Qt::AlignHCenter);
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(buttonLayout);

        this->setLayout(mainLayout);
    }

    QString DeleteSensorDialWindow::getSensorName() const
    {
        return sensorName->text();
    }

    QString DeleteSensorDialWindow::getSensorDescription() const
    {
        return sensorDescription->text();
    }

    void DeleteSensorDialWindow::deleteButtonPressedSlot()
    {
        emit deleteButtonPressed(mainSensor);
    }

}
}
