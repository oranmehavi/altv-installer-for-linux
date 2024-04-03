#include "downloaderinstaller.h"
#include <QJsonDocument>
#include <QDir>

#define BASE_URL "https://cdn.alt-mp.com/client/release/x64_win32/"

DownloaderInstaller::DownloaderInstaller(QObject *parent)
    : QObject{parent}
{

}

void DownloaderInstaller::append(const QString &path)
{
    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, &DownloaderInstaller::startNextDownload);

    downloadQueue.enqueue(path);
}

void DownloaderInstaller::append(const QStringList &paths)
{
    for (const QString &path : paths)
        append(path);

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, &DownloaderInstaller::modFilesDownloadFinished);
}

QString DownloaderInstaller::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    return basename;
}

void DownloaderInstaller::startLauncherDownload()
{
    QUrl url("https://cdn.alt-mp.com/launcher/release/x64_win32/altv.exe");

    QString filename = saveFileName(url);
    QDir dir(m_outputPath);

    output.setFileName(m_outputPath + "/" + filename);

    dir.mkpath(QFileInfo(output.fileName()).absoluteDir().absolutePath());

    if (!output.open(QIODevice::WriteOnly)) {
        qInfo() << "Error opening file";
        return;
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);

    connect(currentDownload, &QNetworkReply::metaDataChanged,
            this, [&]() {
        totalDownloadSize = qint64(currentDownload->header(QNetworkRequest::ContentLengthHeader).toDouble());
        m_totalSize = totalDownloadSize / 1000000;
        m_totalSize = floor(m_totalSize * 10) / 10;

        emit totalSizeChanged();
    });
    connect(currentDownload, &QNetworkReply::downloadProgress,
            this, &DownloaderInstaller::downloadProgress);
    connect(currentDownload, &QNetworkReply::finished,
            this, &DownloaderInstaller::launcherDownloadFinished);
    connect(currentDownload, &QNetworkReply::readyRead,
            this, &DownloaderInstaller::downloadReadyRead);

    downloadTimer.start();
}

void DownloaderInstaller::startNextDownload()
{
    if (downloadQueue.isEmpty()) {
        qInfo() << "Finished downloading files successfully";
        return;
    }

    QString path = downloadQueue.dequeue();

    QUrl url(BASE_URL + path);

    QDir dir(m_outputPath);

    output.setFileName(m_outputPath + "/" + path);

    dir.mkpath(QFileInfo(output.fileName()).absoluteDir().absolutePath());

    if (!output.open(QIODevice::WriteOnly)) {
        qInfo() << "Error opening file";
        startNextDownload();
        return;                 // skip this download
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, &QNetworkReply::downloadProgress,
            this, &DownloaderInstaller::downloadProgress);
    connect(currentDownload, &QNetworkReply::finished,
            this, &DownloaderInstaller::modFilesDownloadFinished);
    connect(currentDownload, &QNetworkReply::readyRead,
            this, &DownloaderInstaller::downloadReadyRead);

    // prepare the output
    qInfo() << "Downloading " << url.toEncoded().constData() << "to " << QFileInfo(output.fileName()).absoluteDir().absolutePath();
}

void DownloaderInstaller::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{

    currentBytesDownloaded += (bytesReceived - lastReceivedByteSize);

    m_progress = currentBytesDownloaded * 100 / totalDownloadSize;
    emit progressChanged();


    m_sizeDownloaded = currentBytesDownloaded / 1000000;
    m_sizeDownloaded = floor(m_sizeDownloaded * 10) / 10;
    emit sizeDownloadedChanged();

    double speed = currentBytesDownloaded * 1000.0 / downloadTimer.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }

    lastReceivedByteSize = bytesReceived;
    m_speed = QString::number(floor(speed * 100.0) / 100.0) + " " + unit;
    emit speedChanged();
}

void DownloaderInstaller::launcherDownloadFinished()
{
    output.close();

    if (currentDownload->error()) {
        // download failed
        fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
        output.remove();
    } else {
        qInfo() << "Succeeded";
        lastReceivedByteSize = 0;
        m_downloadedCount++;
        emit downloadedCountChanged();
    }


    currentDownload->deleteLater();
    totalDownloadSize = 0;
    m_totalCount = 0;
    m_downloadedCount = 0;
    currentBytesDownloaded = 0;
    m_sizeDownloaded = 0;
    emit sizeDownloadedChanged();
    emit totalCountChanged();
    emit downloadedCountChanged();

    prepareModFilesDownload();
}

void DownloaderInstaller::modFilesDownloadFinished()
{
    output.close();

    if (currentDownload->error()) {
        // download failed
        fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
        output.remove();
    } else {
        qInfo() << "Succeeded";
        lastReceivedByteSize = 0;
        ++m_downloadedCount;
        emit downloadedCountChanged();
    }


    currentDownload->deleteLater();
    startNextDownload();
}

void DownloaderInstaller::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}

void DownloaderInstaller::prepareModFilesDownload()
{
    QUrl url(BASE_URL "update.json");

    QNetworkRequest request(url);
    currentDownload = manager.get(request);

    connect(currentDownload, &QNetworkReply::finished, this, [&]() {
        if (currentDownload->error()) {
            qInfo() << "error";
        }
        else {
            QJsonDocument doc(QJsonDocument::fromJson(currentDownload->readAll()));
            QJsonObject json = doc.object()["sizeList"].toObject();
            foreach(const QString& key, json.keys()) {
                QJsonValue value = json.value(key);
                totalDownloadSize += qint64(value.toDouble());
                m_totalCount++;
                paths << key;
            }
            m_totalSize = totalDownloadSize / 1000000;
            m_totalSize = floor(m_totalSize * 10) / 10;

            emit totalSizeChanged();
            emit totalCountChanged();

            currentDownload->deleteLater();
            downloadTimer.start();
            append(paths);
        }

    });
}

int DownloaderInstaller::downloadedCount() const
{
    return m_downloadedCount;
}

int DownloaderInstaller::totalCount() const
{
    return m_totalCount;
}


QString DownloaderInstaller::outputPath() const
{
    return m_outputPath;
}

void DownloaderInstaller::setOutputPath(const QString &newOutputPath)
{
    if (m_outputPath == newOutputPath)
        return;
    m_outputPath = newOutputPath;
    emit outputPathChanged();
}

QString DownloaderInstaller::stepString() const
{
    return m_stepString;
}

QString DownloaderInstaller::speed() const
{
    return m_speed;
}

double DownloaderInstaller::totalSize() const
{
    return m_totalSize;
}

double DownloaderInstaller::sizeDownloaded() const
{
    return m_sizeDownloaded;
}

double DownloaderInstaller::progress() const
{
    return m_progress;
}
