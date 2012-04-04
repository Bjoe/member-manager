#include "balanceentry.h"

#include <QVariant>
#include <QSqlField>

#include "model/databasestructure.h"

namespace membermanager
{
namespace accounting
{
using model::SaldoTable;

BalanceEntry::BalanceEntry(int aMemberId) : balanceRecord()
{
    appendAndSetField(SaldoTable::dorfmitglied_pkey, QVariant::Int, QVariant(aMemberId));
}

int BalanceEntry::getMemberId() const
{
    return balanceRecord.value(SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey]).toInt();
}

void BalanceEntry::setValue(double aValue)
{
    appendAndSetField(SaldoTable::betrag, QVariant::Double, QVariant(aValue));
}

double BalanceEntry::getValue() const
{
    return balanceRecord.value(SaldoTable::COLUMNNAME[SaldoTable::betrag]).toDouble();
}

void BalanceEntry::setValuta(const QDate &aDate)
{
    appendAndSetField(SaldoTable::datum, QVariant::Date, QVariant(aDate));
}

QDate BalanceEntry::getValuta() const
{
   return balanceRecord.value(SaldoTable::COLUMNNAME[SaldoTable::datum]).toDate();
}

void BalanceEntry::setPurpose(const QString &aPurpose)
{
    appendAndSetField(SaldoTable::bezeichnung, QVariant::String, QVariant(aPurpose));
}

QString BalanceEntry::getPurpose() const
{
    return balanceRecord.value(SaldoTable::COLUMNNAME[SaldoTable::bezeichnung]).toString();
}

void BalanceEntry::setInfo(const QString &anInfo)
{
    appendAndSetField(SaldoTable::info, QVariant::String, QVariant(anInfo));
}

QString BalanceEntry::getInfo() const
{
    return balanceRecord.value(SaldoTable::COLUMNNAME[SaldoTable::info]).toString();
}

void BalanceEntry::setAccount(int anAccount)
{
    appendAndSetField(SaldoTable::konten, QVariant::Int, QVariant(anAccount));
}

int BalanceEntry::getAccount() const
{
    return balanceRecord.value(SaldoTable::COLUMNNAME[SaldoTable::konten]).toInt();
}

void BalanceEntry::appendAndSetField(int aIndex, QVariant::Type aType, const QVariant &aValue)
{
    QSqlField field(SaldoTable::COLUMNNAME[aIndex], aType);
    field.setValue(aValue);
    balanceRecord.append(field);
}

}
}
