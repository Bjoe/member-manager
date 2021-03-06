
#include <stdio.h>
#include <stdlib.h>

#include <QString>
#include <QByteArray>
#include <QtWidgets/QApplication>

#include <QMessageLogContext>
#include <QtMessageHandler>

#include "config.h"
#include "gui/mainwindowuicontroller.h"

void messageHandlerOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char **argv)
{
    qInstallMessageHandler(messageHandlerOutput);
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setOrganizationName(ORGANIZATION);
    app.setOrganizationDomain(ORGANIZATION_DOMAIN);

    membermanager::gui::MainWindowUiController *uiController =
            membermanager::gui::MainWindowUiController::createInstance(MAIN_QML);

    uiController->show();
    return app.exec();
}
