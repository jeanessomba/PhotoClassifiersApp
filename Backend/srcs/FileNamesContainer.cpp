#include "FileNamesContainer.h"


FileNamesContainer::FileNamesContainer(QObject *parent)
    :QObject(parent)
{

}

QStringList FileNamesContainer::fileNames() const
{
    return _fileNames;
}

FileNamesContainer &FileNamesContainer::fileNamesContainerInstance()
{
    static FileNamesContainer fileNamesContainer;
    return fileNamesContainer;
}

void FileNamesContainer::fillContainerOnce(const QStringList &fileNames)
{
    foreach (const auto &fileName, fileNames) {
        _fileNames.append(fileName);
        emit containerSizeChanged(fileName);
    }
}

void FileNamesContainer::fillContainer(const QString &fileName)
{
    _fileNames.append(fileName);
    emit containerSizeChanged(fileName);
}

void FileNamesContainer::clearContainer()
{
   _fileNames.clear();
   emit containerCleared();
}
