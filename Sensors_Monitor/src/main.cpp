#include <QApplication>

#include "View/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Sensors Monitor");
    View::MainWindow mw;
    mw.resize(1024, 650);
    mw.show();
    return app.exec();
}
