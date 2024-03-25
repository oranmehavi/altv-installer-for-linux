#include "configuration.h"
#include <QDir>
#include "utilities.h"

Configuration::Configuration(QObject *parent)
    : QObject{parent}, m_isEmpty(true),
    m_needsShortcut(true), m_isGameFound(true)
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

QString Configuration::gameInstallLocation() const
{
    return m_gameInstallLocation;
}

void Configuration::findGameInstallationPath(QString platform)
{
    if (platform == "Steam")
    {
        QString path = Utilities::getSteamGamePath();

        if (path != "") {
            m_gameInstallLocation = path;
            m_isGameFound = true;
            emit isGameFoundChanged();
            emit gameInstallLocationChanged();
        }
        else {
            m_isGameFound = false;
            m_gameInstallLocation = "";
            emit gameInstallLocationChanged();
            emit isGameFoundChanged();
        }
    }
}

bool Configuration::isGameFound() const
{
    return m_isGameFound;
}
