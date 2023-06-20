#include "PhotoFactory.h"
#include "PhotoObject.h"


void PhotoFactory::takeAPicture(const QString &deviceName, const QString &phName)
{
    QSharedPointer<PhotoObject> photo = QSharedPointer<PhotoObject>::create(deviceName, phName);
    _photos.append(photo);
}

void PhotoFactory::takeAPicture(const QString &deviceName, const QString &phName, const QDate &phDate, const QTime &phTime, const QString &phFormat)
{
    QSharedPointer<PhotoObject> photo = QSharedPointer<PhotoObject>::create(deviceName, phName, phDate, phTime, phFormat);
    _photos.append(photo);
}

QVector<QSharedPointer<PhotoObject> > PhotoFactory::photos() const
{
    return _photos;
}

QVector<PhotoObject> PhotoFactory::photoFromDevice(const QString &deviceType) const
{
    QVector<PhotoObject> photos;

    foreach (auto &photo, _photos) {
        if(photo->deviceName().compare(deviceType) == 0)
            photos.append(*photo.data());
    }

    return photos;
}
