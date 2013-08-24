#ifndef MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
#define MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H

#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

#include <QUrl>

#include "databasemanager.h"
#include "gui/memberuicontroller.h"
#include "gui/memberhandler.h"

namespace membermanager {
namespace gui {

class MainWindowUiController
{
public:
    ~MainWindowUiController();

    static MainWindowUiController *createInstance(const QUrl &qmlUrl);
    void show();

private:
    void initContext(QQmlContext *context);
    void init();
    MainWindowUiController();

    QQmlApplicationEngine m_engine;
    QQuickWindow *m_window;
    membermanager::DatabaseManager *m_databaseManager;
    MemberUiController *m_memberUiController;
    MemberHandler *m_memberHandler;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
