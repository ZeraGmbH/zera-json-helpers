#ifndef CZERAJSONPARAMSSTATE_H
#define CZERAJSONPARAMSSTATE_H

#include <QJsonObject>
#include <QStringList>

class ZeraJsonParamsState
{
public:
    ZeraJsonParamsState();

    enum errorTypes {
        ERR_INVALID_STRUCTURE = 0,
        ERR_EMPTY_STATE,
        ERR_UNKNOWN_KEY,
        ERR_ARRAY_NOT_SUPPORTED,

        ERR_PARAM_TYPE,
        ERR_PARAM_LIMIT,

        ERR_INVALID_STRUCTURE_FATAL // This must never happen: we test structures
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
    void validateJsonStateRecursive(const QJsonObject &jsonStateObj, QStringList jsonStatePathList, ErrList &errList);
    void validateJsonStateValue(const QJsonValue &jsonStateValue, const QStringList jsonStatePathList, QJsonValue jsonParamValueStructure, ErrList &errList);

    QJsonObject m_jsonStructure;
};

#endif // CZERAJSONPARAMSSTATE_H
