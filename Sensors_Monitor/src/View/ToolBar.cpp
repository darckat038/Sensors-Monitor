#include "ToolBar.h"

namespace View {

    ToolBar::ToolBar(QWidget *parent)
    : QToolBar{parent}, openButton(nullptr), saveButton(nullptr), saveAsButton(nullptr)
    {

        //Creazione pulsanti usando le actions
        QAction *open = new QAction("Apri", this);
        open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
        open->setIcon(QIcon(":/icons/Buttons/Toolbar/openFileIcon.svg"));
        QAction *save = new QAction("Salva", this);
        save->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
        save->setIcon(QIcon(":/icons/Buttons/Toolbar/saveFileIcon.svg"));
        QAction *saveAs = new QAction("Salva con nome", this);
        saveAs->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
        saveAs->setIcon(QIcon(":/icons/Buttons/Toolbar/saveFileAsIcon.svg"));

        open->setToolTip("Apri file di sensori");
        save->setToolTip("Salva sensori");
        saveAs->setToolTip("Salva sensori su nuovo file");

        this->addActions({open, save, saveAs});
        this->insertSeparator(save);
        this->insertSeparator(saveAs);

        openButton = dynamic_cast<QToolButton*>(this->widgetForAction(open));
        saveButton = dynamic_cast<QToolButton*>(this->widgetForAction(save));
        saveAsButton = dynamic_cast<QToolButton*>(this->widgetForAction(saveAs));
        openButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        openButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        saveButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        saveButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        saveAsButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        saveAsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->setMinimumHeight(30);

        //Connessione per dialog apertura file di sensori
        connect(open, &QAction::triggered, this, &ToolBar::openFileButtonPressed);

        //Connessione per dialog salvataggio file di sensori
        connect(save, &QAction::triggered, this, &ToolBar::saveFileButtonPressed);

        //Connessione per dialog salvataggio nuovo file di sensori
        connect(saveAs, &QAction::triggered, this, &ToolBar::saveFileAsButtonPressed);
    }

}
