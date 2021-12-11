#include "zera-jsonfileloader.h"
#include <QFile>
#include <QJsonDocument>

QJsonObject cJsonFileLoader::loadJsonFile(const QString fileName)
{
    QJsonObject json;
    QFile file(fileName);
    if(file.open(QIODevice::Unbuffered | QIODevice::ReadOnly)) {
        QByteArray jsondeviceInfoData = file.readAll();
        file.close();
        json = QJsonDocument::fromJson(jsondeviceInfoData).object();
    }
    return json;
}

bool cJsonFileLoader::storeJsonFile(const QString fileName, const QJsonObject &object)
{
    bool success = false;
    QFile deviceStateFile(fileName);
    if(deviceStateFile.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(object);
        deviceStateFile.write(doc.toJson(QJsonDocument::Indented));
        deviceStateFile.close();
        success = true;
    }
    return success;
}
