#include <gtest/gtest.h>
#include <QTemporaryFile>
#include <QJsonDocument>

#include "jsonstatefilepersistence.h"
#include "zera-jsonfileloader.h"
#include "zera-json-params-state.h"


TEST(TEST_JSON_PERSISTENCE, SAVE_INVALID_STATE) {
    JsonStateFilePersistence fileLoader;
    QTemporaryFile file;
    file.open();

    cZeraJsonParamsState defaultStateGenerator;
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    defaultStateGenerator.setStructure(stateStruct);
    QJsonObject correctStateDefault=defaultStateGenerator.createDefaultJsonState();

    file.write(QJsonDocument(correctStateDefault).toJson());
    file.flush();

    fileLoader.setStateFilePath(file.fileName());
    fileLoader.setJsonParamStructure(stateStruct);
    fileLoader.saveState(QJsonObject());

    QJsonObject state = cJsonFileLoader::loadJsonFile(file.fileName());

    EXPECT_EQ(state,correctStateDefault);
}

TEST(TEST_JSON_PERSISTENCE, SAVE_VALID_STATE) {
    JsonStateFilePersistence fileLoader;
    QTemporaryFile file;
    file.open();

    cZeraJsonParamsState defaultStateGenerator;
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    defaultStateGenerator.setStructure(stateStruct);
    QJsonObject correctStateDefault=defaultStateGenerator.createDefaultJsonState();

    file.write(QJsonDocument(correctStateDefault).toJson());
    file.flush();

    fileLoader.setStateFilePath(file.fileName());
    fileLoader.setJsonParamStructure(stateStruct);
    QJsonObject stateToWrite;
    stateToWrite["foo"]=5;
    fileLoader.saveState(stateToWrite);

    QJsonObject state = cJsonFileLoader::loadJsonFile(file.fileName());

    EXPECT_EQ(state,stateToWrite);

}

TEST(TEST_JSON_PERSISTENCE, LOAD_INVALID_FILE) {
    JsonStateFilePersistence fileLoader;
    fileLoader.setStateFilePath(":/json-test-files/TEST_PERSISTENCE,LOAD_INVALID_FILE.json");
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    fileLoader.setJsonParamStructure(stateStruct);

    cZeraJsonParamsState defaultStateGenerator;
    defaultStateGenerator.setStructure(stateStruct);

    QJsonObject persistentState=fileLoader.loadState();

    QJsonObject correctStateDefault=defaultStateGenerator.createDefaultJsonState();
    EXPECT_EQ(persistentState,correctStateDefault);
}

TEST(TEST_JSON_PERSISTENCE, LOAD_NOTEXIST_FILE) {
    JsonStateFilePersistence fileLoader;
    QTemporaryFile file;
    file.open();
    fileLoader.setStateFilePath(file.fileName());
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    QJsonObject state = cJsonFileLoader::loadJsonFile(file.fileName());
    fileLoader.setJsonParamStructure(stateStruct);

    cZeraJsonParamsState defaultStateGenerator;
    defaultStateGenerator.setStructure(stateStruct);

    QJsonObject correctStateDefault=defaultStateGenerator.createDefaultJsonState();

    EXPECT_NE(state,correctStateDefault);
    fileLoader.loadState();
    state = cJsonFileLoader::loadJsonFile(file.fileName());
    EXPECT_EQ(state,correctStateDefault);
}

TEST(TEST_JSON_PERSISTENCE, LOAD_VALID_FILE) {
    JsonStateFilePersistence fileLoader;
    fileLoader.setStateFilePath(":/json-test-files/TEST_PERSISTENCE,LOAD_VALID_FILE.json");
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    fileLoader.setJsonParamStructure(stateStruct);

    QJsonObject persistentState=fileLoader.loadState();

    EXPECT_EQ(persistentState["foo"],5);
}

