#ifndef MEMBERCONTRIBUTION_H
#define MEMBERCONTRIBUTION_H

#include <QtCore>
#include <QSqlRecord>

namespace membermanager
{

class MemberContribution
{
public:
    MemberContribution(int anId);

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
    QSqlRecord contributionRecord;
};

}

#endif // MEMBERCONTRIBUTION_H
