#include "EditSensorDialWindow.h"

#include <QHBoxLayout>

#include "View/SensorInfoVisitor.h"

namespace View {
namespace Dialogs {

    EditSensorDialWindow::EditSensorDialWindow(Sensors::AbstractSensor *mSensor, QWidget *parent)
    : QDialog{parent}, sensorType(nullptr), sensorName(nullptr), sensorDescription(nullptr), editButton(nullptr), cancelButton(nullptr), mainSensor(mSensor)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout();
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        //Avvisi inserimento
        QLabel *upperWarnLabel = new QLabel("<b>ATTENZIONE</b>", this);
        QLabel *mainWarnLabel = new QLabel("Modifica non permessa se il nome del sensore non è inserito.");
        mainLayout->addWidget(upperWarnLabel, 0, Qt::AlignHCenter);
        mainLayout->addWidget(mainWarnLabel, 0, Qt::AlignHCenter);

        //Info (ed eventuale futura possibilità di modifica) tipo di sensore
        QHBoxLayout *typeLayout = new QHBoxLayout();
        QLabel *sensorTypeLabel = new QLabel("Tipo: ",this);
        sensorType = new QLabel(this);
        SensorInfoVisitor sVisitor;
        mainSensor->accept(sVisitor);
        //Elimino widget costruiti ma non necessari
        delete sVisitor.getIconWidget();
        delete sVisitor.getInfoWidget();
        sensorType->setText(sVisitor.getSensorType());
        sensorType->setStyleSheet("font-style: italic");

        typeLayout->addWidget(sensorTypeLabel);
        typeLayout->addWidget(sensorType, 0, Qt::AlignRight);

        //Riga modifica nome
        QHBoxLayout *nameLayout = new QHBoxLayout();
        QLabel *sensorNameLabel = new QLabel("Nome: ", this);
        sensorName = new QLineEdit(QString::fromStdString(mainSensor->getName()), this);
        sensorName->setPlaceholderText("nome");
        nameLayout->addWidget(sensorNameLabel);
        nameLayout->addWidget(sensorName);

        //Riga modifica descrizione
        QHBoxLayout *descriptionLayout = new QHBoxLayout();
        QLabel *sensorDescriptionLabel = new QLabel("Descrizione: ", this);
        sensorDescription = new QTextEdit(QString::fromStdString(mainSensor->getDescription()), this);
        sensorDescription->setPlaceholderText("descrizione");
        descriptionLayout->addWidget(sensorDescriptionLabel, 0, Qt::AlignTop);
        descriptionLayout->addWidget(sensorDescription);

        //Creazione e settaggio bottoni
        editButton = new QPushButton("Modifica", this);
        cancelButton = new QPushButton("Annulla", this);
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addWidget(editButton);

        //Connessioni bottoni
        //Connessione con slot per confermare modifica
        connect(editButton, &QPushButton::clicked, this, &EditSensorDialWindow::editButtonPressedSlot);
        //Connessione per chiusura dialog
        connect(editButton, &QPushButton::clicked, this, &EditSensorDialWindow::close);
        connect(cancelButton, &QPushButton::clicked, this, &EditSensorDialWindow::close);
        //Connessione per controllo se nome è inserito correttamente
        connect(sensorName, &QLineEdit::textChanged, this, &EditSensorDialWindow::nameInputChangedSlot);


        //Aggiunta finale delle varie parti
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);

        //Aggiunta warning
        policyWarn = new QLabel(this);
        policyWarn->setText("<b>INSERIRE TUTTI I DATI RICHIESTI</b>");
        mainLayout->addWidget(policyWarn, 0, Qt::AlignHCenter);
        policyWarn->hide();

        mainLayout->addLayout(buttonLayout);

        this->setLayout(mainLayout);

    }

    QString EditSensorDialWindow::getSensorName() const
    {
        return sensorName->text();
    }

    QString EditSensorDialWindow::getSensorDescription() const
    {
        return sensorDescription->toPlainText();
    }

    void EditSensorDialWindow::editButtonPressedSlot()
    {
        mainSensor->setName(sensorName->text().toStdString());
        mainSensor->setDescription(sensorDescription->toPlainText().toStdString());
        emit done(QDialog::Accepted);
    }

    void EditSensorDialWindow::nameInputChangedSlot(const QString &innerText)
    {
        if(innerText == "") {
            editButton->setDisabled(true);
            policyWarn->show();
        } else {
            editButton->setDisabled(false);
            policyWarn->hide();
        }
    }

}
}
