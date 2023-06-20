#pragma once

#include <QtCore>


class PhotoObject;

class PhotoFactory
{
public:
    PhotoFactory() = default;
    virtual ~ PhotoFactory() = default;

    void takeAPicture(const QString &deviceName, const QString &phName);

    void takeAPicture(const QString &deviceName, const QString &phName, const QDate &phDate, const QTime &phTime, const QString &phFormat);

    QVector<QSharedPointer<PhotoObject> > photos() const;

    QVector<PhotoObject>  photoFromDevice(const QString &deviceType)const;

protected:

    QVector<QSharedPointer<PhotoObject>> _photos;
};
