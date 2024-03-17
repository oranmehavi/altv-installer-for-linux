#include "configuration.h"
#include <QDir>

Configuration::Configuration(QObject *parent)
    : QObject{parent}
{
    setRecommendedLocation(QDir::homePath()+"/altv");
    setModInstallLocation(m_recommendedLocation);
}

QString Configuration::modInstallLocation() const
{
    return m_modInstallLocation;
}

void Configuration::setModInstallLocation(const QString &newModInstallLocation)
{
    if (m_modInstallLocation == newModInstallLocation)
        return;
    m_modInstallLocation = newModInstallLocation;
    emit modInstallLocationChanged();
}

QString Configuration::recommendedLocation() const
{
    return m_recommendedLocation;
}

void Configuration::setRecommendedLocation(const QString &newRecommendedLocation)
{
    if (m_recommendedLocation == newRecommendedLocation)
        return;
    m_recommendedLocation = newRecommendedLocation;
    emit recommendedLocationChanged();
}
