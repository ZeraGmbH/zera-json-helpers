#ifndef JSONSTATEFILEPERSISTENCE_H
#define JSONSTATEFILEPERSISTENCE_H

#include <QString>
#include <QJsonObject>

#include "zera-json-params-structure.h"


class JsonStateFilePersistence
{
public:
    JsonStateFilePersistence();
    QJsonObject loadState();
    void saveState(QJsonObject stateObject);


    void setStateFilePath(const QString& path);
    void setJsonParamStructure(const QJsonObject& jsonParamStructure);
    QJsonObject getJsonParamStructure() const;
private:
    QString m_stateFilePath;
    QJsonObject m_jsonParamStructure;
};

#endif // JSONSTATEFILEPERSISTENCE_H
