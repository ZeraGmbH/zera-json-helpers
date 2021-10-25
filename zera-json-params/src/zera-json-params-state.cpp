#include "zera-json-params-state.h"
#include "zera-json-merge.h"

cZeraJsonParamsState::cZeraJsonParamsState()
{

}

void cZeraJsonParamsState::setStructure(const QJsonObject jsonStructure)
{
    m_jsonStructure = jsonStructure;
}

QJsonObject cZeraJsonParamsState::createDefaultJsonState()
{
    QJsonObject jsonStateObj;
    QStringList jsonStructurePathList;
    createDefaultJsonStateRecursive(jsonStateObj, m_jsonStructure, jsonStructurePathList);
    return jsonStateObj;
}

cZeraJsonParamsState::ErrList cZeraJsonParamsState::validateJsonState(const QJsonObject &jsonState)
{
    ErrList errList;
    // TODO
    return errList;
}

void cZeraJsonParamsState::createDefaultJsonStateRecursive(QJsonObject &jsonStateObj, QJsonObject& jsonStructObj, QStringList jsonStructurePathList)
{
    for(QJsonObject::ConstIterator structSubIter=jsonStructObj.begin(); structSubIter!=jsonStructObj.end(); structSubIter++) {
        QString structKey = structSubIter.key();
        if(structKey == QStringLiteral("zj_params")) {
            int subPathDepth = jsonStructurePathList.size();
            QJsonObject paramsToInsertLater;
            QJsonObject &paramsToInsert = subPathDepth == 0 ? jsonStateObj : paramsToInsertLater;
            // "zj_params" has one or more tupels (we are interested in 'default' only).
            QJsonObject paramsObj = structSubIter.value().toObject();
            for(QJsonObject::ConstIterator paramIter=paramsObj.begin(); paramIter!=paramsObj.end(); ++paramIter) {
                QJsonObject paramObj = paramIter.value().toObject();
                paramsToInsert.insert(paramIter.key(), paramObj["default"]);
            }
            // for root entries we are done here - others have to add paramsToInsertLater
            if(subPathDepth > 0) {
                if(subPathDepth > 1) {
                    // are there key paths to add?
                    for(int pathDepth=jsonStructurePathList.size()-1; pathDepth>0; pathDepth--) {
                        auto pathFromBack = jsonStructurePathList[pathDepth];
                        QJsonObject backObj = paramsToInsertLater;
                        paramsToInsertLater = QJsonObject();
                        paramsToInsertLater.insert(pathFromBack, backObj);
                    }
                    cJSONMerge::mergeJson(jsonStateObj, paramsToInsertLater);
                }
                else {
                    jsonStateObj.insert(jsonStructurePathList.takeLast(), paramsToInsertLater);
                }
            }
        }
        else if(jsonStructObj[structKey].isObject() && !jsonStructObj[structKey].isNull()) {
            QJsonValueRef subValue = jsonStructObj[structKey];
            QJsonObject subObject = subValue.toObject();
            jsonStructurePathList.push_back(structKey);
            createDefaultJsonStateRecursive(jsonStateObj, subObject, jsonStructurePathList);
            jsonStructurePathList.pop_back();
        }
    }
}

QString cZeraJsonParamsState::errEntry::strID()
{
    QString str;
    switch(m_errType) {
    case ERR_INVALID_STRUCTURE:
        str = "Invalid parameter parameter structure";
    case ERR_UNKNOWN_ENTRY:
        str = "Parameter not in structure";
    case ERR_NOT_A_PARAM:
        str = "Not a parameter";
    }
    return str;
}
