#include "ApplicationController.h"
#include <QLoggingCategory>

#include "FileNamesContainer.h"


Q_LOGGING_CATEGORY(applicationController, "project.applicationController")

ApplicationController::ApplicationController(QObject *parent)
    : QObject(parent)
{

}

void ApplicationController::startClassifier()
{
#ifdef ENABLED_UI
    _renamingEngine = &RenamingEngine::renamingEngineInstance(_photoDirPath, _schemePattern);
    bool state{_renamingEngine->processRenaming()};
    if(_classifierState != state)
    {
        _classifierState = state;

        switch (_classifierState) {
        case 1:
            _classifierStateToString = QString::fromUtf8(QMetaEnum::fromType<ClassifierState>().valueToKey(0));
            emit classifierStateToStringChanged(_classifierStateToString);
            break;
        default:
            _classifierStateToString = QString::fromUtf8(QMetaEnum::fromType<ClassifierState>().valueToKey(1));
            emit classifierStateToStringChanged(_classifierStateToString);
            break;
        }
    }
    // Fill the data container for the list view
    QStringList fileNames{_renamingEngine->processedFileNames()};
    if(fileNames.isEmpty())
    {
        qCInfo(applicationController)<<QStringLiteral("Can't fill the data container. Because the renaming engin returns an empty list of file names!");
        return;
    }
    FileNamesContainer::fileNamesContainerInstance().fillContainerOnce(fileNames);
#endif
}

void ApplicationController::setPhotoDirPath(QString &dirPath)
{
    FileNamesContainer::fileNamesContainerInstance().clearContainer();

    if(_photoDirPath.compare(dirPath) == 0)
        return;
    _photoDirPath = processDirPath(dirPath);
    _renamingEngine = &RenamingEngine::renamingEngineInstance(_photoDirPath, _schemePattern);
    _renamingEngine->setDirPath(_photoDirPath);
    QDir dir(_photoDirPath);
    dir.setSorting(QDir::Unsorted);
    QStringList filters;
    filters << "*.Jpg";
    dir.setNameFilters(filters);
    foreach (auto &entry, dir.entryInfoList()) {
        QFileInfo info{entry};
        FileNamesContainer::fileNamesContainerInstance().fillContainer(info.absoluteFilePath());
    }

    emit photoDirPathChanged(_photoDirPath);
}

void ApplicationController::setSchemePattern(const QString &scheme)
{
    if(_schemePattern.compare(scheme) == 0)
        return;

    _schemePattern = scheme;
    _renamingEngine = &RenamingEngine::renamingEngineInstance(_photoDirPath, _schemePattern);
    _renamingEngine->setShemePattern(_schemePattern);
    emit schemePatternChanged(scheme);
}

QString ApplicationController::processDirPath(QString &dirPath)
{
    QString path{dirPath.remove(0,8)};
    return path;
}
