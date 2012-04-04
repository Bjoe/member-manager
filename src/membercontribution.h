#ifndef MEMBERCONTRIBUTION_H
#define MEMBERCONTRIBUTION_H

#include <QtCore>
#include <QSqlRecord>

namespace membermanager
{
/// \todo Refactor to ContributionEntry
class MemberContribution
{
public:
    MemberContribution(int aMemberId);

    double getFee() const;
    void setFee(double aFee);
    double getDonation() const;
    void setDonation(double aDonation);
    QString getInfo() const;
    void setInfo(const QString &aText);
    QDate getValidFrom() const;
    void setValidFrom(const QDate &aDate);
/// \todo Refactor to ContributionDao
    bool save();
    bool saveNewRecord();

private:
    int memberId;
    QSqlRecord contributionRecord;
};

}

#endif // MEMBERCONTRIBUTION_H
