#include "zera-jsonfileloader.h"
#include <gtest/gtest.h>
#include <QTemporaryFile>

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

TEST(TEST_JSON_LOAD, STORE_AND_COMPARE) {
    QJsonObject json = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_JSON_LOAD.json");
    QTemporaryFile tempFile;
    tempFile.open();
    EXPECT_TRUE(cJsonFileLoader::storeJsonFile(tempFile.fileName(), json));
    QJsonObject jsonStored = cJsonFileLoader::loadJsonFile(tempFile.fileName());
    EXPECT_EQ(json, jsonStored);
}
