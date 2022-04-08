#include "jsonstatefilepersistence.h"

#include "zera-jsonfileloader.h"
#include "zera-json-params-state.h"

JsonStateFilePersistence::JsonStateFilePersistence()
{
}

void JsonStateFilePersistence::setStateFilePath(const QString& path)
{
    m_stateFilePath = path;
}

void JsonStateFilePersistence::setJsonParamStructure(const QJsonObject& jsonParamStructure)
{
    m_jsonParamStructure = jsonParamStructure;
}

QJsonObject JsonStateFilePersistence::getJsonParamStructure() const
{
    return m_jsonParamStructure;
}

bool JsonStateFilePersistence::checkStateValidity(const QJsonObject &stateObject)
{
    ZeraJsonParamsState jsonParamsState(m_jsonParamStructure);
    ZeraJsonParamsState::ErrList errList = jsonParamsState.validateJsonState(stateObject);
    return errList.isEmpty();
}

QJsonObject JsonStateFilePersistence::loadState()
{
    QJsonObject paramState;
    ZeraJsonParamsState jsonParamsState(m_jsonParamStructure);
    paramState = cJsonFileLoader::loadJsonFile(m_stateFilePath);
    bool isValidState = checkStateValidity(paramState);
    if(!isValidState) {
        paramState = jsonParamsState.getDefaultJsonState();
        saveState(paramState);
    }
    return paramState;
}

bool JsonStateFilePersistence::saveState(QJsonObject stateObject)
{
    bool wasStored = false;
    if(checkStateValidity(stateObject)){
        wasStored = cJsonFileLoader::storeJsonFile(m_stateFilePath, stateObject);
    }
    return wasStored;
}
