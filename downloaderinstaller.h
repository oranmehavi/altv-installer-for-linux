#ifndef DOWNLOADERINSTALLER_H
#define DOWNLOADERINSTALLER_H

#include <QObject>
#include <QtNetwork>


class DownloaderInstaller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int downloadedCount READ downloadedCount NOTIFY downloadedCountChanged FINAL)
    Q_PROPERTY(int totalCount READ totalCount NOTIFY totalCountChanged FINAL)
    Q_PROPERTY(double sizeDownloaded READ sizeDownloaded NOTIFY sizeDownloadedChanged FINAL)
    Q_PROPERTY(double totalSize READ totalSize NOTIFY totalSizeChanged FINAL)
    Q_PROPERTY(double progress READ progress NOTIFY progressChanged FINAL)
    Q_PROPERTY(QString outputPath READ outputPath WRITE setOutputPath NOTIFY outputPathChanged FINAL)
    Q_PROPERTY(QString stepString READ stepString NOTIFY stepStringChanged FINAL)
    Q_PROPERTY(QString speed READ speed NOTIFY speedChanged FINAL)

public:
    explicit DownloaderInstaller(QObject *parent = nullptr);

    void append(const QString &path);
    void append(const QStringList &paths);
    static QString saveFileName(const QUrl &url);

    int downloadedCount() const;

    int totalCount() const;

    QString outputPath() const;
    void setOutputPath(const QString &newOutputPath);

    QString stepString() const;

    QString speed() const;

    double totalSize() const;

    double sizeDownloaded() const;

    double progress() const;

signals:

    void downloadedCountChanged();

    void totalCountChanged();

    void outputPathChanged();

    void stepStringChanged();

    void speedChanged();

    void totalSizeChanged();

    void sizeDownloadedChanged();

    void progressChanged();

public slots:
    void startLauncherDownload();

private slots:
    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void launcherDownloadFinished();
    void modFilesDownloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager manager;
    QQueue<QString> downloadQueue;
    QStringList paths;
    QNetworkReply *currentDownload = nullptr;
    QFile output;
    QElapsedTimer downloadTimer;
    qint64 currentBytesDownloaded = 0;
    qint64 totalDownloadSize = 0;
    qint64 lastReceivedByteSize = 0;

    int m_downloadedCount = 0;
    int m_totalCount = 0;
    bool downloadingLauncher = true;
    QString m_outputPath;

    void prepareModFilesDownload();
    QString m_stepString;
    QString m_speed;
    double m_totalSize;
    double m_sizeDownloaded;
    double m_progress;
};

#endif // DOWNLOADERINSTALLER_H
