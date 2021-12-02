#ifndef CJSONFILELOADER_H
#define CJSONFILELOADER_H

#include <QJsonObject>

class cJsonFileLoader
{
public:
    static QJsonObject loadJsonFile(const QString fileName);
};

#endif // CJSONFILELOADER_H
