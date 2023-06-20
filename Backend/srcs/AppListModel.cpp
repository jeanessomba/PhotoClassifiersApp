#include "AppListModel.h"
#include <QCoreApplication>
#include <QQmlApplicationEngine>

Q_LOGGING_CATEGORY(applicationListModel, "project.applicationListModel")

AppListModel::AppListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    _fileNames = &FileNamesContainer::fileNamesContainerInstance();
    if(_fileNames)
    {
       connect(_fileNames, &FileNamesContainer::containerSizeChanged, this, &AppListModel::addFileName);
       connect(_fileNames, &FileNamesContainer::containerCleared, this, &AppListModel::clear);
    }
}

int AppListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if(parent.isValid())
        return 0;

    return _listView.size();
}

QVariant AppListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() < 0 || index.row() >= _listView.size())
        return QVariant();

    return _listView.at(index.row());
}

QHash<int, QByteArray> AppListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[FileNameRole] = "FileNameRole";
    return roles;
}

void AppListModel::clear()
{
    beginResetModel();
    _listView.clear();
    endResetModel();
}

void AppListModel::addFileName(const QString& fileName)
{
    Q_UNUSED(fileName)
    beginInsertRows({}, _listView.size(), _listView.size());
    _listView.append(fileName);
    endInsertRows();
}
// Called once QCoreApplication exists
static void registerQmlType()
{
    qmlRegisterSingletonType<AppListModel>("App.ListModel", 1, 0, "AppListModel", [](QQmlEngine *engine, QJSEngine *scriptEngine)-> QObject*{
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        AppListModel *appListModel = new AppListModel();
        return appListModel;
    });
}
Q_COREAPP_STARTUP_FUNCTION(registerQmlType)
