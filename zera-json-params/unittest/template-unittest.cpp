#include "gtest/gtest.h"

#include <QJsonDocument>
#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"

QJsonObject initEmptyTemplateObject(){
    QJsonObject retVal;

    QByteArray jsonStructureData(
        "{"
            "\"param_templates\": {"
                "\"data\" : {"
                "}"
            "}"
        "}"
    );

    retVal = QJsonDocument::fromJson(jsonStructureData).object();
    return retVal;
}


TEST(TEST_TEMPLATE,VAILD){
    QJsonObject jsonStructureRaw = initEmptyTemplateObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","type"}, "bool");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","default"}, true);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.empty(),true);
}

TEST(TEST_TEMPLATE,INVALID_TYPE1){
    QJsonObject jsonStructureRaw = initEmptyTemplateObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","type"}, "undefined");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","min"}, 0.001);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","max"}, 20.0);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","decimals"}, 3);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","default"}, 230);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),2);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_TEMPLATE_DEFINITION);
    }
}

TEST(TEST_TEMPLATE,MIN_AND_DEFAULT_GT_MAX){
    QJsonObject jsonStructureRaw = initEmptyTemplateObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","type"}, "float");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","min"}, 0);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","max"}, -10);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","decimals"}, 3);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","default"}, 230);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),2);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_TEMPLATE_DEFINITION);
    }
}

TEST(TEST_TEMPLATE,INVALID_MIN){
    QJsonObject jsonStructureRaw = initEmptyTemplateObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","type"}, "float");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","min"}, "abc");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","max"}, 359.999);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"param_templates","data","decimals"}, 3);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_TEMPLATE_DEFINITION);
    }
}
