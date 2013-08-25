#include "mainwindowuicontroller.h"

#include <QObject>
#include <QList>
#include <QString>

#include <QDateTime>
#include <QStringList>

#include <QDebug>

#include <QSqlTableModel>

namespace membermanager {
namespace gui {

MainWindowUiController::MainWindowUiController()
    : m_engine(),
      m_window(nullptr),
      m_databaseManager(new membermanager::DatabaseManager()),
      m_memberHandler(new MemberHandler())
{
    //m_memberHandler->connect(m_databaseManager, SIGNAL(databaseReady()), SLOT(onDatabaseReady()));
    //m_databaseManager->onLoadSqlFile("file:dorfverw.dat");
}

MainWindowUiController::~MainWindowUiController()
{
    delete m_databaseManager;
    delete m_memberHandler;
    if(m_window)
        delete m_window;
}

MainWindowUiController *MainWindowUiController::createInstance(const QUrl &qmlUrl)
{
    MainWindowUiController *instance = new MainWindowUiController();

    instance->initContext(instance->m_engine.rootContext());

    instance->m_engine.load(qmlUrl);

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

void MainWindowUiController::initContext(QQmlContext *context)
{
    context->setContextProperty("memberTable", m_memberHandler->getProxyModel());
    context->setContextProperty("currentDateTime", QDateTime::currentDateTime());
}

void MainWindowUiController::init()
{
    m_databaseManager->connect(m_window, SIGNAL(qmlOpenSqlFile(QString)), SLOT(onLoadSqlFile(QString)));
    m_memberHandler->connect(m_databaseManager, SIGNAL(databaseReady()), SLOT(onDatabaseReady()));
    m_window->connect(m_databaseManager, SIGNAL(databaseReady()), SLOT(onDatabaseReady()));
    m_window->connect(m_memberHandler->getProxyModel(), SIGNAL(modelReloaded()), SLOT(onModelReloaded()));
}

} // namespace gui
} // namespace membermanager
