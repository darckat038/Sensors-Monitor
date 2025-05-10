#include "SensorChartVisitor.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QSplineSeries>
#include <QValueAxis>

namespace Charts {

    SensorChartVisitor::SensorChartVisitor()
    : sensorChart(nullptr)
    {

    }

    QChart* SensorChartVisitor::getChartWidget() const
    {
        return sensorChart;
    }

    void SensorChartVisitor::visit(const Sensors::TempSensor &tempSensor)
    {
        sensorChart = new QChart();
        //Series si occupa di gestire e mostrare i dati del grafico
        QSplineSeries *splineSeries = new QSplineSeries(sensorChart);
        int i = 0;
        const std::vector<double> *vals = tempSensor.getVals();
        for(const double &val : *(vals)) {
            splineSeries->append(i, val);
            ++i;
        }
        splineSeries->setColor(Qt::blue);
        // splineSeries->setPen(QPen(QBrush("blue"), 2));                  //Utilizzato per cambiare spessore della linea

        sensorChart->legend()->hide();
        sensorChart->setTitle("Valori Temperatura");
        sensorChart->addSeries(splineSeries);
        sensorChart->createDefaultAxes();
        sensorChart->axes(Qt::Horizontal).first()->setTitleText("Tempo (h)");
        sensorChart->axes(Qt::Vertical).first()->setTitleText("Temperatura (°C)");
        sensorChart->axes(Qt::Horizontal).first()->setRange(0, QVariant::fromValue(vals->size()-1));
        sensorChart->axes(Qt::Vertical).first()->setRange(-60, 110);
        sensorChart->setAnimationOptions(QChart::SeriesAnimations);

    }

    void SensorChartVisitor::visit(const Sensors::HumidSensor &humidSensor)
    {
        sensorChart = new QChart();
        //Series si occupa di gestire e mostrare i dati del grafico
        QSplineSeries *splineSeries = new QSplineSeries(sensorChart);
        int i = 0;
        const std::vector<double> *vals = humidSensor.getVals();
        for(const double &val : *(vals)) {
            splineSeries->append(i, val);
            ++i;
        }
        splineSeries->setColor(Qt::darkGreen);

        sensorChart->legend()->hide();
        sensorChart->addSeries(splineSeries);
        sensorChart->setTitle("Valori Umidità");
        sensorChart->createDefaultAxes();
        sensorChart->axes(Qt::Horizontal).first()->setTitleText("Tempo (h)");
        sensorChart->axes(Qt::Vertical).first()->setTitleText("Umidità (%)");
        sensorChart->axes(Qt::Horizontal).first()->setRange(0, QVariant::fromValue(vals->size()-1));
        sensorChart->axes(Qt::Vertical).first()->setRange(0, 100);
        sensorChart->setAnimationOptions(QChart::SeriesAnimations);
    }

    void SensorChartVisitor::visit(const Sensors::MagnetSensor &magnetSensor)
    {
        sensorChart = new QChart();
        //Series si occupa di gestire e mostrare i dati del grafico
        QBarSeries *barSeries = new QBarSeries(sensorChart);
        const std::vector<Sensors::MagneticData> *vals = magnetSensor.getMagneticValues();
        QBarSet *setX = new QBarSet("X", barSeries);
        QBarSet *setY = new QBarSet("Y", barSeries);
        QBarSet *setZ = new QBarSet("Z", barSeries);
        for(const Sensors::MagneticData &val : *(vals)) {
            setX->append(val.getXval());
            setY->append(val.getYval());
            setZ->append(val.getZval());
        }
        barSeries->append(setX);
        barSeries->append(setY);
        barSeries->append(setZ);

        sensorChart->addSeries(barSeries);
        sensorChart->setTitle("Valori Campi Magnetici");

        QBarCategoryAxis *axisX = new QBarCategoryAxis(sensorChart);
        axisX->setTitleText("Tempo (h)");
        sensorChart->addAxis(axisX, Qt::AlignBottom);
        barSeries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis(sensorChart);
        axisY->setTitleText("Campi Magnetici (µT)");
        sensorChart->addAxis(axisY, Qt::AlignLeft);
        barSeries->attachAxis(axisY);

        sensorChart->legend()->setVisible(true);
        sensorChart->legend()->setAlignment(Qt::AlignBottom);
        sensorChart->axes(Qt::Horizontal).first()->setRange(0, QVariant::fromValue(vals->size()));
        sensorChart->axes(Qt::Vertical).first()->setRange(-100, 100);
        sensorChart->setAnimationOptions(QChart::SeriesAnimations);
    }

}
