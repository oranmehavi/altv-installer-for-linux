#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>

class Configuration : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString recommendedLocation READ recommendedLocation WRITE setRecommendedLocation NOTIFY recommendedLocationChanged FINAL)
    Q_PROPERTY(QString modInstallLocation READ modInstallLocation WRITE setModInstallLocation NOTIFY modInstallLocationChanged FINAL)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged FINAL)

public:
    explicit Configuration(QObject *parent = nullptr);

    QString modInstallLocation() const;
    void setModInstallLocation(const QString &newModInstallLocation);

    QString recommendedLocation() const;
    void setRecommendedLocation(const QString &newRecommendedLocation);

    bool isEmpty() const;

public slots:

signals:
    void modInstallLocationChanged();
    void recommendedLocationChanged();

    void isEmptyChanged();

private:
    QString m_modInstallLocation;
    QString m_recommendedLocation;
    bool m_isEmpty;
};

#endif // CONFIGURATION_H
