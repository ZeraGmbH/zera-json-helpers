#include "zera-json-params-structure.h"
#include <QSet>

ZeraJsonParamsStructure::ZeraJsonParamsStructure()
{
}

ZeraJsonParamsStructure::ErrList ZeraJsonParamsStructure::setJson(QJsonObject jsonStructure)
{
    ErrList errList;
    if(!jsonStructure.isEmpty()) {
        // resolve param state templates & validate
        // Note: param templates are validated during resolve activity
        resolveJsonParamTemplates(jsonStructure, errList);
        // now params are complete for validation
        QStringList jsonStructurePathList;
        validateResolvedParamDataRecursive(jsonStructure, jsonStructurePathList, errList);
        if(errList.isEmpty()) {
            m_jsonObjStructure = jsonStructure;
        }
    }
    else {
        errEntry error(ERR_INVALID_PARAM_DEFINITION, QStringLiteral("Empty structure"));
        errList.push_back(error);
    }
    return errList;
}

const QJsonObject &ZeraJsonParamsStructure::getJson()
{
    return m_jsonObjStructure;
}

bool ZeraJsonParamsStructure::isValid()
{
    return !m_jsonObjStructure.isEmpty();
}

void ZeraJsonParamsStructure::resolveJsonParamTemplates(QJsonObject &jsonStructObj, ErrList& errList)
{
    // Find "zj_param_templates" object and start recursive resolve
    if(jsonStructObj.contains("zj_param_templates")) { // param_templates can be ommitted
        QJsonValue paramTemplateValue = jsonStructObj["zj_param_templates"];
        if(paramTemplateValue.isObject()) {
            QJsonObject jsonParamTemplatesObj = paramTemplateValue.toObject();
            // validate param_templates
            for(QJsonObject::ConstIterator iter=jsonParamTemplatesObj.begin(); iter!=jsonParamTemplatesObj.end(); ++iter) {
                validateParamData(iter, true, QStringList()<<"zj_param_templates", errList);
            }
            resolveJsonParamTemplatesRecursive(jsonStructObj, jsonParamTemplatesObj, errList);
            if(errList.isEmpty()) {
                jsonStructObj.remove("zj_param_templates");
            }
        }
        else {
            errEntry error(ERR_INVALID_PARAM_TEMPLATE, QStringLiteral("zj_param_templates"));
            errList.push_back(error);
        }
    }
}

bool ZeraJsonParamsStructure::resolveJsonParamTemplatesRecursive(QJsonObject& jsonStructObj, const QJsonObject jsonParamTemplatesObj, ErrList& errList)
{
    bool objectChanged = false;
    for(QJsonObject::Iterator sub=jsonStructObj.begin(); sub!=jsonStructObj.end(); sub++) {
        QString key = sub.key();
        if(key == QStringLiteral("zj_param_template")) {
            QString linkTo = jsonStructObj[key].toString();
            if(!linkTo.isEmpty()) {
                QJsonValue specVal = jsonParamTemplatesObj[linkTo];
                // zj_param_template reference found in zj_param_templates?
                if(!specVal.isNull() && specVal.isObject()) {
                    QJsonObject spec = jsonParamTemplatesObj[linkTo].toObject();
                    for(QJsonObject::ConstIterator specEntry=spec.begin(); specEntry!=spec.end(); specEntry++) {
                        QString specEntryKey = specEntry.key();
                        if(jsonStructObj[specEntryKey].isNull()) { // specs can be overriden
                            jsonStructObj.insert(specEntryKey, specEntry.value());
                            jsonStructObj.remove("zj_param_template");
                            objectChanged = true;
                        }
                    }
                }
                else {
                    errEntry error(ERR_INVALID_PARAM_DEFINITION, key + " : '" + linkTo + "' not found");
                    errList.push_back(error);
                }
            }
            else {
                errEntry error(ERR_INVALID_PARAM_DEFINITION, key + " : null/wrong type");
                errList.push_back(error);
            }
        }
        else if(key == QStringLiteral("zj_param_templates")) {
            continue;
        }
        else if(jsonStructObj[key].isObject() && !jsonStructObj[key].isNull()) {
            QJsonValueRef subValue = jsonStructObj[key];
            QJsonObject subObject = subValue.toObject();
            if(resolveJsonParamTemplatesRecursive(subObject, jsonParamTemplatesObj, errList)) {
                jsonStructObj[key] = subObject;
                objectChanged = true;
            }
        }
    }
    return objectChanged;
}

QSet<QString> ZeraJsonParamsStructure::m_svalidParamEntryKeys = QSet<QString>() << "type" << "min" << "max" << "decimals" << "default" << "list";
QHash<QString, QStringList> ZeraJsonParamsStructure::m_svalidParamTypes {
    { "bool",  QStringList() << "default"},
    { "number", QStringList() << "min" << "max" << "decimals" << "default"},
    { "string", QStringList() << "default"},
    { "oneof-list", QStringList() << "list" << "default"},
};


void ZeraJsonParamsStructure::validateParamData(QJsonObject::ConstIterator iter, bool inTemplate, QStringList jsonStructurePathList, ZeraJsonParamsStructure::ErrList &errList)
{
    QJsonValue value = iter.value();
    QString key = iter.key();
    QString treePosPrint = key;
    if(!jsonStructurePathList.isEmpty()) {
        treePosPrint = jsonStructurePathList.join(".") + "." + treePosPrint;
    }
    if(!inTemplate || value.isObject()) {
        QJsonObject paramObject = value.toObject();
        QString type = paramObject["type"].toString();
        bool validType = true;
        if(type.isEmpty()) {
            validType = false;
            if(!inTemplate) { // for templates param type is useful but not mandatory
                errEntry error(ERR_INVALID_PARAM_DEFINITION, treePosPrint + ".type : missing");
                errList.push_back(error);
            }
        }
        if(validType) {
            if(!m_svalidParamTypes.contains(type)) {
                validType = false;
                errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                               treePosPrint + ".type" + " : " + type + " invalid type");
                errList.push_back(error);
            }
        }
        for(QJsonObject::ConstIterator iterEntries=paramObject.begin(); iterEntries!=paramObject.end(); iterEntries++) {
            // valid data keys?
            QString entryKey = iterEntries.key();
            if(!m_svalidParamEntryKeys.contains(entryKey)) {
                errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                               treePosPrint + "." + entryKey + " invalid property");
                errList.push_back(error);
            }
            else {
                // type specific
                if(validType && entryKey != "type") {
                    // check if parameter is allowed for type
                    QStringList typeParams = m_svalidParamTypes[type]; // safe see checked above
                    if(!typeParams.contains(entryKey)) {
                        errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                       treePosPrint + "." + entryKey + " not allowed for type " + type);
                        errList.push_back(error);
                    }
                }
            }
        }
        // all properties are mandatory in resolved structure - otherwise we
        // need to plaster checks all over the place
        if(validType && !inTemplate) {
            QStringList typeParams = m_svalidParamTypes[type];
            for(auto paramRequired : typeParams) {
                if(!paramObject.contains(paramRequired)) {
                    errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                   treePosPrint + "." + paramRequired + " missing for type " + type);
                    errList.push_back(error);
                }
            }
        }
        // checks on default
        if(paramObject.contains("default")) {
            if(type == "bool") {
                if(!paramObject["default"].isBool()) {
                    errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                   treePosPrint + ".default not a bool");
                    errList.push_back(error);
                }
            }
            else if(type == "number") {
                if(!paramObject["default"].isDouble()) {
                    errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                   treePosPrint + ".default not a number");
                    errList.push_back(error);
                }
            }
            else if(type == "string") {
                if(!paramObject["default"].isString()) {
                    errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                   treePosPrint + ".default not a string");
                    errList.push_back(error);
                }
            }
            // TODO oneof-list
        }
        // max > min / default out of limit - classic late night bugs introduced
        if(paramObject.contains("max") && paramObject.contains("min")) {
            if(!paramObject["min"].isDouble()) {
                errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                               treePosPrint + ".min not a number");
                errList.push_back(error);
            }
            if(!paramObject["max"].isDouble()) {
                errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                               treePosPrint + ".max not a number");
                errList.push_back(error);
            }
            double min = paramObject["min"].toDouble();
            double max = paramObject["max"].toDouble();
            if(max < min) {
                errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                               treePosPrint + ".max < min");
                errList.push_back(error);
            }

            if(paramObject.contains("default")) {
                double dbldefault = paramObject["default"].toDouble();
                if(dbldefault < min) {
                    errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                   treePosPrint + ".default < min");
                    errList.push_back(error);
                }
                if(dbldefault > max) {
                    errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                   treePosPrint + ".default > max");
                    errList.push_back(error);
                }
            }
        }
        if(paramObject.contains("decimals")) {
            if(!paramObject["decimals"].isDouble()) {
                errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                               treePosPrint + ".decimals not a number");
                errList.push_back(error);
            }
            else {
                double dblDecimals = paramObject["decimals"].toDouble();
                if(dblDecimals<0.0 || dblDecimals>10.0) {
                    errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                                   treePosPrint + ".decimals out of range");
                    errList.push_back(error);
                }
            }
        }
        // TODO valid data types for other?? / maximum tree depth
    }
    else {
        errEntry error(inTemplate ? ERR_INVALID_PARAM_TEMPLATE_DEFINITION : ERR_INVALID_PARAM_DEFINITION,
                       value.isNull() ? "null" : key);
        errList.push_back(error);
    }
}

void ZeraJsonParamsStructure::validateResolvedParamDataRecursive(QJsonObject &jsonStructObj, QStringList jsonStructurePathList, ZeraJsonParamsStructure::ErrList &errList)
{
    for(QJsonObject::Iterator sub=jsonStructObj.begin(); sub!=jsonStructObj.end(); sub++) {
        QString key = sub.key();
        if(key == QStringLiteral("zj_params")) {
            if(sub.value().isObject()) {
                QJsonObject paramsObj = sub.value().toObject();
                for(QJsonObject::ConstIterator iter=paramsObj.begin(); iter!=paramsObj.end(); ++iter) {
                    jsonStructurePathList.push_back(key);
                    validateParamData(iter, false, jsonStructurePathList, errList);
                    jsonStructurePathList.pop_back();
                }
            }
        }
        else if(jsonStructObj[key].isObject() && !jsonStructObj[key].isNull()) {
            QJsonValueRef subValue = jsonStructObj[key];
            QJsonObject subObject = subValue.toObject();
            jsonStructurePathList.push_back(key);
            validateResolvedParamDataRecursive(subObject, jsonStructurePathList, errList);
            jsonStructurePathList.pop_back();
        }
    }
}

ZeraJsonParamsStructure::errEntry::errEntry(ZeraJsonParamsStructure::errorTypes errType, QString strInfo) :
    m_errType(errType),
    m_strInfo(strInfo)
{
}

QString ZeraJsonParamsStructure::errEntry::strID()
{
    QString str;
    switch(m_errType) {
    case ERR_INVALID_PARAM_TEMPLATE:
        str = "Invalid parameter template";
        break;
    case ERR_INVALID_PARAM_TEMPLATE_DEFINITION:
        str = "Invalid parameter template defintion";
        break;
    case ERR_INVALID_PARAM_DEFINITION:
        str = "Invalid parameter template defintion";
        break;
    }
    return str;
}
