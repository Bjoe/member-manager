
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QUrl>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
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
    window->show();
    return app.exec();
}
