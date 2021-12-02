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
