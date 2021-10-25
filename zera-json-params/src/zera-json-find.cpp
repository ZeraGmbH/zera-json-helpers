#include "zera-json-find.h"

QJsonValue cJSONFind::findJson(const QJsonObject &jsonObject, QStringList keyList)
{
    QJsonValue foundValue = jsonObject;
    while(!keyList.isEmpty()) {
        QString key = keyList.takeFirst();
        if(foundValue.isObject() && foundValue.toObject().contains(key)) {
            foundValue = foundValue.toObject()[key];
        }
        else {
            foundValue = QJsonValue();
            break;
        }
    }
    return foundValue;
}
