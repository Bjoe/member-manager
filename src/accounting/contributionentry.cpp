#include "contributionentry.h"

#include <QSqlField>

#include "dao/databasestructure.h"

namespace membermanager
{
namespace accounting
{

using dao::ContributionTable;

ContributionEntry::ContributionEntry(int aMemberId) : contributionRecord()
{
    setValueOnField(ContributionTable::MemberId, QVariant::Int, QVariant(aMemberId));
}

int ContributionEntry::getMemberId() const
{
    QString fieldname = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    return contributionRecord.value(fieldname).toInt();
}

double ContributionEntry::getFee() const
{
    QString fieldname = ContributionTable::COLUMNNAME[ContributionTable::Fee];
    return contributionRecord.value(fieldname).toDouble();
}

void ContributionEntry::setFee(double aFee)
{
    setValueOnField(ContributionTable::Fee, QVariant::Double, QVariant(aFee));
}

double ContributionEntry::getAdditionalFee() const
{
    QString fieldname = ContributionTable::COLUMNNAME[ContributionTable::AdditionalFee];
    return contributionRecord.value(fieldname).toDouble();
}

void ContributionEntry::setAdditionalFee(double aFee)
{
    setValueOnField(ContributionTable::AdditionalFee, QVariant::Double, QVariant(aFee));
}

double ContributionEntry::getDonation() const
{
    QString fieldname = ContributionTable::COLUMNNAME[ContributionTable::Donation];
    return contributionRecord.value(fieldname).toDouble();
}

void ContributionEntry::setDonation(double aDonation)
{
    setValueOnField(ContributionTable::Donation, QVariant::Double, QVariant(aDonation));
}

QString ContributionEntry::getInfo() const
{
    QString fieldname = ContributionTable::COLUMNNAME[ContributionTable::Info];
    return contributionRecord.value(fieldname).toString();
}

void ContributionEntry::setInfo(const QString &aText)
{
    setValueOnField(ContributionTable::Info, QVariant::String, QVariant(aText));
}

QDate ContributionEntry::getValidFrom() const
{
    QString fieldname = ContributionTable::COLUMNNAME[ContributionTable::ValidFrom];
    return contributionRecord.value(fieldname).toDate();
}

void ContributionEntry::setValidFrom(const QDate &aDate)
{
    setValueOnField(ContributionTable::ValidFrom, QVariant::Date, QVariant(aDate));
}

void ContributionEntry::setValueOnField(int aIndex, QVariant::Type aType, const QVariant &aValue)
{
    QString fieldname = ContributionTable::COLUMNNAME[aIndex];
    if(contributionRecord.contains(fieldname) == false) {
        QSqlField field(fieldname, aType);
        contributionRecord.append(field);
    }
    contributionRecord.setValue(fieldname, aValue);
}

} // namespace accounting
} // namespace membermanager
