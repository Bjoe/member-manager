#include "balancepersister.h"

#include <QString>
#include <QDate>
#include <QTableWidgetItem>

#include "dao/balancedao.h"
#include "accounting/balanceentry.h"

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

    for(int i = 0; i < accountingEntryTable->rowCount(); ++i) {
        int memberId = getData(i, 0).toInt();

        if(memberId != 0) {
            float fee = getData(i, 2).toFloat();
            float donation = getData(i, 3).toFloat();
            float additionalFee = getData(i, 4).toFloat();

            float value = getData(i, 6).toFloat();
            if((fee + donation + additionalFee) == value) {
                accounting::BalanceEntry balanceEntry(memberId);

                QVariant date = getData(i, 5);
                balanceEntry.setValuta(date.toDate());

                QTableWidgetItem *item = accountingEntryTable->item(i, 5);
                int cashKey = item->data(Qt::UserRole).toInt();
                balanceEntry.setCashKey(cashKey);

                balanceEntry.setInfo("Automatische Buchung");

                if(fee != 0) {
                    QVariant purpose = getData(i, 7);
                    balanceEntry.setPurpose(purpose.toString());
                    balanceEntry.setValue(fee);
                    balanceEntry.setAccount(11);
                    balanceDao.saveRecord(balanceEntry);
                }

                if(donation != 0) {
                    balanceEntry.setPurpose("Spende");
                    balanceEntry.setValue(donation);
                    balanceEntry.setAccount(12);
                    balanceDao.saveRecord(balanceEntry);
                }

                if(additionalFee != 0) {
                    balanceEntry.setPurpose("Zusaetzlicher Beitrag");
                    balanceEntry.setValue(additionalFee);
                    balanceEntry.setAccount(4);
                    balanceDao.saveRecord(balanceEntry);
                }
                item = accountingEntryTable->item(i, 8);
                item->setCheckState(Qt::Checked);
            } // else
            // TODO Tabellen Eintrag rot faerben. Summe stimmt nicht!
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
