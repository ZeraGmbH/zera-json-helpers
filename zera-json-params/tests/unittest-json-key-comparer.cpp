#include <gtest/gtest.h>

#include "zera-json-keycomparer.h"
#include "zerajsonhelper.h"


TEST(TEST_KEY_COMPARE, COMPARE_BOTH_EMPTY) {
    QJsonObject jsonEmpty;
    EXPECT_TRUE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonEmpty, jsonEmpty));
}

TEST(TEST_KEY_COMPARE, COMPARE_DIFF_BASE_VAL) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    jsonModif.remove("bool1");
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonOrig, jsonModif));
    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, COMPARE_DIFF_BASE_OBJ) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    jsonModif.remove("object1");
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonOrig, jsonModif));
    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, COMPARE_DIFF_SUB_VAL) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    QJsonObject subObj = jsonModif["object1"].toObject();
    subObj.remove("bool2");
    jsonModif["object1"] = subObj;
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonOrig, jsonModif));
    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, COMPARE_DIFF_SUB_OBJ) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    QJsonObject subObj = jsonModif["object1"].toObject();
    subObj.remove("object2");
    jsonModif["object1"] = subObj;
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonOrig, jsonModif));
    EXPECT_FALSE(ZeraJsonKeyComparer::haveJsonsSameKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, COMPARE_SAME) {
    QJsonObject json = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    EXPECT_TRUE(ZeraJsonKeyComparer::haveJsonsSameKeys(json, json));
}


TEST(TEST_KEY_COMPARE, CONTAINS_BOTH_EMPTY) {
    QJsonObject jsonEmpty;
    EXPECT_TRUE(ZeraJsonKeyComparer::containsAllKeys(jsonEmpty, jsonEmpty));
}

TEST(TEST_KEY_COMPARE, CONTAINS_DIFF_BASE_VAL) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    jsonModif.remove("bool1");
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::containsAllKeys(jsonOrig, jsonModif));
    EXPECT_TRUE(ZeraJsonKeyComparer::containsAllKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, CONTAINS_DIFF_BASE_OBJ) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    jsonModif.remove("object1");
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::containsAllKeys(jsonOrig, jsonModif));
    EXPECT_TRUE(ZeraJsonKeyComparer::containsAllKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, CONTAINS_DIFF_SUB_VAL) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    QJsonObject subObj = jsonModif["object1"].toObject();
    subObj.remove("bool2");
    jsonModif["object1"] = subObj;
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::containsAllKeys(jsonOrig, jsonModif));
    EXPECT_TRUE(ZeraJsonKeyComparer::containsAllKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, CONTAINS_DIFF_SUB_OBJ) {
    QJsonObject jsonOrig = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    QJsonObject jsonModif = jsonOrig;
    QJsonObject subObj = jsonModif["object1"].toObject();
    subObj.remove("object2");
    jsonModif["object1"] = subObj;
    ASSERT_NE(jsonOrig, jsonModif);

    EXPECT_FALSE(ZeraJsonKeyComparer::containsAllKeys(jsonOrig, jsonModif));
    EXPECT_TRUE(ZeraJsonKeyComparer::containsAllKeys(jsonModif, jsonOrig));
}

TEST(TEST_KEY_COMPARE, CONTAINS_SAME) {
    QJsonObject json = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");
    EXPECT_TRUE(ZeraJsonKeyComparer::containsAllKeys(json, json));
}
