#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>

class Configuration : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString recommendedLocation READ recommendedLocation WRITE setRecommendedLocation NOTIFY recommendedLocationChanged FINAL)
    Q_PROPERTY(QString modInstallLocation READ modInstallLocation WRITE setModInstallLocation NOTIFY modInstallLocationChanged FINAL)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged FINAL)
    Q_PROPERTY(bool needsShortcut READ needsShortcut WRITE setneedsShortcut NOTIFY needsShortcutChanged FINAL)

public:
    explicit Configuration(QObject *parent = nullptr);

    QString modInstallLocation() const;
    void setModInstallLocation(const QString &newModInstallLocation);

    QString recommendedLocation() const;
    void setRecommendedLocation(const QString &newRecommendedLocation);

    bool isEmpty() const;

    bool needsShortcut() const;
    void setneedsShortcut(bool newNeedsShortcut);

public slots:

signals:
    void modInstallLocationChanged();
    void recommendedLocationChanged();

    void isEmptyChanged();

    void needsShortcutChanged();

private:
    QString m_modInstallLocation;
    QString m_recommendedLocation;
    bool m_isEmpty;
    bool m_needsShortcut;
};

#endif // CONFIGURATION_H
