#ifndef CZERAJSONPARAMSSTATE_H
#define CZERAJSONPARAMSSTATE_H

#include <QJsonObject>
#include <QStringList>

class cZeraJsonParamsState
{
public:
    cZeraJsonParamsState();

    enum errorTypes {
        ERR_INVALID_STRUCTURE = 0,
        ERR_UNKNOWN_ENTRY,
        ERR_NOT_A_PARAM,
    };
    struct errEntry {
        errEntry(enum errorTypes errType, QString strInfo);
        QString strID();
        enum errorTypes m_errType;
        QString m_strInfo;
    };
    typedef QList<errEntry> ErrList;

    void setStructure(const QJsonObject jsonStructure);

    QJsonObject createDefaultJsonState();
    ErrList validateJsonState(const QJsonObject &jsonState);

private:
    void createDefaultJsonStateRecursive(QJsonObject& jsonStateObj, QJsonObject &jsonStructObj, QStringList jsonStructurePathList);

    QJsonObject m_jsonStructure;
};

#endif // CZERAJSONPARAMSSTATE_H
