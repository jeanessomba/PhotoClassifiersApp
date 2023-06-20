#include "PhotoObject.h"



PhotoObject::PhotoObject(const QString &deviceName, const QString &phName, const QDate &phDate, const QTime &phTime, const QString &phFormat)
    : _deviceName(deviceName), _phName(phName), _phDate(phDate), _phTime(phTime), _phFormat(phFormat)
{
    mapDeviceNameToType();
    originalNameSchemeByDevice();
}

PhotoObject::PhotoObject(const QString &deviceName, const QString &phName, const QString &phFormat)
    : _deviceName(deviceName), _phName(phName), _phFormat(phFormat)
{
    _phDate = QDate::currentDate();
    _phTime = QTime::currentTime();
}

QString PhotoObject::deviceName() const
{
    return _deviceName;
}

void PhotoObject::setDeviceName(const QString &newDeviceName)
{
    _deviceName = newDeviceName;
}

QString PhotoObject::phName() const
{
    return _phName;
}

void PhotoObject::setPhName(const QString &newPhName)
{
    _phName = newPhName;
}

QDate PhotoObject::phDate() const
{
    return _phDate;
}

void PhotoObject::setPhDate(const QDate &newPhDate)
{
    _phDate = newPhDate;
}

QTime PhotoObject::phTime() const
{
    return _phTime;
}

void PhotoObject::setPhTime(const QTime &newPhTime)
{
    _phTime = newPhTime;
}

QString PhotoObject::phFormat() const
{
    return _phFormat;
}

void PhotoObject::setPhFormat(const QString &newPhFormat)
{
    _phFormat = newPhFormat;
}

QString PhotoObject::originalNameScheme() const
{
    return _originalNameScheme;
}

void PhotoObject::mapDeviceNameToType()
{
   _deviceNameToType.insert("Samsung", DeviceType::Android);
   _deviceNameToType.insert("Android", DeviceType::Android);
   _deviceNameToType.insert("Apple", DeviceType::Ios);
   _deviceNameToType.insert("Iphone", DeviceType::Ios);
   _deviceNameToType.insert("Macbook", DeviceType::Ios);
   _deviceNameToType.insert("Windows", DeviceType::Windows);

}

void PhotoObject::originalNameSchemeByDevice()
{
    QString munster("%1_%2_%3");

    switch (_deviceNameToType.value(_deviceName, DeviceType::Unknow)) {
    case DeviceType::Android:
        _originalNameScheme = munster.arg(_phTime.toString("hh:mm"))
                .arg(_phDate.toString("yyyy-MM-dd")).arg(phName()).append(phFormat());
        break;
    case DeviceType::Ios:
        _originalNameScheme = munster.arg(_phDate.toString("yyyy-MM-dd"))
                .arg(_phTime.toString("hh:mm")).arg(phName()).append(phFormat());
        break;
    case DeviceType::Windows:
        _originalNameScheme = munster.arg(phName()).arg(_phTime.toString("hh:mm"))
                .arg(_phDate.toString("yyyy-MM-dd")).append(phFormat());
        break;
    default:
        _originalNameScheme = munster.arg("Unknow").arg(_phTime.toString("hh:mm"))
                .arg(_phDate.toString("yyyy-MM-dd")).append(phFormat());
        break;
    }
}
