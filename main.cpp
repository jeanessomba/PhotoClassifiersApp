// Project includes
#include "Settings.h"
#include "PhotoFactory.h"
#include "RenamingEngine.h"
#include "AlbumPresenter.h"

// Qt includes

#ifdef ENABLED_UI
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>
#endif

#include <QtWidgets/QApplication>
#include <QLoggingCategory>




int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    appStartUpSettings();


#ifdef ENABLED_UI
    QQmlApplicationEngine engine;
    const QUrl url("qrc:/PhotoClassifiersApp/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

#else
    PhotoFactory factory;
    factory.takeAPicture("Samsung", "HannoverTrip");

    // To-do: Finish presenter implementation...
    AlbumPresenter presenter(factory);

#endif

    return app.exec();
}
