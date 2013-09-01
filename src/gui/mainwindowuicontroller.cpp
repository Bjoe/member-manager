#include "mainwindowuicontroller.h"

#include <QObject>
#include <QUrl>
#include <QList>
#include <QString>

#include <QDebug>

#include <QtQml/QQmlContext>
#include "qqml.h"

#include "entity/member.h"
#include "gui/memberhandler.h"
#include "gui/proxytablemodel.h"

namespace membermanager {
namespace gui {

MainWindowUiController::MainWindowUiController()
    : m_engine(),
      m_window(nullptr),
      m_databaseManager(new membermanager::DatabaseManager())
{
    //m_databaseManager->onLoadSqlFile("file:dorfverw.dat");

    qmlRegisterType<membermanager::gui::MemberHandler>("membermanager", 1, 0, "MemberHandler");
    qmlRegisterType<membermanager::entity::Member>("membermanager", 1, 0, "Member");
    qmlRegisterType<membermanager::gui::ProxyTableModel>("membermanager", 1, 0, "MemberTable");
}

MainWindowUiController::~MainWindowUiController()
{
    delete m_databaseManager;
    if(m_window)
        delete m_window;
}

MainWindowUiController *MainWindowUiController::createInstance(const QString &qmlUrl)
{
    MainWindowUiController *instance = new MainWindowUiController();

    instance->initContext();
    instance->m_engine.load(QUrl(qmlUrl));
    instance->init();
    return instance;
}

void MainWindowUiController::show()
{
    m_window->show();
}

void MainWindowUiController::initContext()
{
    QQmlContext *context = m_engine.rootContext();
}

void MainWindowUiController::init()
{
    QList<QObject *> list = m_engine.rootObjects();
    QObject *topLevel = list.value(0);
    m_window = qobject_cast<QQuickWindow *>(topLevel);

    m_databaseManager->connect(m_window, SIGNAL(qmlOpenSqlFile(QString)), SLOT(onLoadSqlFile(QString)));
    m_window->connect(m_databaseManager, SIGNAL(databaseReady()), SLOT(onDatabaseReady()));
}

} // namespace gui
} // namespace membermanager
