#include "cashimporthandler.h"

#include <QDate>
#include <QSqlTableModel>

#include <QDebug>

#include "dao/cashaccounttablemodel.h"

namespace membermanager {
namespace gui {

CashImportHandler::CashImportHandler(QObject *parent) :
    QObject(parent), m_cashProxyModel(nullptr), m_cashAccount(new entity::CashAccount())
{
    createCashProxyTableModel(currentYear());
}

ProxyTableModel *CashImportHandler::cashProxyModel() const
{
    return m_cashProxyModel;
}

entity::CashAccount *CashImportHandler::cashAccount() const
{
    return m_cashAccount;
}

void CashImportHandler::selectYear(int year)
{
    delete m_cashProxyModel;
    createCashProxyTableModel(year);
    emit cashProxyModelChanged();
}

void CashImportHandler::onRefresh()
{
    selectYear(currentYear());
}

void CashImportHandler::onSelectedRow(int row)
{
    delete m_cashAccount;
    QSqlTableModel* model = m_cashProxyModel->getModel();
    m_cashAccount = dao::CashAccountTableModel::findBySelectedRow(model, row);
    emit cashAccountChanged();
}

void CashImportHandler::createCashProxyTableModel(int year)
{
    QSqlTableModel* model = dao::CashAccountTableModel::createModel(year);
    m_cashProxyModel = new ProxyTableModel(model, this);
    qDebug() << QString("Database ready. Selected row count: %1").arg(m_cashProxyModel->rowCount());
}

int CashImportHandler::currentYear()
{
    QDate date = QDate::currentDate();
    return date.year();
}

} // namespace gui
} // namespace membermanager
