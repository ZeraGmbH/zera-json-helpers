#include "zera-json-keycomparer.h"

#include <QStringList>
#include <QSet>

bool ZeraJsonKeyComparer::haveJsonsSameKeys(const QJsonObject &json1, const QJsonObject &json2)
{
    return haveJsonsSameKeysTop(json1, json2) && containsAllKeysSub(json1, json2) && containsAllKeysSub(json2, json1);
}

bool ZeraJsonKeyComparer::containsAllKeys(const QJsonObject &jsonReference, const QJsonObject &jsonTest)
{
    return containsAllKeysTop(jsonReference, jsonTest) && containsAllKeysSub(jsonReference, jsonTest);
}

bool ZeraJsonKeyComparer::haveJsonsSameKeysTop(const QJsonObject &json1, const QJsonObject &json2)
{
    return json1.keys() == json2.keys();
}

bool ZeraJsonKeyComparer::containsAllKeysTop(const QJsonObject &jsonReference, const QJsonObject &jsonTest)
{
    QStringList refKeys = jsonReference.keys();
    QStringList testKeys = jsonTest.keys();
    const QSet<QString> testKeysSet = QSet<QString>(testKeys.begin(), testKeys.end());

    bool allKeysFound = true;
    for(auto key : refKeys) {
        if(!testKeysSet.contains(key)) {
            allKeysFound = false;
            break;
        }
    }
    return allKeysFound;
}

bool ZeraJsonKeyComparer::containsAllKeysSub(const QJsonObject &jsonReference, const QJsonObject &jsonTest)
{
    bool stillSame = true;
    for(QJsonObject::ConstIterator iterRef = jsonReference.begin(); iterRef != jsonReference.end() && stillSame; iterRef++) {
        if(iterRef.value().isObject()) {
            auto iterTest = jsonTest.find(iterRef.key());
            if(iterTest != jsonTest.end() && iterTest.value().isObject()) {
                QJsonObject subRef = iterRef.value().toObject();
                QJsonObject subTest = iterTest.value().toObject();
                stillSame = containsAllKeys(subRef, subTest);
            }
            else {
                stillSame = false;
            }
        }
    }
    return stillSame;
}
