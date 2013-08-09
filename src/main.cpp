
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtWidgets/QApplication>

#include "config.h"
#include "gui/mainwindowuicontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setOrganizationName(ORGANIZATION);
    app.setOrganizationDomain(ORGANIZATION_DOMAIN);

    membermanager::gui::MainWindowUiController *uiController =
            membermanager::gui::MainWindowUiController::createInstance(QUrl(MAIN_QML));

    uiController->show();
    return app.exec();
}
