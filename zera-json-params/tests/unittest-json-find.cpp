#include <gtest/gtest.h>

#include "zerajsonhelper.h"

#include "zera-json-find.h"

TEST(TEST_JSON,FIND) {
    // find existing
    QJsonObject jsonFindRaw = ZeraJsonHelper::loadFromQrc("TEST_JSON,FIND");

    QJsonValue value = cJSONFind::findJson(jsonFindRaw, QStringList() << "bool1");
    EXPECT_EQ(value.isBool(), true);
    EXPECT_EQ(value.toBool(), true);

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "number1");
    EXPECT_EQ(value.isDouble(), true);
    EXPECT_EQ(value.toDouble(), 1.0);

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "string1");
    EXPECT_EQ(value.isString(), true);
    EXPECT_EQ(value.toString(), "foo");

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "array1");
    EXPECT_EQ(value.isArray(), true);

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "object1");
    EXPECT_EQ(value.isObject(), true);

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "object1" << "bool2");
    EXPECT_EQ(value.isBool(), true);
    EXPECT_EQ(value.toBool(), true);

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "object1" << "number2");
    EXPECT_EQ(value.isDouble(), true);
    EXPECT_EQ(value.toDouble(), 1.0);

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "object1" << "string2");
    EXPECT_EQ(value.isString(), true);
    EXPECT_EQ(value.toString(), "foo");

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "object1" << "array2");
    EXPECT_EQ(value.isArray(), true);

    // search non existing
    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "foo");
    EXPECT_EQ(value.isNull(), true);

    value = cJSONFind::findJson(jsonFindRaw, QStringList() << "object1" << "foo");
    EXPECT_EQ(value.isNull(), true);
}
