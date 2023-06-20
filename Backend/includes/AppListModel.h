#pragma once

// Qt includes
#include <QAbstractListModel>
#include <QObject>

// Project includes
#include "FileNamesContainer.h"


class AppListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AppListModel(QObject* parent = nullptr);

    enum FileNamesModelRoles
    {
        FileNameRole = Qt::UserRole + 1,
    };

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void addFileName(const QString& fileName);
    void clear();

private:
    FileNamesContainer *_fileNames{nullptr};
    QStringList _listView;
};
