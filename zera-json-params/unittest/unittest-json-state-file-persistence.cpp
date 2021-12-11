#include <gtest/gtest.h>
#include <QTemporaryFile>
#include <QJsonDocument>

#include "jsonstatefilepersistence.h"
#include "zera-jsonfileloader.h"
#include "zera-json-params-state.h"


TEST(TEST_JSON_PERSISTENCE, SAVE_INVALID_STATE) {
    QString fileName;
    {
        QTemporaryFile file;
        file.open();
        fileName = file.fileName();
    }

    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    JsonStateFilePersistence persistentStateHelper;
    persistentStateHelper.setJsonParamStructure(stateStruct);
    persistentStateHelper.setStateFilePath(fileName);

    QJsonObject invalidState;
    invalidState.insert("invalid_foo", "foo");
    persistentStateHelper.saveState(invalidState);
    EXPECT_FALSE(QFile::exists(fileName));
}

TEST(TEST_JSON_PERSISTENCE, SAVE_VALID_STATE) {
    JsonStateFilePersistence persistentStateHelper;
    QTemporaryFile file;
    file.open();

    cZeraJsonParamsState defaultStateGenerator;
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    defaultStateGenerator.setStructure(stateStruct);

    QJsonObject correctStateDefault = defaultStateGenerator.createDefaultJsonState();

    file.write(QJsonDocument(correctStateDefault).toJson());
    file.flush();

    persistentStateHelper.setStateFilePath(file.fileName());
    persistentStateHelper.setJsonParamStructure(stateStruct);
    QJsonObject stateToWrite;
    stateToWrite["foo"] = 5;
    persistentStateHelper.saveState(stateToWrite);

    QJsonObject state = cJsonFileLoader::loadJsonFile(file.fileName());
    EXPECT_EQ(state, stateToWrite);

}

TEST(TEST_JSON_PERSISTENCE, LOAD_INVALID_FILE) {
    JsonStateFilePersistence persistentStateHelper;
    persistentStateHelper.setStateFilePath(":/json-test-files/TEST_PERSISTENCE,LOAD_INVALID_FILE.json");
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    persistentStateHelper.setJsonParamStructure(stateStruct);

    cZeraJsonParamsState defaultStateGenerator;
    defaultStateGenerator.setStructure(stateStruct);

    QJsonObject jsonState = persistentStateHelper.loadState();

    QJsonObject correctStateDefault = defaultStateGenerator.createDefaultJsonState();
    EXPECT_EQ(jsonState, correctStateDefault);
}

TEST(TEST_JSON_PERSISTENCE, LOAD_NOTEXIST_FILE) {
    JsonStateFilePersistence persistentStateHelper;
    QTemporaryFile file;
    file.open();
    persistentStateHelper.setStateFilePath(file.fileName());
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    QJsonObject state = cJsonFileLoader::loadJsonFile(file.fileName());
    persistentStateHelper.setJsonParamStructure(stateStruct);

    cZeraJsonParamsState defaultStateGenerator;
    defaultStateGenerator.setStructure(stateStruct);

    QJsonObject correctStateDefault=defaultStateGenerator.createDefaultJsonState();

    EXPECT_NE(state,correctStateDefault);
    persistentStateHelper.loadState();
    state = cJsonFileLoader::loadJsonFile(file.fileName());
    EXPECT_EQ(state,correctStateDefault);
}

TEST(TEST_JSON_PERSISTENCE, LOAD_VALID_FILE) {
    JsonStateFilePersistence persistentStateHelper;
    persistentStateHelper.setStateFilePath(":/json-test-files/TEST_PERSISTENCE,LOAD_VALID_FILE.json");
    QJsonObject stateStruct = cJsonFileLoader::loadJsonFile(":/json-test-files/TEST_PERSISTENCE_STRUCTURE.json");
    persistentStateHelper.setJsonParamStructure(stateStruct);

    QJsonObject jsonState = persistentStateHelper.loadState();
    EXPECT_EQ(jsonState["foo"], 5);
}

