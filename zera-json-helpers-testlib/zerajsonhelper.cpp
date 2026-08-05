#include "zerajsonhelper.h"
#include <iostream>
#include <QFile>
#include <QJsonDocument>

QJsonObject ZeraJsonHelper::loadFromQrc(const QString &strTestName)
{
    QJsonObject objRet;
    QString fileName = QStringLiteral("://json-test-files/")+strTestName+QStringLiteral(".json");
    QFile jsonFile(fileName);
    if(jsonFile.open(QIODevice::Unbuffered | QIODevice::ReadOnly)) {
        objRet = QJsonDocument::fromJson(jsonFile.readAll()).object();
    }
    checkJsonObject(objRet);
    return objRet;
}

bool ZeraJsonHelper::checkJsonObject(const QJsonObject &jsonObject)
{
    bool retVal=false;
    if(jsonObject.isEmpty()){
        retVal=true;
        std::cerr << "The Provided json object is empty. Your test might fail therefore" << std::endl;
    }
    return retVal;
}
