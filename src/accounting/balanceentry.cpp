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
    setValueOnField(BalanceTable::dorfmitglied_pkey, QVariant::Int, QVariant(aMemberId));
}

int BalanceEntry::getMemberId() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::dorfmitglied_pkey];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setValue(double aValue)
{
    setValueOnField(BalanceTable::betrag, QVariant::Double, QVariant(aValue));
}

double BalanceEntry::getValue() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::betrag];
    return balanceRecord.value(fieldname).toDouble();
}

void BalanceEntry::setValuta(const QDate &aDate)
{
    setValueOnField(BalanceTable::datum, QVariant::Date, QVariant(aDate));
}

QDate BalanceEntry::getValuta() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::datum];
    return balanceRecord.value(fieldname).toDate();
}

void BalanceEntry::setPurpose(const QString &aPurpose)
{
    setValueOnField(BalanceTable::bezeichnung, QVariant::String, QVariant(aPurpose));
}

QString BalanceEntry::getPurpose() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::bezeichnung];
    return balanceRecord.value(fieldname).toString();
}

void BalanceEntry::setInfo(const QString &anInfo)
{
    setValueOnField(BalanceTable::info, QVariant::String, QVariant(anInfo));
}

QString BalanceEntry::getInfo() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::info];
    return balanceRecord.value(fieldname).toString();
}

void BalanceEntry::setAccount(int anAccount)
{
    setValueOnField(BalanceTable::konten, QVariant::Int, QVariant(anAccount));
}

int BalanceEntry::getAccount() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::konten];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setCashKey(int aKey)
{
    setValueOnField(BalanceTable::kasse_pkey, QVariant::Int, QVariant(aKey));
}

int BalanceEntry::getCashKey() const
{
    QString fieldname = BalanceTable::COLUMNNAME[BalanceTable::kasse_pkey];
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
