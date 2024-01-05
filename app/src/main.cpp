
#include <QApplication>
#include <QFontDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "applicationinfo.h"
#include "qmlcontroller.h"

#ifdef APP_STATIC_PLUGINS
Q_IMPORT_PLUGIN(Exiv2Plugin)
Q_IMPORT_PLUGIN(OpenCVPlugin)
#endif

int main(int argc, char *argv[]) {
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

    // Add provider for video frames
    engine.addImageProvider("videoFrame", controller.imageProvider());

    // Start qml
    const QUrl url("qrc:/qml/components/qml/Main.qml");
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
