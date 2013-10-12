#include "mainwindowuicontroller.h"

#include <QObject>
#include <QUrl>
#include <QList>
#include <QString>

#include <QDebug>

#include <QtQml/QQmlContext>
#include "qqml.h"

#include "entity/member.h"
#include "entity/balance.h"
#include "entity/bankaccount.h"
#include "entity/cashaccount.h"
#include "entity/contribution.h"

#include "gui/memberlisthandler.h"
#include "gui/memberhandler.h"
#include "gui/feedebthandler.h"
#include "gui/accountinghandler.h"
#include "gui/cashimporthandler.h"
#include "gui/balancepersisthandler.h"
#include "gui/contributionreceipthandler.h"
#include "gui/proxytablemodel.h"

namespace membermanager {
namespace gui {

MainWindowUiController::MainWindowUiController()
    : m_engine(),
      m_window(nullptr),
      m_databaseManager(new membermanager::DatabaseManager())
{
    //m_databaseManager->onLoadSqlFile("file:dorfverw.dat");

    qmlRegisterType<membermanager::gui::MemberListHandler>("membermanager", 1, 0, "MemberListHandler");
    qmlRegisterType<membermanager::gui::MemberHandler>("membermanager", 1, 0, "MemberHandler");
    qmlRegisterType<membermanager::gui::ContributionReceiptHandler>("membermanager", 1, 0, "ContributionReceiptHandler");
    qmlRegisterType<membermanager::gui::AccountingHandler>("membermanager", 1, 0, "AccountingHandler");
    qmlRegisterType<membermanager::gui::CashImportHandler>("membermanager", 1, 0, "CashImportHandler");
    qmlRegisterType<membermanager::gui::BalancePersistHandler>("membermanager", 1, 0, "BalancePersisterHandler");
    qmlRegisterType<membermanager::gui::FeeDebtHandler>("membermanager", 1, 0, "FeeDebtHandler");
    qmlRegisterType<membermanager::gui::ProxyTableModel>("membermanager", 1, 0, "ProxyTableModel");
    qmlRegisterType<membermanager::entity::Member>("membermanager", 1, 0, "Member");
    qmlRegisterType<membermanager::entity::BankAccount>("membermanager", 1, 0, "BankAccount");
    qmlRegisterType<membermanager::entity::Balance>("membermanager", 1, 0, "Balance");
    qmlRegisterType<membermanager::entity::CashAccount>("membermanager", 1, 0, "CashAccount");
    qmlRegisterType<membermanager::entity::Contribution>("membermanager", 1, 0, "Contribution");
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
