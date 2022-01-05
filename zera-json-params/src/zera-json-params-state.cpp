#include "zera-json-params-state.h"
#include "zera-json-merge.h"
#include "zera-json-find.h"
#include <QJsonArray>

ZeraJsonParamsState::ZeraJsonParamsState()
{

}

void ZeraJsonParamsState::setStructure(const QJsonObject jsonStructure)
{
    m_jsonStructure = jsonStructure;
}

QJsonObject ZeraJsonParamsState::createDefaultJsonState()
{
    QJsonObject jsonStateObj;
    QStringList jsonStructurePathList;
    createDefaultJsonStateRecursive(jsonStateObj, m_jsonStructure, jsonStructurePathList);
    return jsonStateObj;
}

ZeraJsonParamsState::ErrList ZeraJsonParamsState::validateJsonState(const QJsonObject &jsonState)
{
    ErrList errList;
    if(m_jsonStructure.isEmpty()) {
        errEntry error(ERR_INVALID_STRUCTURE, "");
        errList.push_back(error);
    }
    if(jsonState.isEmpty()) {
        errEntry error(ERR_EMPTY_STATE, "");
        errList.push_back(error);
    }
    if(errList.isEmpty()) {
        validateJsonStateRecursive(jsonState, QStringList(), errList);
    }
    return errList;
}

void ZeraJsonParamsState::createDefaultJsonStateRecursive(QJsonObject &jsonStateObj, QJsonObject& jsonStructObj, QStringList jsonStructurePathList)
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

void ZeraJsonParamsState::validateJsonStateRecursive(const QJsonObject &jsonStateObj, QStringList jsonStatePathList, ZeraJsonParamsState::ErrList &errList)
{
    for(QJsonObject::ConstIterator sub=jsonStateObj.begin(); sub!=jsonStateObj.end(); sub++) {
        QString key = sub.key();
        QJsonValue jsonValueInStructure = cJSONFind::findJson(m_jsonStructure, jsonStatePathList);
        if(jsonValueInStructure.isNull()) {
            errEntry error(ERR_UNKNOWN_KEY, jsonStatePathList.join("."));
            errList.append(error);
        }
        else if(sub.value().isObject()) {
            jsonStatePathList.append(key);
            validateJsonStateRecursive(sub.value().toObject(), jsonStatePathList, errList);
            jsonStatePathList.pop_back();
        }
        else if(sub.value().isArray()) {
            jsonStatePathList.append(key);
            errEntry error(ERR_ARRAY_NOT_SUPPORTED, jsonStatePathList.join("."));
            errList.append(error);
            jsonStatePathList.pop_back();
        }
        else { // bool / number / string
            QStringList jsonStructurePathList = jsonStatePathList;
            jsonStructurePathList.append("zj_params");
            jsonStructurePathList.append(key);
            QJsonValue jsonParamInStructure = cJSONFind::findJson(m_jsonStructure, jsonStructurePathList);
            jsonStatePathList.append(key);
            if(jsonParamInStructure.isNull()) {
                errEntry error(ERR_UNKNOWN_KEY, jsonStatePathList.join("."));
                errList.append(error);
            }
            else {
                validateJsonStateValue(sub.value(), jsonStatePathList, jsonParamInStructure, errList);
            }
            jsonStatePathList.pop_back();
        }
    }
}

void ZeraJsonParamsState::validateJsonStateValue(const QJsonValue &jsonStateValue, const QStringList jsonStatePathList, QJsonValue jsonParamValueStructure, ZeraJsonParamsState::ErrList &errList)
{
    QJsonObject jsonValueStruct = jsonParamValueStructure.toObject();
    QString type = jsonValueStruct["type"].toString();
    if(type == "bool") {
        if(!jsonStateValue.isBool()) {
            errEntry error(ERR_PARAM_TYPE, jsonStatePathList.join("."));
            errList.append(error);
        }
    }
    else if(type == "number") {
        if(!jsonStateValue.isDouble()) {
            errEntry error(ERR_PARAM_TYPE, jsonStatePathList.join("."));
            errList.append(error);
        }
        else {
            double paramVal = jsonStateValue.toDouble();
            double min = jsonValueStruct["min"].toDouble();
            double max = jsonValueStruct["max"].toDouble();
            if(paramVal > max || paramVal < min) {
                errEntry error(ERR_PARAM_LIMIT, jsonStatePathList.join("."));
                errList.append(error);
            }
        }
    }
    else if(type == "string") {
        if(!jsonStateValue.isString()) {
            errEntry error(ERR_PARAM_TYPE, jsonStatePathList.join("."));
            errList.append(error);
        }
    }
    else if(type == "oneof-list") {
        // Maybe we add a sub type later - TODO?
        QJsonArray listValidEntries = jsonValueStruct["list"].toArray();
        if(!listValidEntries.contains(jsonStateValue)) {
            errEntry error(ERR_PARAM_LIMIT, jsonStatePathList.join("."));
            errList.append(error);
        }
    }
    else {
        errEntry error(ERR_INVALID_STRUCTURE_FATAL, jsonStatePathList.join("."));
        errList.append(error);
    }
}

ZeraJsonParamsState::errEntry::errEntry(ZeraJsonParamsState::errorTypes errType, QString strInfo) :
    m_errType(errType),
    m_strInfo(strInfo)
{
}

QString ZeraJsonParamsState::errEntry::strID()
{
    QString str;
    switch(m_errType) {
    case ERR_INVALID_STRUCTURE:
        str = "No parameter parameter structure";
        break;
    case ERR_EMPTY_STATE:
        str = "State is empty";
        break;
    case ERR_UNKNOWN_KEY:
        str = "Key not in structure";
        break;
    case ERR_ARRAY_NOT_SUPPORTED:
        str = "Arrays are not supported as params";
        break;
    case ERR_PARAM_TYPE:
        str = "Param has data type";
        break;
    case ERR_PARAM_LIMIT:
        str = "Param is out of limits";
        break;
    case ERR_INVALID_STRUCTURE_FATAL:
        str = "Fatal: Invalid parameter parameter structure";
        break;
    }
    return str;
}
