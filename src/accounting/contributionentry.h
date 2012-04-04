#ifndef MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONENTRY_H
#define MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONENTRY_H

#include <QString>
#include <QVariant>
#include <QDate>
#include <QSqlRecord>

#include "model/contributiondao.h"

namespace membermanager {
namespace model {

class ContributionDao;

}
namespace accounting {

class ContributionEntry
{
public:
    ContributionEntry(int aMemberId);

    int getMemberId() const;
    double getFee() const;
    void setFee(double aFee);
    double getDonation() const;
    void setDonation(double aDonation);
    QString getInfo() const;
    void setInfo(const QString &aText);
    QDate getValidFrom() const;
    void setValidFrom(const QDate &aDate);

    friend class model::ContributionDao;

private:
    QSqlRecord contributionRecord;

    void setValueOnField(int aIndex, QVariant::Type aType, const QVariant &aValue);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONENTRY_H
