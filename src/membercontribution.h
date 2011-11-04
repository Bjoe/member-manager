#ifndef MEMBERCONTRIBUTION_H
#define MEMBERCONTRIBUTION_H

#include <QtCore>
#include <QSqlRecord>
#include "model/memberfilter.h"

namespace membermanager
{

class MemberContribution
{
public:
    MemberContribution(const model::MemberFilter &aFilter);

    double getFee() const;
    void setFee(double aFee);
    double getDonation() const;
    void setDonation(double aDonation);
    QString getInfo() const;
    void setInfo(const QString &aText);
    QDate getValidFrom() const;
    void setValidFrom(const QDate &aDate);

    bool save();
    bool saveNewRecord();

private:
    const model::MemberFilter &filter;
    QSqlRecord contributionRecord;
};

}

#endif // MEMBERCONTRIBUTION_H
