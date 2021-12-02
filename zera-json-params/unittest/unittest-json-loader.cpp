#include <gtest/gtest.h>

#include "zera-jsonfileloader.h"

TEST(TEST_JSON_LOAD, LOAD_NOT_EXISTS) {
    QJsonObject json = cJsonFileLoader::loadJsonFile("foo");
    EXPECT_TRUE(json.isEmpty());
}

TEST(TEST_JSON_LOAD, LOAD_EXISTING) {
    QJsonObject json = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_JSON_LOAD.json");
    EXPECT_FALSE(json.isEmpty());
    EXPECT_EQ(json["boolVal"], true);
    EXPECT_EQ(json["numVal"], 10);
    EXPECT_EQ(json["strVal"], "foo");
}
