#include <gtest/gtest.h>
#include <QDir>
#include <QJsonDocument>
#include <declarativejsonitem.h>
#include "../../zera-json-params/unittest/zerajsonhelper.h"

// positive in out same
TEST(TEST_CPP,TYPE_LOAD_UNLOAD_COMPARE) {
    QJsonObject jsonOrigData = ZeraJsonHelper::loadFromQrc("TEST_CPP,TYPE_LOAD_UNLOAD_COMPARE");
    DeclarativeJsonItem declarativeJsonItem;
    declarativeJsonItem.fromJson(jsonOrigData);
    QJsonObject jsonReturnedData = declarativeJsonItem.toJson();
    EXPECT_EQ(jsonOrigData, jsonReturnedData);
}
