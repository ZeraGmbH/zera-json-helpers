#include "zera-jsonfileloader.h"
#include <QFile>
#include <QJsonDocument>

QJsonObject cJsonFileLoader::loadJsonFile(const QString &fileName, QJsonParseError *jsonError)
{
    QJsonObject json;
    QFile file(fileName);
    if(file.open(QIODevice::Unbuffered | QIODevice::ReadOnly)) {
        QByteArray jsondeviceInfoData = file.readAll();
        file.close();
        json = QJsonDocument::fromJson(jsondeviceInfoData, jsonError).object();
    }
    return json;
}

bool cJsonFileLoader::storeJsonFile(const QString &fileName, const QJsonObject &json)
{
    bool success = false;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(json);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        success = true;
    }
    return success;
}
