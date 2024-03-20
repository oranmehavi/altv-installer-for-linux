#include "configuration.h"
#include <QDir>

Configuration::Configuration(QObject *parent)
    : QObject{parent}, m_isEmpty(true),
    m_needsShortcut(true)
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

    if (newModInstallLocation == "")
    {
        m_isEmpty = true;
        emit isEmptyChanged();
        return;
    }

    QDir dir(newModInstallLocation);

    if (!dir.isEmpty())
    {
        m_isEmpty = false;
        emit isEmptyChanged();
        return;
    } else if (!m_isEmpty)
    {
        m_isEmpty = true;
        emit isEmptyChanged();
    }

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

bool Configuration::isEmpty() const
{
    return m_isEmpty;
}

bool Configuration::needsShortcut() const
{
    return m_needsShortcut;
}

void Configuration::setneedsShortcut(bool newNeedsShortcut)
{
    qInfo() << newNeedsShortcut;
    if (m_needsShortcut == newNeedsShortcut)
        return;
    m_needsShortcut = newNeedsShortcut;
    emit needsShortcutChanged();
}
