#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>

class Configuration : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString recommendedLocation READ recommendedLocation WRITE setRecommendedLocation NOTIFY recommendedLocationChanged FINAL)
    Q_PROPERTY(QString modInstallLocation READ modInstallLocation WRITE setModInstallLocation NOTIFY modInstallLocationChanged FINAL)
    Q_PROPERTY(QString gameInstallLocation READ gameInstallLocation NOTIFY gameInstallLocationChanged FINAL)
    Q_PROPERTY(QString platformName READ platformName WRITE setPlatformName NOTIFY platformNameChanged FINAL)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged FINAL)
    Q_PROPERTY(bool needsShortcut READ needsShortcut WRITE setneedsShortcut NOTIFY needsShortcutChanged FINAL)
    Q_PROPERTY(bool isGameFound READ isGameFound NOTIFY isGameFoundChanged FINAL)

public:
    explicit Configuration(QObject *parent = nullptr);

    QString modInstallLocation() const;
    void setModInstallLocation(const QString &newModInstallLocation);

    QString recommendedLocation() const;
    void setRecommendedLocation(const QString &newRecommendedLocation);

    bool isEmpty() const;

    bool needsShortcut() const;
    void setneedsShortcut(bool newNeedsShortcut);

    QString gameInstallLocation() const;

    bool isGameFound() const;

    QString platformName() const;
    void setPlatformName(const QString &newPlatformName);

public slots:
    void findGameInstallationPath(QString platform);

signals:
    void modInstallLocationChanged();
    void recommendedLocationChanged();

    void isEmptyChanged();

    void needsShortcutChanged();

    void gameInstallLocationChanged();

    void isGameFoundChanged();

    void platformNameChanged();

private:
    QString m_modInstallLocation;
    QString m_recommendedLocation;
    bool m_isEmpty;
    bool m_needsShortcut;
    QString m_gameInstallLocation;
    bool m_isGameFound;
    QString m_platformName;
};

#endif // CONFIGURATION_H
