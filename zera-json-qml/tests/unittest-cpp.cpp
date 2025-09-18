#include <gtest/gtest.h>
#include <QDir>
#include <QJsonDocument>
#include <declarativejsonitem.h>
#include "../../zera-json-params/tests/zerajsonhelper.h"

// positive in out same
TEST(TEST_CPP,TYPE_LOAD_UNLOAD_COMPARE) {
    QJsonObject jsonOrigData = ZeraJsonHelper::loadFromQrc("TEST_CPP,TYPE_LOAD_UNLOAD_COMPARE");
    DeclarativeJsonItem declarativeJsonItem;
    declarativeJsonItem.fromJson(jsonOrigData);
    QJsonObject jsonReturnedData = declarativeJsonItem.toJson();
    EXPECT_EQ(jsonOrigData, jsonReturnedData);
}

// positive: check if double is not casted to int (by QVariant magic)
TEST(TEST_CPP, NO_UNWANTED_INT_CAST) {
    QJsonObject jsonObj;
    QString strKey = "testInt";
    jsonObj.insert(strKey, 1);
    DeclarativeJsonItem declarativeJsonItem;
    declarativeJsonItem.fromJson(jsonObj);
    double newValue = 1.001;
    declarativeJsonItem[strKey] = newValue;
    QJsonObject jsonReturnedData = declarativeJsonItem.toJson();
    EXPECT_EQ(jsonReturnedData[strKey], newValue);
}
