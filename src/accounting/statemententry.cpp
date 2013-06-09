#include "statemententry.h"

#include <QSqlField>

#include "dao/databasestructure.h"

namespace membermanager
{
namespace accounting
{

StatementEntry::StatementEntry(int aKeyId) : statementRecord()
{
    setValueOnField(dao::CashTable::kasse_pkey, QVariant::Int, aKeyId);
}

int StatementEntry::getId() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::kasse_pkey];
    return statementRecord.value(columnname).toInt();
}

void StatementEntry::setDeleted(bool deleted)
{
    setValueOnField(dao::CashTable::deleted, QVariant::Bool, deleted);
}

bool StatementEntry::isDeleted() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::deleted];
    return statementRecord.value(columnname).toBool();
}

void StatementEntry::setDate(QDateTime aDate)
{
    setValueOnField(dao::CashTable::buchungsdatum, QVariant::DateTime, aDate);
}

QDateTime StatementEntry::getDate() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::buchungsdatum];
    return statementRecord.value(columnname).toDateTime();
}

void StatementEntry::setValuta(QDateTime aValuta)
{
    setValueOnField(dao::CashTable::valutadatum, QVariant::DateTime, aValuta);
}

QDateTime StatementEntry::getValuta() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::valutadatum];
    return statementRecord.value(columnname).toDateTime();
}

void StatementEntry::setPrimanota(QString aPrimanota)
{
    setValueOnField(dao::CashTable::einleseid, QVariant::String, aPrimanota);
}

QString StatementEntry::getPrimanota() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::einleseid];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setValue(double aValue)
{
    setValueOnField(dao::CashTable::betrag, QVariant::Double, aValue);
}

double StatementEntry::getValue() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::betrag];
    return statementRecord.value(columnname).toDouble();
}

void StatementEntry::setTransactionCode(int aCode)
{
    setValueOnField(dao::CashTable::bankbuschl, QVariant::Int, aCode);
}

int StatementEntry::getTransactionCode() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::bankbuschl];
    return statementRecord.value(columnname).toInt();
}

void StatementEntry::setTransactionText(QString aText)
{
    setValueOnField(dao::CashTable::buschl, QVariant::String, aText);
}

QString StatementEntry::getTransactionText() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::buschl];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setRemoteName(QString aName)
{
    setValueOnField(dao::CashTable::fremdname, QVariant::String, aName);
}

QString StatementEntry::getRemoteName() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::fremdname];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setRemoteBankCode(QString aCode)
{
    setValueOnField(dao::CashTable::fremdblz, QVariant::String, aCode);
}

QString StatementEntry::getRemoteBankCode() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::fremdblz];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setRemoteAccountNumber(QString aNumber)
{
    setValueOnField(dao::CashTable::fremdktnr, QVariant::String, aNumber);
}

QString StatementEntry::getRemoteAccountNumber() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::fremdktnr];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setPurpose(QString aText)
{
    setValueOnField(dao::CashTable::bezeichnung, QVariant::String, aText);
}

QString StatementEntry::getPurpose() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::bezeichnung];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setMemberId(int anId)
{
    setValueOnField(dao::CashTable::dorfmitglied_pkey, QVariant::Int, anId);
}

int StatementEntry::getMemberId() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::dorfmitglied_pkey];
    return statementRecord.value(columnname).toInt();
}

void StatementEntry::setBooked(bool booked)
{
    setValueOnField(dao::CashTable::erfasst, QVariant::Bool, booked);
}

bool StatementEntry::isBooked() const
{
    QString columnname = dao::CashTable::COLUMNNAME[dao::CashTable::erfasst];
    return statementRecord.value(columnname).toBool();
}

void StatementEntry::setValueOnField(int aIndex, const QVariant::Type aType, const QVariant &aValue)
{
    QString fieldname = dao::CashTable::COLUMNNAME[aIndex];
    if(statementRecord.contains(fieldname) == false) {
        QSqlField field(fieldname, aType);
        statementRecord.append(field);
    }
    statementRecord.setValue(fieldname, aValue);
}

} // namespace accounting
} // namespace membermanager
