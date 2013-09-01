#ifndef MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
#define MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>

#include "databasemanager.h"

namespace membermanager {
namespace gui {

class MainWindowUiController
{
public:
    ~MainWindowUiController();

    static MainWindowUiController *createInstance(const QString &qmlUrl);
    void show();

private:
    void initContext();
    void init();
    MainWindowUiController();

    QQmlApplicationEngine m_engine;
    QQuickWindow *m_window;
    membermanager::DatabaseManager *m_databaseManager;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
