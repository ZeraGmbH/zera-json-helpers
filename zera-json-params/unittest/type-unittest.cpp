#include "gtest/gtest.h"

#include <QJsonDocument>
#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"

QJsonObject initFloatObject(){
    QJsonObject retVal;

    QByteArray jsonStructureData(
        "{"
            "\"params\": {"
                "\"data\": {"
                    "\"type\": \"float\","
                    "\"min\": 0.0,"
                    "\"max\": 10.0,"
                    "\"decimals\": 3,"
                    "\"default\": 10.0"
                "}"
            "}"
        "}"
    );

    retVal = QJsonDocument::fromJson(jsonStructureData).object();
    return retVal;
}

QJsonObject initIntObject(){
    QJsonObject retVal;

    QByteArray jsonStructureData(
        "{"
            "\"params\": {"
                "\"data\": {"
                    "\"type\": \"int\","
                    "\"min\": 0,"
                    "\"max\": 10,"
                    "\"default\": 0"
                "}"
            "}"
        "}"
    );

    retVal = QJsonDocument::fromJson(jsonStructureData).object();
    return retVal;
}

QJsonObject initBoolObject(){
    QJsonObject retVal;

    QByteArray jsonStructureData(
        "{"
            "\"params\": {"
                "\"data\": {"
                    "\"type\": \"bool\","
                    "\"default\": false"
                "}"
            "}"
        "}"
    );

    retVal = QJsonDocument::fromJson(jsonStructureData).object();
    return retVal;
}

QJsonObject initEmptyObject(){
    QJsonObject retVal;

    QByteArray jsonStructureData(
        "{"
            "\"params\": {"
                "\"data\": {"
                "}"
            "}"
        "}"
    );

    retVal = QJsonDocument::fromJson(jsonStructureData).object();
    return retVal;
}


TEST(SELF_TEST,NO_DATA){
    GTEST_SKIP();
    QByteArray emptyArr;
    ASSERT_TRUE(ZeraJsonHelper::checkJsonObject(QJsonObject()));
}

TEST(TEST_GENERALTYPE,TYPE_MISSING){
    QJsonObject jsonStructureRaw = initEmptyObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","default"}, "false");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_GENERALTYPE,INVALID_TYPE){
    QJsonObject jsonStructureRaw = initEmptyObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","type"}, "foo");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","default"}, "false");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_FLOAT,VALID){
    QJsonObject jsonStructureRaw = initFloatObject();
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.empty(),true);
}

TEST(TEST_FLOAT,INVALID_PROPERTY){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","foo"}, "bar");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_FLOAT,MISSING_MIN){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::removeJsonItem(jsonStructureRaw,{"params","data","min"});
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_FLOAT,MISSING_MAX){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::removeJsonItem(jsonStructureRaw,{"params","data","max"});
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_FLOAT,DECIMALS_MISSING){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::removeJsonItem(jsonStructureRaw,{"params","data","decimals"});
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_FLOAT,DEFAULT_MISSING){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::removeJsonItem(jsonStructureRaw,{"params","data","default"});
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_FLOAT,MIN_GT_MAX){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","min"}, 10.0);
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","max"}, 0);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),2);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_FLOAT,DATA_TYPE_MIN_MAX_DEFAULT_DECIMMALS){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","min"}, "");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","max"}, "");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","default"}, "");
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","decimals"}, "");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),4);
    for(auto err : errListStructure){
        EXPECT_EQ(err.m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
    }
}

TEST(TEST_FLOAT,DECIMALS_OUT_OF_RANGE){
    QJsonObject jsonStructureRaw = initFloatObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","decimals"}, 11);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_INT,VALID){
    QJsonObject jsonStructureRaw = initIntObject();
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.empty(),true);
}

TEST(TEST_INT,INVALID_TYPE_PROPERTY){
    QJsonObject jsonStructureRaw = initIntObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","decimals"}, 3);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_BOOL,VALID){
    QJsonObject jsonStructureRaw = initBoolObject();
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.empty(),true);
}

TEST(TEST_BOOL,INVALID_TYPE_PROPERTY){
    QJsonObject jsonStructureRaw = initBoolObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","defualt"}, 230);
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}

TEST(TEST_BOOL,DEFAULT_INVALID){
    QJsonObject jsonStructureRaw = initBoolObject();
    jsonStructureRaw=ZeraJsonHelper::manipulateJson(jsonStructureRaw,{"params","data","defualt"}, "foo");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    ZeraJsonHelper::checkJsonObject(jsonStructureRaw);
    EXPECT_EQ(errListStructure.length(),1);
    EXPECT_EQ(errListStructure.first().m_errType,cZeraJsonParamsStructure::errorTypes::ERR_INVALID_PARAM_DEFINITION);
}


