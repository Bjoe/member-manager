#ifndef MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONENTRY_H
#define MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONENTRY_H

#include <QString>
#include <QVariant>
#include <QDate>
#include <QSqlRecord>

#include "dao/contributiondao.h"

namespace membermanager {
namespace dao {

class ContributionDao;

}
namespace accounting {

class ContributionEntry
{
public:
    ContributionEntry(int aMemberId = 0);

    int getMemberId() const;
    double getFee() const;
    void setFee(double aFee);
    double getAdditionalFee() const;
    void setAdditionalFee(double aFee);
    double getDonation() const;
    void setDonation(double aDonation);
    QString getInfo() const;
    void setInfo(const QString &aText);
    QDate getValidFrom() const;
    void setValidFrom(const QDate &aDate);

    friend class dao::ContributionDao;

private:
    QSqlRecord contributionRecord;

    void setValueOnField(int aIndex, QVariant::Type aType, const QVariant &aValue);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONENTRY_H
