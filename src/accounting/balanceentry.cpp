#include "balanceentry.h"

#include <QString>
#include <QVariant>
#include <QSqlField>

#include "dao/databasestructure.h"

namespace membermanager
{
namespace accounting
{
using dao::SaldoTable;

BalanceEntry::BalanceEntry(int aMemberId) : balanceRecord()
{
    setValueOnField(SaldoTable::dorfmitglied_pkey, QVariant::Int, QVariant(aMemberId));
}

int BalanceEntry::getMemberId() const
{
    QString fieldname = SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setValue(double aValue)
{
    setValueOnField(SaldoTable::betrag, QVariant::Double, QVariant(aValue));
}

double BalanceEntry::getValue() const
{
    QString fieldname = SaldoTable::COLUMNNAME[SaldoTable::betrag];
    return balanceRecord.value(fieldname).toDouble();
}

void BalanceEntry::setValuta(const QDate &aDate)
{
    setValueOnField(SaldoTable::datum, QVariant::Date, QVariant(aDate));
}

QDate BalanceEntry::getValuta() const
{
    QString fieldname = SaldoTable::COLUMNNAME[SaldoTable::datum];
    return balanceRecord.value(fieldname).toDate();
}

void BalanceEntry::setPurpose(const QString &aPurpose)
{
    setValueOnField(SaldoTable::bezeichnung, QVariant::String, QVariant(aPurpose));
}

QString BalanceEntry::getPurpose() const
{
    QString fieldname = SaldoTable::COLUMNNAME[SaldoTable::bezeichnung];
    return balanceRecord.value(fieldname).toString();
}

void BalanceEntry::setInfo(const QString &anInfo)
{
    setValueOnField(SaldoTable::info, QVariant::String, QVariant(anInfo));
}

QString BalanceEntry::getInfo() const
{
    QString fieldname = SaldoTable::COLUMNNAME[SaldoTable::info];
    return balanceRecord.value(fieldname).toString();
}

void BalanceEntry::setAccount(int anAccount)
{
    setValueOnField(SaldoTable::konten, QVariant::Int, QVariant(anAccount));
}

int BalanceEntry::getAccount() const
{
    QString fieldname = SaldoTable::COLUMNNAME[SaldoTable::konten];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setCashKey(int aKey)
{
    setValueOnField(SaldoTable::kasse_pkey, QVariant::Int, QVariant(aKey));
}

int BalanceEntry::getCashKey() const
{
    QString fieldname = SaldoTable::COLUMNNAME[SaldoTable::kasse_pkey];
    return balanceRecord.value(fieldname).toInt();
}

void BalanceEntry::setValueOnField(int aIndex, QVariant::Type aType, const QVariant &aValue)
{
    QString fieldname = SaldoTable::COLUMNNAME[aIndex];
    if(balanceRecord.contains(fieldname) == false) {
        QSqlField field(fieldname, aType);
        balanceRecord.append(field);
    }
    balanceRecord.setValue(fieldname, aValue);
}

}
}
