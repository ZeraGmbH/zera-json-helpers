#include "gtest/gtest.h"

#include <QJsonDocument>
#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"

TEST(TEST_TEMPLATE,VALID){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true) << "Expect no errors";
    QJsonObject jsonStructure = jsonParamStructure.getJson();
}

TEST(TEST_TEMPLATE,INVALID_LINK) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,INVALID_LINK");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    // We expect:
    // 1. link
    // 2. type missing
    // 3. invalid property
    ASSERT_EQ(errListStructure.length(), 3);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}


TEST(TEST_TEMPLATE,VALID_CONTENT){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true);
}

TEST(TEST_TEMPLATE,VALID_CONTENT_RESOLVE_EXPECTED){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    QJsonObject jsonStructure = jsonParamStructure.getJson();

    QJsonObject jsonStructureExpected = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT_RESOLVE_EXPECTED");
    EXPECT_EQ(jsonStructureExpected, jsonStructure);
}

TEST(TEST_TEMPLATE,VALID_CONTENT_NESTED){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT_NESTED");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_TRUE(errListStructure.isEmpty());
    QJsonObject jsonStructure = jsonParamStructure.getJson();

    QJsonObject jsonStructureExpected = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,VALID_CONTENT_NESTED_EXPECTED");
    EXPECT_EQ(jsonStructureExpected, jsonStructure);
}

TEST(TEST_TEMPLATE,MIN_LARGER_MAX){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,MIN_LARGER_MAX");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    // min > max & default > max
    ASSERT_EQ(errListStructure.length(), 2);
    EXPECT_EQ(errListStructure[0].m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_TEMPLATE_DEFINITION);
    EXPECT_EQ(errListStructure[0].m_errType, errListStructure[1].m_errType);
}

TEST(TEST_TEMPLATE,INVALID_TYPE){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,INVALID_TYPE");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_EQ(errListStructure.length(), 1);
    EXPECT_EQ(errListStructure[0].m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_TEMPLATE_DEFINITION);
}

// we are not testing all combinations of incorrect parameter definitions here: it is done at parameter test

