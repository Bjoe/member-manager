#include "membercontribution.h"

#include "model/databasestructure.h"
#include "model/memberdao.h"

namespace membermanager
{

MemberContribution::MemberContribution(int anId) :
    contributionRecord()
{
    model::MemberDao dao(QSqlDatabase::database());

    contributionRecord = dao.getRecordWithMemberId(model::ContributionTable::TABLENAME, anId
                         , model::ContributionTable::ValidFrom
                         , Qt::DescendingOrder);
}

bool MemberContribution::save()
{
    model::MemberDao dao(QSqlDatabase::database());

    return dao.saveRecordWithMemberId(model::ContributionTable::TABLENAME, contributionRecord
                                      , model::ContributionTable::ValidFrom
                                      , Qt::DescendingOrder);
}

bool MemberContribution::saveNewRecord()
{
    contributionRecord.setNull(model::ContributionTable::ContributionId);

    model::MemberDao dao(QSqlDatabase::database());

    return dao.saveNewRecordWithMemberId(model::ContributionTable::TABLENAME, contributionRecord
                                         , model::ContributionTable::ValidFrom
                                         , Qt::DescendingOrder);
}

double MemberContribution::getFee() const
{
    return contributionRecord.value(model::ContributionTable::Fee).toDouble();
}

void MemberContribution::setFee(double aFee)
{
    contributionRecord.setValue(model::ContributionTable::Fee, QVariant(aFee));
}

double MemberContribution::getDonation() const
{
    return contributionRecord.value(model::ContributionTable::Donation).toDouble();
}

void MemberContribution::setDonation(double aDonation)
{
    contributionRecord.setValue(model::ContributionTable::Donation, QVariant(aDonation));
}

QString MemberContribution::getInfo() const
{
    return contributionRecord.value(model::ContributionTable::Info).toString();
}

void MemberContribution::setInfo(const QString &aText)
{
    contributionRecord.setValue(model::ContributionTable::Info, QVariant(aText));
}

QDate MemberContribution::getValidFrom() const
{
    return contributionRecord.value(model::ContributionTable::ValidFrom).toDate();
}

void MemberContribution::setValidFrom(const QDate &aDate)
{
    contributionRecord.setValue(model::ContributionTable::ValidFrom, QVariant(aDate));
}

}
