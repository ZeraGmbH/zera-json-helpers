#ifndef ZERAJSONKEYCOMPARER_H
#define ZERAJSONKEYCOMPARER_H

#include <QJsonObject>

class ZeraJsonKeyComparer
{
public:
    static bool haveJsonsSameKeys(const QJsonObject &json1, const QJsonObject &json2);
    static bool containsAllKeys(const QJsonObject &jsonReference, const QJsonObject &jsonTest);
private:
    static bool haveJsonsSameKeysTop(const QJsonObject &json1, const QJsonObject &json2);
    static bool containsAllKeysTop(const QJsonObject &jsonReference, const QJsonObject &jsonTest);
    static bool containsAllKeysSub(const QJsonObject &jsonReference, const QJsonObject &jsonTest);
};

#endif // ZERAJSONKEYCOMPARER_H
