#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "configuration.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Configuration* config = new Configuration(&app);
    qmlRegisterSingletonInstance("Configuration", 1, 0, "Configuration", config);
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
