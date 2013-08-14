#ifndef MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
#define MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H

#include <QQmlApplicationEngine>
#include <QQuickView>

#include "databasemanager.h"

namespace membermanager {
namespace gui {

class MainWindowUiController
{
public:
    ~MainWindowUiController();

    static MainWindowUiController *createInstance(const QUrl &qmlUrl);
    void show();

private:
    void init();
    MainWindowUiController(const QUrl &qmlUrl);

    QQmlApplicationEngine m_engine;
    QQuickWindow *m_window;
    membermanager::DatabaseManager *m_databaseManager;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
