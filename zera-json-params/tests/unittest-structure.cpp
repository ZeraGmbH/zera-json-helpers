#include <gtest/gtest.h>

#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"

TEST(TEST_STRUCTURE,EMPTY){
    QJsonObject jsonStructureRaw;
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_EQ(errListStructure.length(), 1) << "Expect one error for empty structure";
    EXPECT_EQ(errListStructure[0].m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION) << "Expect ERR_INVALID_PARAM_DEFINITION";
}


TEST(TEST_STRUCTURE,VALID_STRUCURE) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,VALID_STRUCURE");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_TRUE(errListStructure.isEmpty());

    QJsonObject jsonStructure = jsonParamStructure.getJson();
    EXPECT_EQ(jsonStructureRaw, jsonStructure) << "Expect no modifications on json";
}

TEST(TEST_STRUCTURE,TYPE_MISSING) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,TYPE_MISSING");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_EQ(errListStructure.length(), 1);
    EXPECT_EQ(errListStructure[0].m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

// negative: type invalid
TEST(TEST_STRUCTURE,TYPE_INVALID) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,TYPE_INVALID");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_EQ(errListStructure.length(), 1);
    EXPECT_EQ(errListStructure[0].m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

// negative: invalid param property
TEST(TEST_STRUCTURE,PROPERTY_INVALID) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,PROPERTY_INVALID");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    ASSERT_EQ(errListStructure.length(), 1);
    EXPECT_EQ(errListStructure[0].m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

// negative: default missing
TEST(TEST_STRUCTURE,DEFAULT_MISSING) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,DEFAULT_MISSING");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: bool invalid default value type
TEST(TEST_STRUCTURE,BOOL_INVALID_TYPE_DEFAULT) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,BOOL_INVALID_TYPE_DEFAULT");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: float invalid default value type
TEST(TEST_STRUCTURE,FLOAT_INVALID_TYPE_DEFAULT) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,FLOAT_INVALID_TYPE_DEFAULT");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: min/max missing
TEST(TEST_STRUCTURE,MIN_MAX_MISSING) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,MIN_MAX_MISSING");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 2);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: min/max invalid
TEST(TEST_STRUCTURE,MIN_MAX_INVALID) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,MIN_MAX_INVALID");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 8);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: min/max invalid
TEST(TEST_STRUCTURE,MIN_MAX_DEFAULT_LIMITS) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,MIN_MAX_DEFAULT_LIMITS");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 3+1); // min larger max throws default > max too
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: float decimals invalid
TEST(TEST_STRUCTURE,FLOAT_INVALID_DECIMALS) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,FLOAT_INVALID_DECIMALS");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 8);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: string invalid type default
TEST(TEST_STRUCTURE,STRING_INVALID_TYPE_DEFAULT) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STRUCTURE,STRING_INVALID_TYPE_DEFAULT");
    ZeraJsonParamsStructure jsonParamStructure;
    ZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, ZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}




