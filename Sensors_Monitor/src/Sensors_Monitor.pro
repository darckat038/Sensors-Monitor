TARGET = Sensors_Monitor

QT += widgets           #per i widgets in generale
QT += charts            #per i grafici
QT += svgwidgets        #per i file in formato svg
QT += gui               #per le icone

HEADERS += \
    Charts/SensorChartVisitor.h \
    Sensors/AbstractSensor.h \
    Sensors/HumidSensor.h \
    Sensors/Json/AbstractSensorJsonManager.h \
    Sensors/Json/SensorJsonParser.h \
    Sensors/Json/SensorToJsonVisitor.h \
    Sensors/Json/SensorsJsonManager.h \
    Sensors/MagnetSensor.h \
    Sensors/MagneticData.h \
    Sensors/Management/MemoryObserverI.h \
    Sensors/Management/SensorsMemory.h \
    Sensors/SensorObserverI.h \
    Sensors/SensorVisitorI.h \
    Sensors/TempSensor.h \
    View/Dialogs/AddSensorDialWindow.h \
    View/Dialogs/DeleteSensorDialWindow.h \
    View/Dialogs/EditSensorDialWindow.h \
    View/MainWindow.h \
    View/SensorInfo.h \
    View/SensorInfoVisitor.h \
    View/SensorView.h \
    View/SensorWidget.h \
    View/SensorsPanel.h \
    View/StatusBar.h \
    View/ToolBar.h

SOURCES += \
    Charts/SensorChartVisitor.cpp \
    Sensors/AbstractSensor.cpp \
    Sensors/HumidSensor.cpp \
    Sensors/Json/AbstractSensorJsonManager.cpp \
    Sensors/Json/SensorJsonParser.cpp \
    Sensors/Json/SensorToJsonVisitor.cpp \
    Sensors/Json/SensorsJsonManager.cpp \
    Sensors/MagnetSensor.cpp \
    Sensors/MagneticData.cpp \
    Sensors/Management/SensorsMemory.cpp \
    Sensors/TempSensor.cpp \
    View/Dialogs/AddSensorDialWindow.cpp \
    View/Dialogs/DeleteSensorDialWindow.cpp \
    View/Dialogs/EditSensorDialWindow.cpp \
    View/MainWindow.cpp \
    View/SensorInfo.cpp \
    View/SensorInfoVisitor.cpp \
    View/SensorView.cpp \
    View/SensorWidget.cpp \
    View/SensorsPanel.cpp \
    View/StatusBar.cpp \
    View/ToolBar.cpp \
    main.cpp

RESOURCES += \
    Resources.qrc
