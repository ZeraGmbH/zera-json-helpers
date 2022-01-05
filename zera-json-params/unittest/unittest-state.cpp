#include <gtest/gtest.h>

#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"
#include "zera-json-params-state.h"

TEST(TEST_STATE,VALID_ALL_TYPES) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_TRUE(errListStructure.isEmpty());
}

TEST(TEST_STATE,VALID_DEFAULT) {
    ZeraJsonParamsStructure jsonParamStructure;
    jsonParamStructure.setJson(ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES"));

    ZeraJsonParamsState jsonParamState;
    jsonParamState.setStructure(jsonParamStructure.getJson());
    QJsonObject jsonParamDefault = jsonParamState.createDefaultJsonState();
    QJsonObject jsonParamDefaultExpected = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES_DEFAULT");
    EXPECT_EQ(jsonParamDefault, jsonParamDefaultExpected) << "Expected default params do not match";
}

TEST(TEST_STATE,EMPTY_STRUCT) {
    QJsonObject jsonParamDummy;
    jsonParamDummy.insert("dummy", true);
    ZeraJsonParamsState jsonParamState;
    ZeraJsonParamsState::ErrList errList = jsonParamState.validateJsonState(jsonParamDummy);
    ASSERT_EQ(errList.count(), 1);
    EXPECT_EQ(errList[0].m_errType,ZeraJsonParamsState::errorTypes::ERR_INVALID_STRUCTURE);
}

TEST(TEST_STATE,EMPTY_STATE) {
    // Load dummy but working structure
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_TRUE(errListStructure.isEmpty());

    // Valiate empty state & expect empty state errror
    ZeraJsonParamsState jsonParamState;
    jsonParamState.setStructure(jsonParamStructure.getJson());
    ZeraJsonParamsState::ErrList errList = jsonParamState.validateJsonState(QJsonObject());
    ASSERT_EQ(errList.count(), 1);
    EXPECT_EQ(errList[0].m_errType,ZeraJsonParamsState::errorTypes::ERR_EMPTY_STATE);
}

TEST(TEST_STATE,EMPTY_STATE_AND_STRUCT) {
    ZeraJsonParamsState jsonParamState;
    ZeraJsonParamsState::ErrList errList = jsonParamState.validateJsonState(QJsonObject());
    EXPECT_EQ(errList.count(), 2);
}

TEST(TEST_STATE,VALIDATE_DEFAULT) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_TRUE(errListStructure.isEmpty());

    ZeraJsonParamsState jsonParamState;
    jsonParamState.setStructure(jsonParamStructure.getJson());

    QJsonObject jsonParamDefault = jsonParamState.createDefaultJsonState();
    ZeraJsonParamsState::ErrList paramErrList = jsonParamState.validateJsonState(jsonParamDefault);
    EXPECT_EQ(paramErrList.count(), 0) << "Expected default params valid";
}

TEST(TEST_STATE,VALIDATE_TYPE_ERRORS) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_TRUE(errListStructure.isEmpty());

    ZeraJsonParamsState jsonParamState;
    jsonParamState.setStructure(jsonParamStructure.getJson());

    QJsonObject jsonStateWrongTypes = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALIDATE_TYPE_ERRORS");
    ZeraJsonParamsState::ErrList paramErrList = jsonParamState.validateJsonState(jsonStateWrongTypes);
    EXPECT_EQ(paramErrList.count(), 6) << "Expected all params invalid for type error";
}

TEST(TEST_STATE,VALIDATE_LIMIT_ERRORS) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_TRUE(errListStructure.isEmpty());

    ZeraJsonParamsState jsonParamState;
    jsonParamState.setStructure(jsonParamStructure.getJson());

    QJsonObject jsonStateWrongTypes = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALIDATE_LIMIT_ERRORS");
    ZeraJsonParamsState::ErrList paramErrList = jsonParamState.validateJsonState(jsonStateWrongTypes);
    EXPECT_EQ(paramErrList.count(), 3) << "Expected all params invalid for limits";
}
