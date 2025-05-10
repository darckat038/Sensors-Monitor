#include "SensorInfo.h"
#include "SensorInfoVisitor.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
// #include <QtSvgWidgets/QSvgWidget>

namespace View {

    SensorInfo::SensorInfo(Sensors::AbstractSensor *aSensor, QWidget *parent)
    : QWidget{parent}, mainSensor(aSensor)
    {

        if(mainSensor) {

            //Layout principale
            QVBoxLayout *mainLayout = new QVBoxLayout();

            //Info in comune (nome e descrizione)
            ///NOME
            sensorName = new QLabel(this);
            sensorName->setText(QString::fromStdString(mainSensor->getName()));
            sensorName->setStyleSheet("font-weight: bold; font-size: 25px");
            ///DESCRIZIONE
            sensorDescription = new QLabel(this);
            sensorDescription->setText(QString::fromStdString(mainSensor->getDescription()));
            sensorDescription->setStyleSheet("font-size: 20px");
            sensorDescription->setWordWrap(true);
            ///LAYOUT
            QVBoxLayout *commonInfoLayout = new QVBoxLayout();
            commonInfoLayout->addWidget(sensorName);
            commonInfoLayout->addWidget(sensorDescription);

            //Info specifiche (VISITOR)
            ///ICONA
            SensorInfoVisitor visitor;
            mainSensor->accept(visitor);
            iconWidget = visitor.getIconWidget();
            iconWidget->setMaximumSize(QSize(50, 50));
            iconWidget->setMinimumSize(QSize(20, 20));
            ///INFORMAZIONI
            infoWidget = visitor.getInfoWidget();
            ///LAYOUT
            QHBoxLayout *upperInfoLayout = new QHBoxLayout();
            upperInfoLayout->addWidget(iconWidget);
            upperInfoLayout->addLayout(commonInfoLayout);

            //Unione finale
            mainLayout->addLayout(upperInfoLayout);
            mainLayout->addWidget(infoWidget);

            this->setLayout(mainLayout);

            mainSensor->registerObserver(this);

        }

        this->setMinimumHeight(150);
    }

    void SensorInfo::notify(Sensors::AbstractSensor &sensor)
    {
        //Aggiorno parti in comune
        if(sensorName->text() != QString::fromStdString(sensor.getName())) {
            sensorName->setText(QString::fromStdString(sensor.getName()));
            sensorName->setWordWrap(true);
        }
        if(sensorDescription->text() != QString::fromStdString(sensor.getDescription())) {
            sensorDescription->setText(QString::fromStdString(sensor.getDescription()));
            sensorDescription->setWordWrap(true);
        }

        //Aggiorno parti specifiche
        SensorInfoVisitor visitor;
        sensor.accept(visitor);
        infoWidget->deleteLater();
        infoWidget = visitor.getInfoWidget();
        static_cast<QVBoxLayout*>(this->layout())->addWidget(infoWidget);
    }

    void SensorInfo::notifyDeletion()
    {
        mainSensor = nullptr;
    }

    SensorInfo::~SensorInfo()
    {
        //Quando cancello il widget, lo tolgo anche dagli observers del sensore di riferimento (se non nullptr)
        if(mainSensor)
            mainSensor->unregisterObserver(this);

    }
}
