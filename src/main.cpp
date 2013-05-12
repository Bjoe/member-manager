#include <QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Dorfverwaltung");
    app.setOrganizationName("Chaosdorf");
    app.setOrganizationDomain("www.chaosdorf.de");

    membermanager::gui::MainWindow *mainWindow = new membermanager::gui::MainWindow();
    mainWindow->show();
    return app.exec();
}
