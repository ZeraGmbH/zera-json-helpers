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
};

#endif // ZERAJSONHELPER_H
