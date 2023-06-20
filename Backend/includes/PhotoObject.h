#pragma once

#include <QtCore>

/**
 * @brief The PhotoObject class represents a picture with EXIF Data to this picture (device name, picture name, etc..)
 */
class PhotoObject
{
public:
    PhotoObject() = default;

    explicit PhotoObject(const QString &deviceName, const QString &phName, const QDate &phDate, const QTime &phTime, const QString &phFormat = ".jpg");

    explicit PhotoObject(const QString &deviceName, const QString &phName, const QString &phFormat = ".jpg");

    virtual ~PhotoObject() = default;

    QString deviceName() const;
    void setDeviceName(const QString &newDeviceName);

    QString phName() const;
    void setPhName(const QString &newPhName);

    QDate phDate() const;
    void setPhDate(const QDate &newPhDate);

    QTime phTime() const;
    void setPhTime(const QTime &newPhTime);

    QString phFormat() const;
    void setPhFormat(const QString &newPhFormat);

    QString originalNameScheme() const;

private:

    enum class DeviceType{
        Android = 0,
        Ios,
        Windows,
        Unknow
    };
    /**
     * @brief mapDeviceNameToType map the name of the device to the enum DeviceType and use it in the function "originalNameSchemeByDevice()".
     */
    void mapDeviceNameToType();

    /**
     * @brief originalNameSchemeByDevice is a function that builds the name schema based on the device that took the photo.
     */
    void originalNameSchemeByDevice();

protected:
    QString _deviceName;
    QString _phName;
    QDate _phDate;
    QTime _phTime;
    QString _phFormat;
    QString _originalNameScheme;
    QHash<QString, PhotoObject::DeviceType> _deviceNameToType;
};
