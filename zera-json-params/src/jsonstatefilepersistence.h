#ifndef JSONSTATEFILEPERSISTENCE_H
#define JSONSTATEFILEPERSISTENCE_H

#include <QString>
#include <QJsonObject>

#include "zera-json-params-structure.h"


class JsonStateFilePersistence
{
public:
    JsonStateFilePersistence();
    void setStateFilePath(const QString& path);
    void setJsonParamStructure(const QJsonObject& jsonParamStructure);

    QJsonObject loadState();
    bool saveState(QJsonObject stateObject);

    QJsonObject getJsonParamStructure();

private:
    bool checkStateValidity(const QJsonObject& stateObject);

    QString m_stateFilePath;
    QJsonObject m_jsonParamStructure;
};

#endif // JSONSTATEFILEPERSISTENCE_H
