#include "gtest/gtest.h"

#include <QJsonDocument>
#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"

// negative: empty structure (is not a template test exactly...)
TEST(TEST_TEMPLATE,EMPTY){
    QJsonObject jsonStructureRaw;
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 1) << "Expect one error for empty structure";
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION) << "Expect ERR_INVALID_PARAM_DEFINITION";
    }
}

// positive: valid template
TEST(TEST_TEMPLATE,VALID){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true) << "Expect no errors";
    QJsonObject jsonStructure = jsonParamStructure.getJson();

}

// positive: valid template / resolve one parameter
TEST(TEST_TEMPLATE,VALID_CONTENT){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true) << "Expect no errors";
    QJsonObject jsonStructure = jsonParamStructure.getJson();
    int elemCount = jsonStructure.count();
    // Important note: While debugging this the param 'param_from_template' is displayed as 'param_fro'!!!
    // But our test below passes
    EXPECT_EQ(elemCount, 1) << "Expect one entry 'params";
    if(elemCount == 1) {
        QJsonObject::const_iterator iterOnFirst = jsonStructure.begin();
        bool isObject = iterOnFirst.value().isObject();
        EXPECT_EQ(isObject, true) << "Expect 'params' a json object";
        if(isObject) {
            QJsonObject subObj = iterOnFirst.value().toObject();
            int subElemCount = subObj.count();
            EXPECT_EQ(subElemCount, 1) << "Expect one sub entry 'param_from_template";
            if(elemCount == 1) {
                QJsonObject::const_iterator itersubObj = subObj.begin();
                EXPECT_EQ(itersubObj.key(), "param_from_template") << "Expect 'param_from_template' but found" << qPrintable(itersubObj.key());
            }
        }
    }
    // Check whole content
    QJsonObject jsonStructureExpected = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT_RESOLVE_EXPECTED");
    EXPECT_EQ(jsonStructureExpected, jsonStructure) << "Expected resolved structuture does not match";
}

// positive: valid template / resolve one parameter
TEST(TEST_TEMPLATE,VALID_CONTENT_NESTED){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT_NESTED");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true) << "Expect no errors";
    QJsonObject jsonStructure = jsonParamStructure.getJson();
    // Check whole content
    QJsonObject jsonStructureExpected = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT_NESTED_EXPECTED");
    EXPECT_EQ(jsonStructureExpected, jsonStructure) << "Expected resolved nested structuture does not match";
}

// negative: check extraction of template indirectly by invalid parameter: min > max & default > max
TEST(TEST_TEMPLATE,MIN_LARGER_MAX){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,MIN_LARGER_MAX");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),2);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_TEMPLATE_DEFINITION);
    }
}

// negative: check extraction of template indirectly by invalid parameter: type
TEST(TEST_TEMPLATE,INVALID_TYPE){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,INVALID_TYPE");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_TEMPLATE_DEFINITION);
    }
}

// we are not testing all combinations of incorrect parameter definitions here: it is done at parameter test

