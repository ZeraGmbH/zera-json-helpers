#ifndef ZERAJSONHELPER_H
#define ZERAJSONHELPER_H

#include <QJsonObject>
#include <QMap>

class ZeraJsonHelper
{
public:
    static QJsonObject loadFromQrc(const QString &strTestName);
    static bool checkJsonObject(const QJsonObject &jsonObject);
};

#endif // ZERAJSONHELPER_H
