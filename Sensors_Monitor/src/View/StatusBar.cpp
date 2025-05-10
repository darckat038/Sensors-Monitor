#include "StatusBar.h"

namespace View {

    StatusBar::StatusBar(Sensors::Management::SensorsMemory* sMem, QWidget *parent)
    : QStatusBar{parent}, sensorMemory(sMem)
    {
        fileStatusMessage = new QLabel("<b>Nessun file aperto</b>", this);
        fileStatusMessage->setTextInteractionFlags(Qt::TextSelectableByMouse);

        savingsStatusMessage = new QLabel("<b>Non salvato</b>", this);

        //Aggiungo indicatore file a destra e indicatore salvataggio a sinistra
        this->addPermanentWidget(savingsStatusMessage, 1);
        this->addPermanentWidget(fileStatusMessage, 0);

        sensorMemory->registerObserver(this);
    }

    StatusBar::~StatusBar()
    {
        if(sensorMemory)
            sensorMemory->unregisterObserver(this);
    }

    void StatusBar::notify(Sensors::Management::SensorsMemory &sMemory)
    {
        QString openFileName = QString::fromStdString(sMemory.getOpenFileName());
        if(openFileName != "")
            fileStatusMessage->setText("<b>File aperto:</b> " + openFileName);
        else
            fileStatusMessage->setText("<b>Nessun file aperto</b>");

        bool saved = sMemory.isSaved();
        if(saved)
            savingsStatusMessage->setText("<b>Salvato</b>");
        else
            savingsStatusMessage->setText("<b>Non Salvato</b>");
    }

    void StatusBar::notifyDeletion()
    {
        sensorMemory = nullptr;
    }

}
