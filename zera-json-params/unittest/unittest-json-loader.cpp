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

TEST(TEST_JSON_LOAD, LOAD_NOT_EXIST_NO_PARSE_ERROR) {
    QJsonParseError jsonError;
    QJsonObject json = cJsonFileLoader::loadJsonFile("foo", &jsonError);
    EXPECT_EQ(jsonError.error, QJsonParseError::NoError);
}

TEST(TEST_JSON_LOAD, LOAD_EXISTING_NO_PARSE_ERROR) {
    QJsonParseError jsonError;
    QJsonObject json = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_JSON_LOAD.json", &jsonError);
    EXPECT_EQ(jsonError.error, QJsonParseError::NoError);
}

TEST(TEST_JSON_LOAD, LOAD_EXISTING_PARSE_ERROR) {
    QJsonParseError jsonError;
    QJsonObject json = cJsonFileLoader::loadJsonFile(":/json-test-invalid-files/TEST_JSON_LOAD_INVALID.json", &jsonError);
    EXPECT_NE(jsonError.error, QJsonParseError::NoError);
}
