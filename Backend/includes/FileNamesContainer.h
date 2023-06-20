#pragma once

#include <QtCore>


class FileNamesContainer: public QObject
{
    Q_OBJECT

public:
    static FileNamesContainer& fileNamesContainerInstance();

    void fillContainerOnce(const QStringList &fileNames);

    void fillContainer(const QString &fileName);

    void clearContainer();

    QStringList fileNames() const;

signals:
    /* Signal emitted everytime container size ist incremented or decremented. The AppListModel will use this signal
     * to get changes in the container.
    */
    void containerSizeChanged(const QString &fileName);

    void containerCleared();

private:
    explicit FileNamesContainer(QObject *parent = nullptr);
    FileNamesContainer(const FileNamesContainer &) = delete;
    FileNamesContainer& operator=(const FileNamesContainer&) = delete;

    QStringList _fileNames;
};
