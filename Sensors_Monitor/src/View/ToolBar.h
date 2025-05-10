#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QToolButton>
#include <QWidget>

namespace View {

class ToolBar : public QToolBar
{
    Q_OBJECT

private:
    //Bottoni
    QToolButton *openButton;
    QToolButton *saveButton;
    QToolButton *saveAsButton;
public:
    ToolBar(QWidget *parent = nullptr);

signals:
    //Segnale bottone apertura file premuto
    void openFileButtonPressed();

    //Segnale bottone salvataggio su file premuto
    void saveFileButtonPressed();

    //Segnale bottone salvataggio su nuovo file premuto
    void saveFileAsButtonPressed();

};

}

#endif // TOOLBAR_H


