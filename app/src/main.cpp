
#include <QApplication>
#include <QFontDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qmlcontroller.h"
#include "applicationinfo.h"
#include "options.h"

// Add static plugins
//Q_IMPORT_PLUGIN(Exiv2Plugin)
//Q_IMPORT_PLUGIN(OpenCVPlugin)


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    app.setOrganizationName("Simon-12");
    app.setOrganizationDomain("https://github.com/Simon-12");
    app.setApplicationName("Tidy Images");
    app.setWindowIcon(QIcon(":/icons/flaticon/icon.png"));
    ApplicationInfo::loadFonts();

    // Start controller
    QmlController controller("config.ini", &app);

    // Start engine and set controller property
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("controller", &controller);

    // Register ApplicationInfo class
    qmlRegisterType<ApplicationInfo>("qml.applicationinfo", 1, 0, "ApplicationInfo");

    // Register enum class
    qmlRegisterUncreatableType<Options>("qml.options", 1, 0, "Options",
                                        "Not creatable as it is an enum type");
    // Add provider for video frames
    engine.addImageProvider("videoFrame", controller.imageProvider());

    // Start qml
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
