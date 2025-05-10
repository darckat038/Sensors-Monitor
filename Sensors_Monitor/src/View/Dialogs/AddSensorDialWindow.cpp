#include "AddSensorDialWindow.h"
// #include "MainWindow.h"

#include "Sensors/TempSensor.h"
#include "Sensors/HumidSensor.h"
#include "Sensors/MagnetSensor.h"

#include <QHBoxLayout>
#include <QMessageBox>

#include <View/SensorInfoVisitor.h>

namespace View {
namespace Dialogs {

AddSensorDialWindow::AddSensorDialWindow(QWidget *parent)
    : QDialog{parent}, sensorType(nullptr), sensorName(nullptr), sensorDescription(nullptr), addButton(nullptr), cancelButton(nullptr), policyWarn(nullptr)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout();
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        //Avvisi inserimento
        QLabel *upperWarnLabel = new QLabel("<b>ATTENZIONE</b>", this);
        QLabel *mainWarnLabel = new QLabel("Inserimento non permesso finché non vengono inseriti/scelti sia<br>nome che tipo del sensore.");
        // mainWarnLabel->setWordWrap(true);
        mainLayout->addWidget(upperWarnLabel, 0, Qt::AlignHCenter);
        mainLayout->addWidget(mainWarnLabel, 0, Qt::AlignHCenter);

        //Scelta tipo di sensore
        QHBoxLayout *typeLayout = new QHBoxLayout();
        QLabel *sensorTypeLabel = new QLabel("Tipo: ",this);
        sensorType = new QComboBox(this);
        for(const QString &s : SensorInfoVisitor::sensorTypes){
            sensorType->addItem(s);
        }
        sensorType->setCurrentIndex(-1);                        //Setto in questa maniera in modo che non mostri niente quando appare il dialog
        typeLayout->addWidget(sensorTypeLabel);
        typeLayout->addWidget(sensorType);

        //Riga inserimento nome
        QHBoxLayout *nameLayout = new QHBoxLayout();
        QLabel *sensorNameLabel = new QLabel("Nome: ", this);
        sensorName = new QLineEdit(this);
        sensorName->setPlaceholderText("nome");
        nameLayout->addWidget(sensorNameLabel);
        nameLayout->addWidget(sensorName);

        //Riga inserimento descrizione
        QHBoxLayout *descriptionLayout = new QHBoxLayout();
        QLabel *sensorDescriptionLabel = new QLabel("Descrizione: ", this);
        sensorDescription = new QTextEdit("", this);
        sensorDescription->setPlaceholderText("descrizione");
        descriptionLayout->addWidget(sensorDescriptionLabel, 0, Qt::AlignTop);
        descriptionLayout->addWidget(sensorDescription);

        //Creazione e settaggio bottoni
        addButton = new QPushButton("Crea", this);
        cancelButton = new QPushButton("Annulla", this);
        addButton->setDisabled(true);
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addWidget(addButton);

        //Connessioni bottoni
        //Connessione con slot per confermare inserimento
        connect(addButton, &QPushButton::clicked, this, &AddSensorDialWindow::addButtonPressedSlot);
        //Connessione per chiusura dialog
        connect(addButton, &QPushButton::clicked, this, &AddSensorDialWindow::close);
        connect(cancelButton, &QPushButton::clicked, this, &AddSensorDialWindow::close);
        //Connessione per controllo se nome è inserito correttamente
        connect(sensorName, &QLineEdit::textChanged, this, &AddSensorDialWindow::nameInputChangedSlot);
        //Connessione in caso di cambiamento di scelta del tipo di sensore,
        //se ci sono campi specifici per un determinato tipo, questi vengono aggiunti
        //come campi in cui poter inserire dati nel dialog
        connect(sensorType, &QComboBox::currentIndexChanged, this, &AddSensorDialWindow::sensorTypeSelectionChangedSlot);


        //Aggiunta finale delle varie parti
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);

        //Aggiunta warning
        policyWarn = new QLabel(this);
        policyWarn->setText("<b>INSERIRE TUTTI I DATI RICHIESTI</b>");
        mainLayout->addWidget(policyWarn, 0, Qt::AlignHCenter);

        mainLayout->addLayout(buttonLayout);

        this->setLayout(mainLayout);
        // ((MainWindow*)(this->parent()))->i;

    }

    QString AddSensorDialWindow::getSensorName() const
    {
        return sensorName->text();
    }

    QString AddSensorDialWindow::getSensorDescription() const
    {
        return sensorDescription->toPlainText();
    }

    void AddSensorDialWindow::addButtonPressedSlot()
    {
        //Costruisco sensore da inviare
        Sensors::AbstractSensor *finalSensor;
        //Index tipi di sensore:
        //0. Temperatura
        //1. Umidità
        //2. Campi Magnetici
        switch(sensorType->currentIndex())
        {
        case 0:
            //Imposto id = 0, e poi nella Memory gestisco e assegno in maniera diversa
            finalSensor = new Sensors::TempSensor(0, sensorName->text().toStdString(), sensorDescription->toPlainText().toStdString());
            emit addButtonPressed(finalSensor);
            break;
        case 1:
            finalSensor = new Sensors::HumidSensor(0, sensorName->text().toStdString(), sensorDescription->toPlainText().toStdString());
            emit addButtonPressed(finalSensor);
            break;
        case 2:
            finalSensor = new Sensors::MagnetSensor(0, sensorName->text().toStdString(), sensorDescription->toPlainText().toStdString());
            emit addButtonPressed(finalSensor);
            break;
        default:
            QMessageBox *alertMessage = new QMessageBox(QMessageBox::Critical, "Errore", "<b>ERRORE</b>C'è stato un problema<br> nella creazione del sensore!");
            alertMessage->setAttribute(Qt::WA_DeleteOnClose);
            alertMessage->addButton("Ok", QMessageBox::YesRole);
            alertMessage->exec();
            break;
        }
    }

    void AddSensorDialWindow::sensorTypeSelectionChangedSlot(const int index)
    {

        if(index == -1 || sensorName->text() == "") {
            addButton->setDisabled(true);
            policyWarn->show();
        } else{
            addButton->setDisabled(false);
            policyWarn->hide();
        }
    }

    void AddSensorDialWindow::nameInputChangedSlot(const QString &innerText)
    {

        if(innerText == "" || sensorType->currentIndex() == -1) {
            addButton->setDisabled(true);
            policyWarn->show();
        } else {
            addButton->setDisabled(false);
            policyWarn->hide();
        }
    }


}
}
