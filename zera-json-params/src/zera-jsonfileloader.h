#ifndef CJSONFILELOADER_H
#define CJSONFILELOADER_H

#include <QJsonObject>
#include <QJsonParseError>

class cJsonFileLoader
{
public:
    static QJsonObject loadJsonFile(const QString fileName, QJsonParseError* jsonError = nullptr);
    static bool storeJsonFile(const QString fileName, const QJsonObject& opbject);
};

#endif // CJSONFILELOADER_H
