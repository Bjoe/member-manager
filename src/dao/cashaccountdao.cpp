#include "cashaccountdao.h"

#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QSqlTableModel>

#include <QDebug>

#include "databasestructure.h"
#include "member.h"

namespace membermanager
{
namespace dao
{

CashAccountDao::CashAccountDao() : memberDao()
{
}

bool CashAccountDao::clearAndAddTransaction(QTableWidget *aTable)
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(CashTable::TABLENAME);
    QString whereClause = QString("%1 = %2")
            .arg(CashTable::COLUMNNAME[CashTable::deleted])
            .arg("'false'");
    model->setFilter(whereClause);
    model->select();

    for(int y = aTable->rowCount()-1; 0 <= y; --y) {
        aTable->removeRow(y);
    }
    int x=0;
    do {
        model->fetchMore();
        for(; x < model->rowCount(); ++x) {
            QSqlRecord record = model->record(x);
            aTable->insertRow(x);
            aTable->setItem(x, 5, createItem(record.value(CashTable::buchungsdatum)));
            QTableWidgetItem *item = createItem(record.value(CashTable::betrag));
            item->setData(Qt::UserRole, record.value(CashTable::kasse_pkey));
            aTable->setItem(x, 6, item);
            aTable->setItem(x, 7, createItem(record.value(CashTable::bezeichnung)));
            aTable->setItem(x, 8, createItem(record.value(CashTable::fremdname)));

            item = new QTableWidgetItem();
            item->setFlags(Qt::ItemIsUserCheckable);

            if(record.value(CashTable::erfasst).toBool()) {
                item->setCheckState(Qt::Checked);

                QVariant memberId = record.value(CashTable::dorfmitglied_pkey);
                Member member = memberDao.findByMemberId(memberId.toInt());

                aTable->setItem(x, 0, createItem(memberId));
                aTable->setItem(x, 1, createItem(member.getFirstname()));
                aTable->setItem(x, 2, createItem(""));
                aTable->setItem(x, 3, createItem(""));
                aTable->setItem(x, 4, createItem(""));
            } else {
                item->setCheckState(Qt::Unchecked);

                aTable->setItem(x, 0, createItem(""));
                aTable->setItem(x, 1, createEditableItem("-"));
                aTable->setItem(x, 2, createEditableItem(""));
                aTable->setItem(x, 3, createEditableItem(""));
                aTable->setItem(x, 4, createEditableItem(""));
            }
            aTable->setItem(x, 9, item);
        }
    }
    while(model->canFetchMore());

    return true;
}

QTableWidgetItem *CashAccountDao::createEditableItem(QVariant aVariant)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, aVariant);
    return item;
}

QTableWidgetItem *CashAccountDao::createItem(QVariant aVariant)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, aVariant);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    return item;
}

bool CashAccountDao::importTransactions(QList<qiabanking::swift::Transaction *> aTransactionList)
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(CashTable::TABLENAME);
    model->select();

    foreach(qiabanking::swift::Transaction *transaction, aTransactionList) {
        QSqlRecord record = model->record();

        record.setValue(CashTable::valutadatum, QVariant(transaction->getValutaDate()));
        record.setValue(CashTable::buchungsdatum ,QVariant(transaction->getDate()));
        record.setValue(CashTable::fremdname ,QVariant(transaction->getRemoteName()));
        record.setValue(CashTable::fremdblz ,QVariant(transaction->getRemoteBankCode()));
        record.setValue(CashTable::fremdktnr ,QVariant(transaction->getRemoteAccountNumber()));
        record.setValue(CashTable::betrag ,QVariant(transaction->getValue()));
        record.setValue(CashTable::bezeichnung, QVariant(transaction->getPurpose()));
        record.setValue(CashTable::bankbuschl ,QVariant(transaction->getTransactionCode()));
        record.setValue(CashTable::buschl ,QVariant(transaction->getTransactionText()));
        record.setValue(CashTable::einleseid ,QVariant(transaction->getPrimanota()));
        record.setValue(CashTable::einlesedatum, QVariant(QDateTime::currentDateTime()));
        record.setValue(CashTable::deleted, QVariant(false));
        record.setValue(CashTable::erfasst, QVariant(false));

        model->insertRecord(-1, record);
    }
    model->submit();

    return true;
}

accounting::StatementEntry CashAccountDao::findById(int aKeyId)
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(CashTable::TABLENAME);
    model->setFilter(QString("%1=%2")
                     .arg(CashTable::COLUMNNAME[CashTable::kasse_pkey])
                     .arg(aKeyId));
    model->select();
    printSqlError(model->lastError());

    accounting::StatementEntry entry(aKeyId);
    entry.statementRecord = model->record(0);
    return entry;
}

bool CashAccountDao::saveRecord(const accounting::StatementEntry aStatementEntry)
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(CashTable::TABLENAME);
    model->select();

    QSqlRecord record = aStatementEntry.statementRecord;
    bool successful = model->insertRecord(-1, record);
    printSqlError(model->lastError());
    return successful;
}

bool CashAccountDao::updateRecord(const accounting::StatementEntry aStatementEntry)
{
    QSqlRecord record = aStatementEntry.statementRecord;
    int pKey = record.value(CashTable::kasse_pkey).toInt();

    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(CashTable::TABLENAME);
    model->setFilter(QString("%1=%2")
                     .arg(CashTable::COLUMNNAME[CashTable::kasse_pkey])
                     .arg(pKey));
    model->select();
    if(model->rowCount() != 1) {
        return false;
    }
    bool successful = model->setRecord(0, record);
    successful &= model->submitAll();
    return successful;
}

void CashAccountDao::printSqlError(const QSqlError &anError)
{
    if (anError.type() != QSqlError::NoError) {
        /// \todo Publish error to the statusbar as event.
        qDebug() << anError.text();
    }
}

} // namespace dao
} // namespace membermanager
