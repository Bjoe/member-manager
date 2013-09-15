#include "cashimporthandler.h"

#include <QSqlTableModel>

#include <QDebug>

#include "dao/cashaccounttablemodel.h"

namespace membermanager {
namespace gui {

CashImportHandler::CashImportHandler(QObject *parent) :
    QObject(parent), m_cashProxyModel(nullptr), m_cashAccount(new entity::CashAccount())
{
    createCashProxyTableModel();
}

ProxyTableModel *CashImportHandler::cashProxyModel() const
{
    return m_cashProxyModel;
}

entity::CashAccount *CashImportHandler::cashAccount() const
{
    return m_cashAccount;
}

void CashImportHandler::onDatabaseReady()
{
    delete m_cashProxyModel;
    createCashProxyTableModel();
    emit cashProxyModelChanged();
}

void CashImportHandler::onCashSelected(int row)
{
    delete m_cashAccount;
    QSqlTableModel *model = m_cashProxyModel->getModel();
    m_cashAccount = dao::CashAccountTableModel::findBySelectedRow(model, row);
    emit cashAccountChanged();
}

void CashImportHandler::createCashProxyTableModel()
{
    QSqlTableModel *model = dao::CashAccountTableModel::createModel();
    m_cashProxyModel = new ProxyTableModel(model, this);
    qDebug() << QString("Database ready. Selected row count: %1").arg(m_cashProxyModel->rowCount());
}



} // namespace gui
} // namespace membermanager
