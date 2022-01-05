#include <gtest/gtest.h>

#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"

// negative: invalid link to template
TEST(TEST_TEMPLATE,INVALID_LINK) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_TEMPLATE,INVALID_LINK");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    // We expect:
    // 1. link
    // 2. type missing
    // 3. invalid property
    EXPECT_EQ(errListStructure.length(), 3);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// positive: all parameter types / check for contents untouched
TEST(TEST_PARAMS,VALID) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,VALID");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 0) << "Expect no errors";
    QJsonObject jsonStructure = jsonParamStructure.getJson();
    EXPECT_EQ(jsonStructureRaw, jsonStructure) << "Expect no modifications on json";
}

// negative: type missing
TEST(TEST_PARAMS,TYPE_MISSING) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,TYPE_MISSING");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 1);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: type invalid
TEST(TEST_PARAMS,TYPE_INVALID) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,TYPE_INVALID");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 1);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: invalid param property
TEST(TEST_PARAMS,PROPERTY_INVALID) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,PROPERTY_INVALID");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 1);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: default missing
TEST(TEST_PARAMS,DEFAULT_MISSING) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,DEFAULT_MISSING");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: bool invalid default value type
TEST(TEST_PARAMS,BOOL_INVALID_TYPE_DEFAULT) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,BOOL_INVALID_TYPE_DEFAULT");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: float invalid default value type
TEST(TEST_PARAMS,FLOAT_INVALID_TYPE_DEFAULT) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,FLOAT_INVALID_TYPE_DEFAULT");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: min/max missing
TEST(TEST_PARAMS,MIN_MAX_MISSING) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,MIN_MAX_MISSING");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 2);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: min/max invalid
TEST(TEST_PARAMS,MIN_MAX_INVALID) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,MIN_MAX_INVALID");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 8);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: min/max invalid
TEST(TEST_PARAMS,MIN_MAX_DEFAULT_LIMITS) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,MIN_MAX_DEFAULT_LIMITS");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 3+1); // min larger max throws default > max too
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: float decimals invalid
TEST(TEST_PARAMS,FLOAT_INVALID_DECIMALS) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,FLOAT_INVALID_DECIMALS");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 8);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

// negative: string invalid type default
TEST(TEST_PARAMS,STRING_INVALID_TYPE_DEFAULT) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_PARAMS,STRING_INVALID_TYPE_DEFAULT");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.setJson(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(), 4);
    for(auto err : errListStructure) {
        EXPECT_EQ(err.m_errType, cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}




