#include "zerajsonhelper.h"
#include <iostream>
#include <QFile>
#include <QJsonDocument>

ZeraJsonHelper::ZeraJsonHelper()
{
}

QJsonObject ZeraJsonHelper::loadFromQrc(const QString strTestName)
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

bool ZeraJsonHelper::checkJsonObject(QJsonObject p_data)
{
    bool retVal=false;
    if(p_data.isEmpty()){
        retVal=true;
        std::cerr << "The Provided json object is empty. Your test might fail therefore" << std::endl;
    }
    return retVal;
}
