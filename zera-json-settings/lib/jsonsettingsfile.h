#ifndef JSONSETTINGSFILE_H
#define JSONSETTINGSFILE_H

#include <QObject>

class JsonSettingsFilePrivate;

class JsonSettingsFile : public QObject
{
    Q_OBJECT
public:
    explicit JsonSettingsFile(QObject *parent = nullptr);
    static JsonSettingsFile *getInstance();
    bool loadFromStandardLocation(const QString &fileName);
    void setAutoWriteBackEnabled(bool autoWriteBackEnabled=true);

    Q_INVOKABLE QString getOption(const QString &key, const QString &valueDefault);
    Q_INVOKABLE bool setOption(const QString &key, const QString &value);
signals:
    void settingsSaveRequest(JsonSettingsFile *settingsFile);

private:
    bool loadFromFile(const QString &filePath);
    void saveToFile(const QString &filePath, bool overwrite=false);
    QString getCurrentFilePath();
    bool hasOption(const QString &key);

    JsonSettingsFilePrivate *d_ptr;

    static JsonSettingsFile *s_globalSettings;

    Q_DECLARE_PRIVATE(JsonSettingsFile)
    Q_DISABLE_COPY(JsonSettingsFile)
};

#endif // JSONSETTINGSFILE_H
