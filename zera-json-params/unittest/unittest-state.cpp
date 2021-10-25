#include <gtest/gtest.h>

#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"
#include "zera-json-params-state.h"

// positive: valid template / creete and check default
TEST(TEST_STATE,VALID_ALL_TYPES){
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true) << "Expect no errors";
    if(errListStructure.isEmpty()) {
        cZeraJsonParamsState jsonParamState;
        jsonParamState.setStructure(jsonParamStructure.jsonStructure());
        QJsonObject jsonParamDefault = jsonParamState.createDefaultJsonState();
        QJsonObject jsonParamDefaultExpected = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES_DEFAULT");
        EXPECT_EQ(jsonParamDefaultExpected, jsonParamDefaultExpected) << "Expected default params do not match";
    }
}

