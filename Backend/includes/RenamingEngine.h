#pragma once

// Qt includes
#include <QObject>
#include <QDataStream>
#include <QDir>

// Project includes
#include "PhotoObject.h"

class RenamingEngine: public QObject
{

public:
    static RenamingEngine& renamingEngineInstance(const QString &dirPath = "", const QString &scheme = "");
    QString shemePattern() const;
    void setShemePattern(const QString &newSchemePattern);
    void setDirPath(const QString &dirPath);
    QString dirPath()const{ return _dirPath; }
    [[nodiscard]]bool processRenaming(const QVector<PhotoObject> &photos);
    QStringList processedFileNames();

private:
    enum class NamingPattern{
        NameDateTime = 0,
        NameTimeDate,
        DateTimeName,
        DateNameTime,
        TimeDateName,
        TimeNameDate
    };

    explicit RenamingEngine(const QString &dirPath, const QString &schemePattern = "name_YYYY-MM-dd_hh:mm.jpg", QObject *parent = nullptr);
    RenamingEngine(const RenamingEngine &) = delete;
    RenamingEngine& operator=(const RenamingEngine&) = delete;

    [[nodiscard]]bool processScheme();
protected:
    QString _scheme;
    QStringList _processedFiles;
    QString _dirPath;
    QStringList _filePaths;    
    RenamingEngine::NamingPattern _namingPattern;

    // Map photo to their new naming scheme
    QHash<QString, QString> _photoNameToNewScheme;
};
