#include "cashimporthandler.h"

#include <QDate>
#include <QSqlTableModel>
#include <QSettings>
#include <QUrl>

#include <QDebug>

#include "swift/importer.h"
#include "swift/transaction.h"

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

void CashImportHandler::onImport(const QString &urlFilename)
{
    emit progress(0);
    emit statusMessage("Importing SWIFT .... please wait");

    QUrl url(urlFilename);
    QString filename = url.path();
    QSettings settings;
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();

    qiabanking::swift::Importer importer(bankCode, accountNumber);
    QList<qiabanking::swift::Transaction *> transactionList = importer.importMt940Swift(filename);

    for(const qiabanking::swift::Transaction* transaction : transactionList) {
        entity::CashAccount* cashAccount = new entity::CashAccount();

        cashAccount->setRemoteName(transaction->getRemoteName());
        cashAccount->setRemoteBankCode(transaction->getRemoteBankCode());
        cashAccount->setRemoteAccountNumber(transaction->getRemoteAccountNumber());
        cashAccount->setValue(transaction->getValue());
        cashAccount->setValuta(transaction->getValutaDate());
        cashAccount->setDate(transaction->getDate());
        cashAccount->setPurpose(transaction->getPurpose());
        cashAccount->setTransactionText(transaction->getTransactionText());
        cashAccount->setTransactionCode(transaction->getTransactionCode());
        cashAccount->setPrimanota(transaction->getPrimanota());

        cashAccount->save();
        delete cashAccount;
        delete transaction;
    }

    emit statusMessage(QString("Imported SWIFT file: %1").arg(urlFilename));
    emit progress(1);
    emit cashAccountModelChanged();
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
