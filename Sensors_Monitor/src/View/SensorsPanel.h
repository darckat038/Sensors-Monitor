#ifndef SENSORSPANEL_H
#define SENSORSPANEL_H

#include "Sensors/AbstractSensor.h"
#include "Sensors/Management/SensorsMemory.h"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>
#include <vector>


namespace View {

class SensorsPanel : public QWidget, public Sensors::Management::MemoryObserverI
{
    Q_OBJECT

    //Filtro
    QPushButton *searchButton;
    QLineEdit *searchBox;
    QLabel *sensorsCounter;

    //Contenitore widget sensori
    QScrollArea *scrollArea;

    //Pulsante aggiungi in fondo
    QPushButton *addSensorButton;

    //Puntatore a memoria
    //Utilizzato per observer
    Sensors::Management::SensorsMemory* sensorMemory;

public:
    SensorsPanel(Sensors::Management::SensorsMemory* sMem, QWidget *parent = nullptr);

    ~SensorsPanel();

    //Aggiorna la scroll area in base ad un vettore di sensori che rispetta il filtro
    void updateScrollArea(const std::vector<Sensors::AbstractSensor*> *sensors);

    //Restituisce il testo nel filtro
    QString getFilterText() const;

    //Imposto stringa del filtro
    void setFilterText(QString filterText);

    //Metodo di notifica
    void notify(Sensors::Management::SensorsMemory &sMemory) override;

    //Metodo di notifica eliminazione
    void notifyDeletion() override;

signals:
    //Segnale invio sensore da inserire
    void addSensor(Sensors::AbstractSensor *fSensor);

    //Segnale widget sensore cliccato
    void sensorWidgetPressed(Sensors::AbstractSensor* sensor);

private slots:
    //Slot bottone aggiunta sensore premuto
    void addSensorButtonPressedSlot();

    //Slot widget sensore cliccato
    void sensorWidgetPressedSlot(Sensors::AbstractSensor* sensor);

public slots:

    //Slot per filtrare sensori
    void filterSensorsSlot();

};

}

#endif // SENSORSPANEL_H
