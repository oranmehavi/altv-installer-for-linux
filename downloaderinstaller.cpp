#include "downloaderinstaller.h"
#include <QJsonDocument>

#define BASE_URL "https://cdn.alt-mp.com/client/release/x64_win32/"

DownloaderInstaller::DownloaderInstaller(QObject *parent)
    : QObject{parent}
{

}

void DownloaderInstaller::append(const QUrl &url)
{
    // if (downloadQueue.isEmpty())
    //     QTimer::singleShot(0, this, &DownloadManager::startNextDownload);

    // downloadQueue.enqueue(url);
    // ++totalCount;
}

void DownloaderInstaller::append(const QStringList &urls)
{
    // for (const QString &urlAsString : urls)
    //     append(QUrl::fromEncoded(urlAsString.toLocal8Bit()));

    // if (downloadQueue.isEmpty())
    //     QTimer::singleShot(0, this, &DownloadManager::finished);
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
    qInfo() << m_outputPath;
    output.setFileName(m_outputPath + "/" + filename);
    if (!output.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
                qPrintable(filename), url.toEncoded().constData(),
                qPrintable(output.errorString()));
        return;
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, &QNetworkReply::downloadProgress,
            this, &DownloaderInstaller::downloadProgress);
    connect(currentDownload, &QNetworkReply::finished,
            this, &DownloaderInstaller::downloadFinished);
    connect(currentDownload, &QNetworkReply::readyRead,
            this, &DownloaderInstaller::downloadReadyRead);

}

void DownloaderInstaller::startNextDownload()
{

}

void DownloaderInstaller::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{


}

void DownloaderInstaller::downloadFinished()
{
    output.close();

    if (currentDownload->error()) {
        // download failed
        fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
        output.remove();
    } else {
        qInfo() << "Succeeded";
        ++m_downloadedCount;
    }


    currentDownload->deleteLater();

    if(downloadingLauncher) {
        downloadingLauncher = false;
        prepareModFilesDownload();
    }
}

void DownloaderInstaller::downloadReadyRead()
{
    //output.write(currentDownload->readAll());
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
                //qInfo() << "Key = " << key << ", Value = " << qint64(value.toDouble());
                totalDownloadSize += qint64(value.toDouble());
            }
            qInfo() << totalDownloadSize;
        }
        currentDownload->deleteLater();
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
