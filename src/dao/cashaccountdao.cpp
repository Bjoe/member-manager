#include "cashaccountdao.h"

#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QSqlTableModel>

#include "databasestructure.h"
#include "member.h"

namespace membermanager
{
namespace dao
{

CashAccountDao::CashAccountDao() : memberDao()
{
}

bool CashAccountDao::addTransaction(QTableWidget *aTable)
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(KassaTable::TABLENAME);
    QString whereClause = QString("%1 = %2")
            .arg(KassaTable::COLUMNNAME[KassaTable::deleted])
            .arg("'false'");
    model->setFilter(whereClause);
    model->select();

    int y = aTable->rowCount();
    for(int x=0; x < model->rowCount(); ++x) {
        QSqlRecord record = model->record(x);
        aTable->insertRow(y + x);
        aTable->setItem(y + x, 5, createItem(record.value(KassaTable::buchungsdatum)));
        aTable->setItem(y + x, 6, createItem(record.value(KassaTable::betrag)));
        aTable->setItem(y + x, 7, createItem(record.value(KassaTable::bezeichnung)));
        aTable->setItem(y + x, 8, createItem(record.value(KassaTable::fremdname)));

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsUserCheckable);

        if(record.value(KassaTable::erfasst).toBool()) {
            item->setCheckState(Qt::Checked);

            QVariant memberId = record.value(KassaTable::dorfmitglied_pkey);
            Member member = memberDao.findByMemberId(memberId.toInt());

            aTable->setItem(y + x, 0, createItem(memberId));
            aTable->setItem(y + x, 1, createItem(member.getFirstname()));
            aTable->setItem(y + x, 2, createItem(""));
            aTable->setItem(y + x, 3, createItem(""));
            aTable->setItem(y + x, 4, createItem(""));
        } else {
            item->setCheckState(Qt::Unchecked);

            aTable->setItem(y + x, 0, createItem(""));
            aTable->setItem(y + x, 1, createEditableItem("-"));
            aTable->setItem(y + x, 2, createEditableItem(""));
            aTable->setItem(y + x, 3, createEditableItem(""));
            aTable->setItem(y + x, 4, createEditableItem(""));
        }
        aTable->setItem(y + x, 9, item);
    }
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
    model->setTable(KassaTable::TABLENAME);
    model->select();

    foreach(qiabanking::swift::Transaction *transaction, aTransactionList) {
        QSqlRecord record = model->record();

        record.setValue(KassaTable::valutadatum, QVariant(transaction->getValutaDate()));
        record.setValue(KassaTable::buchungsdatum ,QVariant(transaction->getDate()));
        record.setValue(KassaTable::fremdname ,QVariant(transaction->getRemoteName()));
        record.setValue(KassaTable::fremdblz ,QVariant(transaction->getRemoteBankCode()));
        record.setValue(KassaTable::fremdktnr ,QVariant(transaction->getRemoteAccountNumber()));
        record.setValue(KassaTable::betrag ,QVariant(transaction->getValue()));
        record.setValue(KassaTable::bezeichnung, QVariant(transaction->getPurpose()));
        record.setValue(KassaTable::bankbuschl ,QVariant(transaction->getTransactionCode()));
        record.setValue(KassaTable::buschl ,QVariant(transaction->getTransactionText()));
        record.setValue(KassaTable::einleseid ,QVariant(transaction->getPrimanota()));
        record.setValue(KassaTable::einlesedatum, QVariant(QDateTime::currentDateTime()));
        record.setValue(KassaTable::deleted, QVariant(false));
        record.setValue(KassaTable::erfasst, QVariant(false));

        model->insertRecord(-1, record);
    }
    model->submit();

    return true;
}

} // namespace dao
} // namespace membermanager
