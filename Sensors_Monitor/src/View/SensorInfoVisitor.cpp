#include "SensorInfoVisitor.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSvgWidget>

namespace View {

std::vector<QString> SensorInfoVisitor::sensorTypes = {"Sensore di Temperatura", "Sensore di Umidità", "Sensore di Campi Magnetici"};

    SensorInfoVisitor::SensorInfoVisitor()
    : iconWidget(nullptr), infoWidget(nullptr)
    {

    }

    QWidget* SensorInfoVisitor::getIconWidget() const
    {
        return iconWidget;
    }

    QWidget* SensorInfoVisitor::getInfoWidget() const
    {
        return infoWidget;
    }

    QString SensorInfoVisitor::getSensorType() const
    {
        return sensorType;
    }

    void SensorInfoVisitor::visit(const Sensors::TempSensor &tempSensor)
    {
        sensorType = "Sensore di Temperatura";
        //Impostazione icona
        iconWidget = new QSvgWidget(":icons/Sensors/tempSensorIcon.svg");
        //Impostazione dati specifici
        infoWidget = new QWidget();
        QHBoxLayout *infoWidgetLayout = new QHBoxLayout(infoWidget);
        QLabel *infoMaxVal = new QLabel("Valore massimo(°C): " + QString::number(tempSensor.getMaxVal()));
        QLabel *infoMinVal = new QLabel("Valore minimo(°C): " + QString::number(tempSensor.getMinVal()));
        infoWidgetLayout->addWidget(infoMaxVal);
        infoWidgetLayout->addWidget(infoMinVal);
        infoWidget->setLayout(infoWidgetLayout);
        infoWidget->setStyleSheet("font-size: 15px");
    }

    void SensorInfoVisitor::visit(const Sensors::HumidSensor &humidSensor)
    {
        sensorType = "Sensore di Umidità";
        //Impostazione icona
        iconWidget = new QSvgWidget(":icons/Sensors/humidSensorIcon.svg");
        //Impostazione dati specifici
        infoWidget = new QLabel("Media valori(%): " + QString::number(humidSensor.getAvg()));
        infoWidget->setStyleSheet("font-size: 15px");
    }

    void SensorInfoVisitor::visit(const Sensors::MagnetSensor &magnetSensor)
    {
        sensorType = "Sensore di Campi Magnetici";
        //Impostazione icona
        iconWidget = new QSvgWidget(":icons/Sensors/magnetSensorIcon.svg");
        //Impostazione dati specifici
        infoWidget = new QWidget();
        QVBoxLayout *infoWidgetLayout = new QVBoxLayout(infoWidget);
        QString x = "<b>X</b>=" + QString::number(magnetSensor.getLastMagneticDataVariation()->getXval());
        QString y = "<b>Y</b>=" + QString::number(magnetSensor.getLastMagneticDataVariation()->getYval());
        QString z = "<b>Z</b>=" + QString::number(magnetSensor.getLastMagneticDataVariation()->getZval());
        QLabel *infoLastVariation = new QLabel("Ultima variazione(µT): " + x + " | " + y + " | " + z);

        QString varX = "<b>X</b>=" + QString::number(magnetSensor.getMagneticDataVariance()->getXval());
        QString varY = "<b>Y</b>=" + QString::number(magnetSensor.getMagneticDataVariance()->getYval());
        QString varZ = "<b>Z</b>=" + QString::number(magnetSensor.getMagneticDataVariance()->getZval());

        QLabel *infoVar = new QLabel("Varianza(µT<sup>2</sup>): " + varX + " | " + varY + " | " + varZ);

        infoWidgetLayout->addWidget(infoLastVariation);
        infoWidgetLayout->addWidget(infoVar);

        infoWidget->setLayout(infoWidgetLayout);
        infoWidget->setStyleSheet("font-size: 15px");
    }

}
