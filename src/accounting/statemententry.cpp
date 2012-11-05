#include "statemententry.h"

#include <QSqlField>

#include "dao/databasestructure.h"

namespace membermanager
{
namespace accounting
{

StatementEntry::StatementEntry(int aKeyId) : statementRecord()
{
    setValueOnField(dao::KassaTable::kasse_pkey, QVariant::Int, aKeyId);
}

int StatementEntry::getId() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::kasse_pkey];
    return statementRecord.value(columnname).toInt();
}

void StatementEntry::setDeleted(bool deleted)
{
    setValueOnField(dao::KassaTable::deleted, QVariant::Bool, deleted);
}

bool StatementEntry::isDeleted() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::deleted];
    return statementRecord.value(columnname).toBool();
}

void StatementEntry::setDate(QDateTime aDate)
{
    setValueOnField(dao::KassaTable::buchungsdatum, QVariant::DateTime, aDate);
}

QDateTime StatementEntry::getDate() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::buchungsdatum];
    return statementRecord.value(columnname).toDateTime();
}

void StatementEntry::setValuta(QDateTime aValuta)
{
    setValueOnField(dao::KassaTable::valutadatum, QVariant::DateTime, aValuta);
}

QDateTime StatementEntry::getValuta() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::valutadatum];
    return statementRecord.value(columnname).toDateTime();
}

void StatementEntry::setPrimanota(QString aPrimanota)
{
    setValueOnField(dao::KassaTable::einleseid, QVariant::String, aPrimanota);
}

QString StatementEntry::getPrimanota() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::einleseid];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setValue(double aValue)
{
    setValueOnField(dao::KassaTable::betrag, QVariant::Double, aValue);
}

double StatementEntry::getValue() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::betrag];
    return statementRecord.value(columnname).toDouble();
}

void StatementEntry::setTransactionCode(int aCode)
{
    setValueOnField(dao::KassaTable::bankbuschl, QVariant::Int, aCode);
}

int StatementEntry::getTransactionCode() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::bankbuschl];
    return statementRecord.value(columnname).toInt();
}

void StatementEntry::setTransactionText(QString aText)
{
    setValueOnField(dao::KassaTable::buschl, QVariant::String, aText);
}

QString StatementEntry::getTransactionText() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::buschl];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setRemoteName(QString aName)
{
    setValueOnField(dao::KassaTable::fremdname, QVariant::String, aName);
}

QString StatementEntry::getRemoteName() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::fremdname];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setRemoteBankCode(QString aCode)
{
    setValueOnField(dao::KassaTable::fremdblz, QVariant::String, aCode);
}

QString StatementEntry::getRemoteBankCode() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::fremdblz];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setRemoteAccountNumber(QString aNumber)
{
    setValueOnField(dao::KassaTable::fremdktnr, QVariant::String, aNumber);
}

QString StatementEntry::getRemoteAccountNumber() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::fremdktnr];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setPurpose(QString aText)
{
    setValueOnField(dao::KassaTable::bezeichnung, QVariant::String, aText);
}

QString StatementEntry::getPurpose() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::bezeichnung];
    return statementRecord.value(columnname).toString();
}

void StatementEntry::setMemberId(int anId)
{
    setValueOnField(dao::KassaTable::dorfmitglied_pkey, QVariant::Int, anId);
}

int StatementEntry::getMemberId() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::dorfmitglied_pkey];
    return statementRecord.value(columnname).toInt();
}

void StatementEntry::setBooked(bool booked)
{
    setValueOnField(dao::KassaTable::erfasst, QVariant::Bool, booked);
}

bool StatementEntry::isBooked() const
{
    QString columnname = dao::KassaTable::COLUMNNAME[dao::KassaTable::erfasst];
    return statementRecord.value(columnname).toBool();
}

void StatementEntry::setValueOnField(int aIndex, const QVariant::Type aType, const QVariant &aValue)
{
    QString fieldname = dao::KassaTable::COLUMNNAME[aIndex];
    if(statementRecord.contains(fieldname) == false) {
        QSqlField field(fieldname, aType);
        statementRecord.append(field);
    }
    statementRecord.setValue(fieldname, aValue);
}

} // namespace accounting
} // namespace membermanager
