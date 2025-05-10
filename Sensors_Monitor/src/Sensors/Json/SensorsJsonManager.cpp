#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

#include "SensorsJsonManager.h"
#include "SensorToJsonVisitor.h"
#include "SensorJsonParser.h"

namespace Sensors {
namespace Json {

SensorsJsonManager::SensorsJsonManager(const std::string &fName)
    : AbstractSensorJsonManager(fName)
    {

    }

    void SensorsJsonManager::saveOnJSonFile(const std::vector<Sensors::AbstractSensor*> *sensors)
    {
        QJsonArray sensorsJsonObjectsList;
        //Creazione json per ogni sensore
        for(const Sensors::AbstractSensor *val : *sensors) {
            QJsonObject sensorJsonObject;
            //Campi Comuni
            sensorJsonObject["Id"] = (int)val->getId();
            sensorJsonObject["Name"] = QString::fromStdString(val->getName());
            sensorJsonObject["Description"] = QString::fromStdString(val->getDescription());
            //Campi Specifici
            SensorToJsonVisitor jVisitor;
            val->accept(jVisitor);
            QJsonObject *infoObject = jVisitor.getInfoObject();
            foreach(const QString &key, infoObject->keys()) {
                sensorJsonObject[key] = infoObject->value(key);
            }
            sensorsJsonObjectsList.append(sensorJsonObject);
            delete infoObject;
        }

        //Creo documento JSon
        QJsonDocument jsonDocument(sensorsJsonObjectsList);

        QFile jsonFile(QString::fromStdString(getSaveFileName()));

        //Controllo errore apertura file
        if(!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            setSaveFileName("");
            showErrorMessage("<b>ERRORE!</b><br>Scrittura del file<br>non riuscita!");
            return;
        }

        jsonFile.write(jsonDocument.toJson());

        jsonFile.close();

    }

    std::vector<AbstractSensor*>* SensorsJsonManager::openJSonFile()
    {
        QFile jsonFile(QString::fromStdString(getSaveFileName()));

        //Controllo esistenza file
        if(!jsonFile.exists()) {                                                     //FILE NON ESISTE
            showErrorMessage("<b>ERRORE!</b><br>Il file non esiste!");
            return nullptr;
        }

        //Controllo errore apertura file
        if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {                 //ERRORE APERTURA FILE
            showErrorMessage("<b>ERRORE!</b><br>Apertura del file<br>non riuscita!");
            return nullptr;
        }

        QByteArray jsonData = jsonFile.readAll();

        if(jsonData.isEmpty()) {                                                    //FILE VUOTO
            showErrorMessage("<b>ERRORE!</b><br>Il file è vuoto!");
            return nullptr;
        }

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &parseError);

        if(parseError.error != QJsonParseError::NoError) {                          //ERRORE PARSING
            showErrorMessage("<b>ERRORE!</b><br>C'è stato un errore<br>nel parsing dei dati!");
            return nullptr;
        }

        if(!jsonDocument.isArray()) {                                               //ERRORE CONTENUTO JSON NON IN FORMATO PREVISTO
            showErrorMessage("<b>ERRORE!</b><br>Il formato json nel<br>file non era corretto!");
            return nullptr;
        }

        std::vector<Sensors::AbstractSensor*> *sensorsVector = new std::vector<Sensors::AbstractSensor*>();

        QJsonArray sensorsArray = jsonDocument.array();
        for(auto it = sensorsArray.begin(); it != sensorsArray.end(); ++it) {
            QJsonObject sObject = (*it).toObject();
            SensorJsonParser sParser(sObject);
            if(sParser.getMainSensor() != nullptr) {
                sensorsVector->push_back(sParser.getMainSensor());
            }
        }
        if(sensorsVector->empty()) {
            delete sensorsVector;
            return nullptr;
        }
        return sensorsVector;
    }

    void SensorsJsonManager::showErrorMessage(QString message)
    {
        QMessageBox *alertMessage = new QMessageBox(QMessageBox::Critical, "Errore", message);
        alertMessage->setAttribute(Qt::WA_DeleteOnClose);
        alertMessage->addButton("Ok", QMessageBox::YesRole);
        alertMessage->exec();
    }

}
}
