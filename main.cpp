#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qtquickplugin.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/TableView_DelegateChooser/table.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    QtquickPlugin plugin;
    plugin.registerTypes("org.lxqt.qps");
    engine.load(url);
    return app.exec();
}
