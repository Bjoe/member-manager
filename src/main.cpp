
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QUrl>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtWidgets/QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Dorfverwaltung");
    app.setOrganizationName("Chaosdorf");
    app.setOrganizationDomain("www.chaosdorf.de");

    QQmlApplicationEngine engine(QUrl("qrc:/assets/qml/main.qml"));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if( !window ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }

    membermanager::gui::MainWindow *mainWindow = new membermanager::gui::MainWindow();

    QObject::connect(topLevel, SIGNAL(qmlSettingsTriggered()), mainWindow, SLOT(showSettingsDialog()));

    window->show();
    return app.exec();
}
