#include "balanceentry.h"

#include <QString>
#include <QVariant>
#include <QSqlField>

#include "dao/databasestructure.h"

namespace membermanager
{
namespace accounting
{
using dao::BalanceTable;

BalanceEntry::BalanceEntry(int aMemberId) : balanceRecord()
{
    setValueOnField(BalanceTable::MemberId, QVariant::Int, QVariant(aMemberId));
}

int BalanceEntry::getMemberId() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::MemberId];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setValue(double aValue)
{
    setValueOnField(BalanceTable::Amount, QVariant::Double, QVariant(aValue));
}

double BalanceEntry::getValue() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::Amount];
    return balanceRecord.value(fieldname).toDouble();
}

void BalanceEntry::setValuta(const QDate &aDate)
{
    setValueOnField(BalanceTable::Date, QVariant::Date, QVariant(aDate));
}

QDate BalanceEntry::getValuta() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::Date];
    return balanceRecord.value(fieldname).toDate();
}

void BalanceEntry::setPurpose(const QString &aPurpose)
{
    setValueOnField(BalanceTable::Description, QVariant::String, QVariant(aPurpose));
}

QString BalanceEntry::getPurpose() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::Description];
    return balanceRecord.value(fieldname).toString();
}

void BalanceEntry::setInfo(const QString &anInfo)
{
    setValueOnField(BalanceTable::Info, QVariant::String, QVariant(anInfo));
}

QString BalanceEntry::getInfo() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::Info];
    return balanceRecord.value(fieldname).toString();
}

void BalanceEntry::setAccount(int anAccount)
{
    setValueOnField(BalanceTable::BookingAccount, QVariant::Int, QVariant(anAccount));
}

int BalanceEntry::getAccount() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::BookingAccount];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setCashKey(int aKey)
{
    setValueOnField(BalanceTable::CashId, QVariant::Int, QVariant(aKey));
}

int BalanceEntry::getCashKey() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::CashId];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setValueOnField(int aIndex, QVariant::Type aType, const QVariant &aValue)
{
    QString fieldname = BalanceTable::COLUMNNAME[aIndex];
    if(balanceRecord.contains(fieldname) == false) {
        QSqlField field(fieldname, aType);
        balanceRecord.append(field);
    }
    balanceRecord.setValue(fieldname, aValue);
}

}
}
