#include "SensorInfoVisitor.h"
#include "SensorWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

namespace View {

    SensorWidget::SensorWidget(Sensors::AbstractSensor *sensor, QWidget *parent)
        : QFrame{parent}, mainSensor(sensor)
    {
        QHBoxLayout *mainLayout = new QHBoxLayout();
        QVBoxLayout *infoLayout = new QVBoxLayout();

        //Info in comune
        QString id = QString::number(mainSensor->getId());
        nameLabel = new QLabel(id + " - " + QString::fromStdString(mainSensor->getName()));
        nameLabel->setStyleSheet("font-weight: bold; font-size: 15px");
        descriptionLabel = new QLabel(QString::fromStdString(mainSensor->getDescription()));
        descriptionLabel->setStyleSheet("font-size: 13px");
        descriptionLabel->setWordWrap(true);
        infoLayout->addWidget(nameLabel);
        infoLayout->addWidget(descriptionLabel);

        //Info Specifiche
        SensorInfoVisitor visitor;
        mainSensor->accept(visitor);
        iconWidget = visitor.getIconWidget();
        iconWidget->setMaximumSize({50, 50});

        //Unione finale
        mainLayout->addWidget(iconWidget);
        mainLayout->addLayout(infoLayout);

        this->setLayout(mainLayout);

        mainSensor->registerObserver(this);

        this->setMinimumWidth(360);
    }

    const Sensors::AbstractSensor* SensorWidget::getConstMainSensor() const
    {
        return mainSensor;
    }

    Sensors::AbstractSensor* SensorWidget::getMainSensor()
    {
        return mainSensor;
    }

    void SensorWidget::setMainSensor(Sensors::AbstractSensor *newMainSensor)
    {
        mainSensor = newMainSensor;
    }

    void SensorWidget::mousePressEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton) {
            emit mousePressed(this->getMainSensor());
        }
        QFrame::mousePressEvent(event);
    }

    void SensorWidget::notify(Sensors::AbstractSensor &sensor)
    {
        //Aggiorno parti in comune
        if(nameLabel->text() != QString::fromStdString(mainSensor->getName())) {
            QString id = QString::number(mainSensor->getId());
            nameLabel->setText(id + " - " + QString::fromStdString(sensor.getName()));
            nameLabel->setWordWrap(true);
        }
        if(descriptionLabel->text() != QString::fromStdString(sensor.getDescription())) {
            descriptionLabel->setText(QString::fromStdString(sensor.getDescription()));
            descriptionLabel->setWordWrap(true);
        }
    }

    void SensorWidget::notifyDeletion()
    {
        mainSensor = nullptr;
    }

    SensorWidget::~SensorWidget()
    {
        //Quando cancello il widget, lo tolgo anche dagli observers del sensore di riferimento
        if(mainSensor)
            mainSensor->unregisterObserver(this);
    }

}
