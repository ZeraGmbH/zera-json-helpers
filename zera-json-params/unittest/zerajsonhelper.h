#ifndef ZERAJSONHELPER_H
#define ZERAJSONHELPER_H

#include <QJsonObject>
#include <QMap>

class ZeraJsonHelper
{
public:
    ZeraJsonHelper();
    static QJsonObject loadFromQrc(const QString strTestName);
    static bool checkJsonObject(QJsonObject p_data);
    static QJsonObject manipulateJson(const QJsonObject &p_base, QStringList p_keyList, const QJsonValue &p_newValue);
    static QJsonObject removeJsonItem(const QJsonObject p_base, QStringList p_keyList);
};

#endif // ZERAJSONHELPER_H
