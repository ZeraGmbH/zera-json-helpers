#ifndef ZERA_JSON_FIND_H
#define ZERA_JSON_FIND_H

#include <QJsonValue>
#include <QJsonObject>
#include <QStringList>

class cJSONFind
{
public:
    static QJsonValue findJson(const QJsonObject& jsonObject, QStringList keyList);
};

#endif // ZERA_JSON_FIND_H
