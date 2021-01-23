#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QDebug>
#include "config.h"

//全局宏定义
#define GLOBAL_ORGANIZATION_NAME                "jsqinyinghao"
#define GLOBAL_ORGANIZATION_DOMAIN              "jsqinyinghao@live.com"
#define GLOBAL_SOFTWARE_NAME                    "picture_player"
#define GLOBAL_SOFTWARE_VERSION                 "1.0.1"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    app.setApplicationDisplayName(GLOBAL_SOFTWARE_NAME);
    QCoreApplication::setOrganizationDomain(GLOBAL_ORGANIZATION_DOMAIN);
    QCoreApplication::setOrganizationName(GLOBAL_ORGANIZATION_NAME);
    QCoreApplication::setApplicationName(GLOBAL_SOFTWARE_NAME);
    QCoreApplication::setApplicationVersion(GLOBAL_SOFTWARE_VERSION);

    Config *g_config = new Config();
    if(!g_config->init()){
        qDebug()<<"check config file";
        return -1;
    }
    QString g_strExeRoot = QCoreApplication::applicationDirPath();
    QDir::setCurrent(g_strExeRoot);

    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("g_strExeRoot",g_strExeRoot);
    ctxt->setContextProperty("g_config",g_config);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
