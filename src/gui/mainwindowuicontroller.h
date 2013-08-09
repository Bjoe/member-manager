#ifndef MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
#define MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include "managerengine.h"

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
    membermanager::ManagerEngine *m_managerEngine;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MAINWINDOWUICONTROLLER_H
