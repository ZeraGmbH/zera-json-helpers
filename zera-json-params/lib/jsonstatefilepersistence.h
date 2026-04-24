#ifndef JSONSTATEFILEPERSISTENCE_H
#define JSONSTATEFILEPERSISTENCE_H

#include <QString>
#include <QJsonObject>

class JsonStateFilePersistence
{
public:
    void setStateFilePath(const QString& path);
    void setJsonParamStructure(const QJsonObject& jsonParamStructure);

    QJsonObject loadState();
    bool saveState(const QJsonObject &stateObject);

    QJsonObject getJsonParamStructure() const;

private:
    bool checkStateValidity(const QJsonObject& stateObject);

    QString m_stateFilePath;
    QJsonObject m_jsonParamStructure;
};

#endif // JSONSTATEFILEPERSISTENCE_H
