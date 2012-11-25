#include "balancepersister.h"

#include <QString>
#include <QColor>
#include <QBrush>
#include <QDate>
#include <QTableWidgetItem>

#include "dao/balancedao.h"
#include "dao/cashaccountdao.h"
#include "accounting/balanceentry.h"
#include "accounting/statemententry.h"

namespace membermanager {
namespace accounting {

BalancePersister::BalancePersister(QTableWidget *anAccountingEntryTable, QObject *aParent)
    : QObject(aParent),
      accountingEntryTable(anAccountingEntryTable)
{
}

void BalancePersister::booking() const
{
    dao::BalanceDao balanceDao;
    dao::CashAccountDao cashAccountDao;

    for(int i = 0; i < accountingEntryTable->rowCount(); ++i) {
        int memberId = getData(i, 0).toInt();

        if(memberId != 0) {
            QTableWidgetItem *item = accountingEntryTable->item(i, 6);
            int cashKey = item->data(Qt::UserRole).toInt();
            accounting::StatementEntry statementEntry = cashAccountDao.findById(cashKey);
            if(statementEntry.isBooked() == false && statementEntry.isDeleted() == false) {

                float fee = getData(i, 2).toFloat();
                float donation = getData(i, 3).toFloat();
                float additionalFee = getData(i, 4).toFloat();

                float value = statementEntry.getValue();
                if((fee + donation + additionalFee) == value) {
                    item->setBackground(QBrush(Qt::NoBrush));
                    accounting::BalanceEntry balanceEntry(memberId);

                    balanceEntry.setValuta(statementEntry.getDate().date());
                    balanceEntry.setCashKey(cashKey);
                    balanceEntry.setInfo("Automatische Buchung");

                    if(fee != 0) {
                        balanceEntry.setPurpose(statementEntry.getPurpose());
                        balanceEntry.setValue(fee);
                        balanceEntry.setAccount(11);
                        balanceDao.saveRecord(balanceEntry);
                    }

                    if(donation != 0) {
                        balanceEntry.setPurpose(statementEntry.getPurpose());
                        balanceEntry.setValue(donation);
                        balanceEntry.setAccount(12);
                        balanceDao.saveRecord(balanceEntry);
                    }

                    if(additionalFee != 0) {
                        balanceEntry.setPurpose(statementEntry.getPurpose());
                        balanceEntry.setValue(additionalFee);
                        balanceEntry.setAccount(4);
                        balanceDao.saveRecord(balanceEntry);
                    }

                    item = accountingEntryTable->item(i, 8);
                    item->setCheckState(Qt::Checked);
                    statementEntry.setBooked(true);
                    statementEntry.setMemberId(memberId);
                    cashAccountDao.updateRecord(statementEntry);
                } else {
                    item->setBackground(QBrush(Qt::red));
                }
            }
        }
    }
}

QVariant BalancePersister::getData(int aRow, int aColumn) const
{
    QTableWidgetItem *item = accountingEntryTable->item(aRow, aColumn);
    return item->data(Qt::DisplayRole);
}

} // namespace accounting
} // namespace membermanager
