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
    if(p_data.empty()){
        retVal=true;
        std::cerr << "The Provided json object is empty. Your test might fail therefore" << std::endl;
    }
    return retVal;
}


// These following methods can go - keep them as reminder for now
QJsonObject ZeraJsonHelper::manipulateJson(const QJsonObject &p_base, QStringList p_keyList, const QJsonValue &p_newValue)
{
    QString finalKey=p_keyList.takeLast();
    QJsonObject retVal=p_base;
    QMap<QString,QJsonObject> objectArray;
    QJsonObject lastObj=retVal;
    for(QString key : p_keyList){
        if(!lastObj.contains(key)) {
            lastObj.insert(key,QJsonObject());
        }
        lastObj=lastObj[key].toObject();
    }
    lastObj[finalKey]=p_newValue;
    objectArray[p_keyList.last()]=lastObj;
    for (QStringList::reverse_iterator i = p_keyList.rbegin();i != p_keyList.rend(); ++i ){
        QJsonObject buf=objectArray[*i+1];
        buf[*i]=lastObj;
        lastObj=buf;
        objectArray[*i]=buf;
    }
    retVal=lastObj;
    return retVal;
}

QJsonObject ZeraJsonHelper::removeJsonItem(const QJsonObject p_base, QStringList p_keyList)
{
    QString finalKey=p_keyList.takeLast();
    QJsonObject retVal=p_base;
    QMap<QString,QJsonObject> objectArray;
    QJsonObject lastObj=retVal;
    for(QString key : p_keyList) {
        if(!lastObj.contains(key)) {
            lastObj.insert(key,QJsonObject());
        }
        lastObj=lastObj[key].toObject();
    }
    lastObj.remove(finalKey);
    objectArray[p_keyList.last()]=lastObj;
    for (QStringList::reverse_iterator i = p_keyList.rbegin();i != p_keyList.rend(); ++i ) {
        QJsonObject buf=objectArray[*i+1];
        buf[*i]=lastObj;
        lastObj=buf;
        objectArray[*i]=buf;
    }
    retVal=lastObj;
    return retVal;
}
