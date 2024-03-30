#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "configuration.h"
#include "downloaderinstaller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Configuration* config = new Configuration(&app);
    DownloaderInstaller* downloaderInstaller = new DownloaderInstaller(&app);

    qmlRegisterSingletonInstance("Configuration", 1, 0, "Configuration", config);
    qmlRegisterSingletonInstance("DownloaderInstaller", 1, 0, "DownloadInstaller", downloaderInstaller);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/altv-installer-for-linux/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
