#ifndef CJSONFILELOADER_H
#define CJSONFILELOADER_H

#include <QJsonObject>

class cJsonFileLoader
{
public:
    static QJsonObject loadJsonFile(const QString fileName);
    static bool storeJsonFile(const QString fileName, const QJsonObject& opbject);
};

#endif // CJSONFILELOADER_H
