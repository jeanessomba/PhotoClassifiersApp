#pragma once

#include <QObject>
#include <QQmlEngine>
#include "RenamingEngine.h"

class ApplicationController: public QObject
{
    Q_OBJECT
    // Exposed properties to QML
    Q_PROPERTY(QString classifierStateToString READ classifierStateToString NOTIFY classifierStateToStringChanged)
    Q_PROPERTY(QString photoDirPath READ photoDirPath WRITE setPhotoDirPath NOTIFY photoDirPathChanged)
    Q_PROPERTY(QString schemePattern READ schemePattern WRITE setSchemePattern NOTIFY schemePatternChanged)

public:
    enum class ClassifierState
    {
        Successful = 0,
        Failed,
        Waiting
    };
    Q_ENUM(ClassifierState)

    explicit ApplicationController(QObject *parent = nullptr);

    Q_INVOKABLE void startClassifier();

    QString classifierStateToString()const{ return _classifierStateToString
                ; }

    QString photoDirPath()const{ return _photoDirPath; }

    QString schemePattern()const{ return _schemePattern; }

    void setPhotoDirPath(QString &dirPath);

    void setSchemePattern(const QString &scheme);

signals:
    void classifierStateToStringChanged(const QString &classifierState);
    void photoDirPathChanged(const QString &dirPath);
    void schemePatternChanged(const QString &scheme);

protected:
    // Removes "file:///" from file:///C:/Users/...
    QString processDirPath(QString &dirPath);
    // State should be true, when classifier successfully done
    QString _classifierStateToString{QString::fromUtf8(QMetaEnum::fromType<ClassifierState>().valueToKey(2))};
    bool _classifierState{false};
    QString _photoDirPath;
    // The renaming engine needs this scheme for the classification order
    QString _schemePattern;
    RenamingEngine *_renamingEngine{nullptr};
};

static QObject *appControllerProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    ApplicationController *appController = new ApplicationController();
    return appController;
}
