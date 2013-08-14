#include "mainwindowuicontroller.h"

#include <QObject>
#include <QList>
#include <QString>
#include <QUrl>

namespace membermanager {
namespace gui {

MainWindowUiController::MainWindowUiController(const QUrl &qmlUrl)
    : m_engine(qmlUrl),
      m_window(nullptr),
      m_databaseManager(new membermanager::DatabaseManager())
{
}

MainWindowUiController::~MainWindowUiController()
{
    delete m_databaseManager;
    if(m_window)
        delete m_window;
}

MainWindowUiController *MainWindowUiController::createInstance(const QUrl &qmlUrl)
{
    MainWindowUiController *instance = new MainWindowUiController(qmlUrl);
    QList<QObject *> list = instance->m_engine.rootObjects();
    QObject *topLevel = list.value(0);
    instance->m_window = qobject_cast<QQuickWindow *>(topLevel);

    instance->init();

    return instance;
}

void MainWindowUiController::show()
{
    m_window->show();
}

void MainWindowUiController::init()
{
    m_databaseManager->connect(m_window, SIGNAL(qmlOpenSqlFile(QString)), SLOT(onLoadSqlFile(QString)));
}

} // namespace gui
} // namespace membermanager
