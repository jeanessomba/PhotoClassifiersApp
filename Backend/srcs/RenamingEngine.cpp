#include "RenamingEngine.h"
#include <QLoggingCategory>


Q_LOGGING_CATEGORY(renamingEngine, "project.renamingEngine")

RenamingEngine::RenamingEngine(const QString &dirPath, const QString &schemePattern, QObject *parent)
    : QObject(parent), _scheme(schemePattern), _dirPath(dirPath)
{
}

RenamingEngine &RenamingEngine::renamingEngineInstance(const QString &dirPath, const QString &scheme)
{
    static RenamingEngine renamingEngine(dirPath, scheme);
    return renamingEngine;
}

QString RenamingEngine::shemePattern() const
{
    return _scheme;
}

void RenamingEngine::setShemePattern(const QString &newSchemePattern)
{
    _scheme = newSchemePattern;
}

void RenamingEngine::setDirPath(const QString &dirPath)
{
    _dirPath = dirPath;
}

bool RenamingEngine::processRenaming(const QVector<PhotoObject> &photos)
{
    bool result{processScheme()};

    if(!result)
    {
        qCCritical(renamingEngine)<<QStringLiteral("Fail to parse the scheme of the Renaming engine!");
        return result;
    }
#ifdef ENABLED_UI
    Q_UNUSED(photos)
    _filePaths.clear();
    QDir dir(_dirPath);
    dir.setSorting(QDir::Unsorted);
    QStringList filters;
    filters << "*.png" << "*.Jpg";
    dir.setNameFilters(filters);
    QString path;
    int pos = 0;
    foreach (auto &entry, dir.entryInfoList()) {
        QFileInfo info{entry};
        _filePaths.append(info.absoluteFilePath());
    }
    // To be continue... for the UI case
#else

    QString newSchemeForPhotos("%1_%2_%3");

    foreach (auto &photo, photos) {
        switch (_namingPattern) {
        case NamingPattern::NameDateTime:
            newSchemeForPhotos.arg(photo.phName()).arg(photo.phDate().toString("yyyy-MM-dd"))
                    .arg(photo.phTime().toString("hh:mm")).append(photo.phFormat());
            break;
        case NamingPattern::NameTimeDate:
            newSchemeForPhotos.arg(photo.phName()).arg(photo.phTime().toString("hh:mm"))
                    .arg(photo.phDate().toString("yyyy-MM-dd")).append(photo.phFormat());
            break;
        case NamingPattern::DateTimeName:
            newSchemeForPhotos.arg(photo.phDate().toString("yyyy-MM-dd")).arg(photo.phTime().toString("hh:mm"))
                    .arg(photo.phName()).append(photo.phFormat());
            break;
        case NamingPattern::DateNameTime:
            newSchemeForPhotos.arg(photo.phDate().toString("yyyy-MM-dd")).arg(photo.phName())
                    .arg(photo.phTime().toString("hh:mm")).append(photo.phFormat());
            break;
        case NamingPattern::TimeDateName:
            newSchemeForPhotos.arg(photo.phTime().toString("hh:mm")).arg(photo.phDate().toString("yyyy-MM-dd"))
                    .arg(photo.phName()).append(photo.phFormat());
            break;
        case NamingPattern::TimeNameDate:
            newSchemeForPhotos.arg(photo.phTime().toString("hh:mm")).arg(photo.phName())
                    .arg(photo.phDate().toString("yyyy-MM-dd")).append(photo.phFormat());
            break;
        default:
            break;
        }
        _photoNameToNewScheme.insert(photo.phName(), newSchemeForPhotos);
    }

#endif
    return result;
}

QStringList RenamingEngine::processedFileNames()
{
    return QStringList();
}

bool RenamingEngine::processScheme()
{
    bool result{false};

    /* Map parts of the scheme to their occupied position in the scheme
     * So the renaming engine know how the build the renaming
    */
    QHash<QString, int> schemePartToPosition;
    QStringList parts{_scheme.split('_')};
    int pos = 1;
    foreach (auto &name, parts) {
        if(name.startsWith("name"))
        {
           schemePartToPosition.insert("name", pos);
        }else if(name.startsWith("YY")){
            schemePartToPosition.insert("date", pos);
        }else{
            schemePartToPosition.insert("time", pos);
        }
        ++pos;
    }
    if(schemePartToPosition.size() == 3)
        result = true;

    if(schemePartToPosition.value("name") == 1 && schemePartToPosition.value("date") == 2 && schemePartToPosition.value("time") == 3 )
    {
        _namingPattern = NamingPattern::NameDateTime;
    }
    else if(schemePartToPosition.value("name") == 1 && schemePartToPosition.value("time") == 2 && schemePartToPosition.value("date") == 3 )
    {
        _namingPattern = NamingPattern::NameTimeDate;
    }
    else if(schemePartToPosition.value("name") == 3 && schemePartToPosition.value("date") == 1 && schemePartToPosition.value("time") == 2 )
    {
        _namingPattern = NamingPattern::DateTimeName;
    }
    else if(schemePartToPosition.value("name") == 2 && schemePartToPosition.value("date") == 1 && schemePartToPosition.value("time") == 3 )
    {
        _namingPattern = NamingPattern::DateNameTime;
    }
    else if(schemePartToPosition.value("name") == 3 && schemePartToPosition.value("date") == 2 && schemePartToPosition.value("time") == 1 )
    {
        _namingPattern = NamingPattern::TimeDateName;
    }
    else if(schemePartToPosition.value("name") == 2 && schemePartToPosition.value("date") == 3 && schemePartToPosition.value("time") == 1 )
    {
        _namingPattern = NamingPattern::TimeNameDate;
    }

    return result;
}
