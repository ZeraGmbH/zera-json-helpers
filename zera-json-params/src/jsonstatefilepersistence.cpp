#include "jsonstatefilepersistence.h"

#include "zera-jsonfileloader.h"
#include "zera-json-params-state.h"

#include <QFile>
#include <QJsonDocument>

JsonStateFilePersistence::JsonStateFilePersistence()
{

}

void JsonStateFilePersistence::setStateFilePath(const QString& path)
{
    m_stateFilePath=path;
}


void JsonStateFilePersistence::setJsonParamStructure(const QJsonObject& jsonParamStructure)
{
    m_jsonParamStructure=jsonParamStructure;
}

QJsonObject JsonStateFilePersistence::getJsonParamStructure() const
{
    return m_jsonParamStructure;
}

bool JsonStateFilePersistence::checkStateValidity(const QJsonObject &stateObject)
{
    bool isValid=false;
    cZeraJsonParamsState jsonParamsState;
    jsonParamsState.setStructure(m_jsonParamStructure);
    cZeraJsonParamsState::ErrList errList = jsonParamsState.validateJsonState(stateObject);
    if(errList.isEmpty()){
        isValid=true;
    }
    return isValid;
}

QJsonObject JsonStateFilePersistence::loadState()
{
    QJsonObject paramState;
    cZeraJsonParamsState jsonParamsState;

    try{
        jsonParamsState.setStructure(m_jsonParamStructure);
        QJsonObject stateObject = cJsonFileLoader::loadJsonFile(m_stateFilePath);
        bool isValidState=checkStateValidity(stateObject);
        if(!isValidState) {
            throw std::runtime_error("invalid struct");
        }
        paramState = stateObject;

    }catch(std::runtime_error &e){
        paramState= jsonParamsState.createDefaultJsonState();
        saveState(paramState);
    }
    return paramState;
}

void JsonStateFilePersistence::saveState(QJsonObject stateObject)
{
    bool isValidState=checkStateValidity(stateObject);
    if(isValidState){
        cJsonFileLoader::storeJsonFile(m_stateFilePath,stateObject);
    }
}
