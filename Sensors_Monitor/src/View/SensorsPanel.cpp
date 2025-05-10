#include "SensorsPanel.h"
#include "SensorWidget.h"

#include <QFrame>

#include "View/Dialogs/AddSensorDialWindow.h"

namespace View {

    SensorsPanel::SensorsPanel(Sensors::Management::SensorsMemory* sMem, QWidget *parent)
    : QWidget{parent}, sensorMemory(sMem)
    {

        //ATTENZIONE: se metto this come parametro allora il layout
        //sarà automaticamente "associato" all'oggetto puntato da this, in questo
        //caso SensorsPanel
        QVBoxLayout *mainLayout = new QVBoxLayout();

        //Parte del filtro
        searchBox = new QLineEdit("");
        searchBox->setPlaceholderText("Filtro nome");
        searchButton = new QPushButton("Ricerca");
        QHBoxLayout *searchLayout = new QHBoxLayout();
        searchLayout->addWidget(searchBox);
        searchLayout->addWidget(searchButton);
        sensorsCounter = new QLabel("<b>Sensori trovati:</b> 0");

        //Connetto bottone premuto con filtro ricerca
        connect(searchButton, &QPushButton::clicked, this, &SensorsPanel::filterSensorsSlot);
        //Connetto tasto invio premuto con filtro ricerca
        connect(searchBox, &QLineEdit::returnPressed, this, &SensorsPanel::filterSensorsSlot);

        //Contenitore lista di sensori
        scrollArea = new QScrollArea(this);

        //Permette ai widget di adattarsi alla scroll area
        // scrollArea->setWidgetResizable(true);

        //Vettore di widgets inizialmente vuoto

        //Bottone di aggiunta sensore
        addSensorButton = new QPushButton("Aggiungi Sensore");
        //Bottone aggiungi premuto
        connect(addSensorButton, &QPushButton::clicked, this, &SensorsPanel::addSensorButtonPressedSlot);

        mainLayout->addLayout(searchLayout);
        mainLayout->addWidget(sensorsCounter);
        mainLayout->addWidget(scrollArea);
        mainLayout->addWidget(addSensorButton);

        this->setLayout(mainLayout);

        //Per settare dimensioni di widget attuale (in questo caso SensorsPanel)
        this->setMaximumWidth(400);
        this->setMinimumWidth(300);

        //Registro observer
        sensorMemory->registerObserver(this);
    }

    void SensorsPanel::updateScrollArea(const std::vector<Sensors::AbstractSensor*> *sensors)
    {
        //Elimino widgets precedentemente in scrollArea se ce n'è uno
        if(scrollArea->widget())
            scrollArea->takeWidget()->deleteLater();
        //Creo widget che andrà contenuto nella scrollArea
        QWidget *scrollAreaWidget = new QWidget(scrollArea);
        QVBoxLayout *scrollAreaWidgetLayout = new QVBoxLayout();
        for(Sensors::AbstractSensor *val : *sensors) {

            SensorWidget *scrollAreaSensorWidget = new SensorWidget(val, scrollAreaWidget);
            scrollAreaSensorWidget->setFrameStyle(QFrame::Box || QFrame::Plain);
            scrollAreaSensorWidget->setLineWidth(1);
            scrollAreaSensorWidget->setMidLineWidth(0);
            scrollAreaSensorWidget->setFrameShadow(QFrame::Sunken);
            scrollAreaSensorWidget->setStyleSheet("border-color: black");

            //Connetto segnale widget sensore cliccato
            connect(scrollAreaSensorWidget, &SensorWidget::mousePressed, this, &SensorsPanel::sensorWidgetPressedSlot);
            scrollAreaWidgetLayout->addWidget(scrollAreaSensorWidget);
        }

        sensorsCounter->setText("<b>Sensori trovati:</b> " + QString::number(sensors->size()));
        scrollAreaWidget->setLayout(scrollAreaWidgetLayout);
        scrollArea->setWidget(scrollAreaWidget);
        delete sensors;
    }

    QString SensorsPanel::getFilterText() const
    {
        return searchBox->text();
    }

    void SensorsPanel::setFilterText(QString filterText)
    {
        searchBox->setText(filterText);
    }

    void SensorsPanel::notify(Sensors::Management::SensorsMemory &sMemory)
    {
        updateScrollArea(sMemory.filterName(searchBox->text().toStdString()));
    }

    void SensorsPanel::notifyDeletion()
    {
        sensorMemory = nullptr;
    }

    void SensorsPanel::sensorWidgetPressedSlot(Sensors::AbstractSensor* sensor)
    {
        emit sensorWidgetPressed(sensor);
    }

    void SensorsPanel::filterSensorsSlot()
    {
        updateScrollArea(sensorMemory->filterName(searchBox->text().toStdString()));
    }

    void SensorsPanel::addSensorButtonPressedSlot()
    {
        Dialogs::AddSensorDialWindow *addWindow = new Dialogs::AddSensorDialWindow(this);
        addWindow->setWindowTitle("Aggiungi Sensore");
        //Questo permette di eliminare il dialog quando viene chiuso
        addWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(addWindow, &Dialogs::AddSensorDialWindow::addButtonPressed, this, &SensorsPanel::addSensor);
        addWindow->exec();
    }

    SensorsPanel::~SensorsPanel()
    {
        if(sensorMemory)
            sensorMemory->unregisterObserver(this);
    }

}
