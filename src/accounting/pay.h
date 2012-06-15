#ifndef MEMBERMANAGER_ACCOUNTING_PAY_H
#define MEMBERMANAGER_ACCOUNTING_PAY_H

#include <QString>
#include <QDate>
#include <QByteArray>
#include <QList>
#include "member.h"
#include "dao/contributiondao.h"
#include "dao/balancedao.h"
#include "exporter.h"

namespace membermanager {
namespace accounting {

class Pay
{
public:
    Pay(const QString &anAccountNumber, const QString &aBankName, const QString &aBankCode);

    bool payment(const Member &aMember, const QString &aMonth, const QDate &aDate, bool withBooking = false);

    QList<double> balancing(const QString &aFilename);

private:
    dao::ContributionDao contributionDao;
    dao::BalanceDao balanceDao;
    qiabanking::Exporter exporter;
    QByteArray data;
    QList<double> sum;
    QString accountNumber;
    QString bankCode;
    QString bankName;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_PAY_H
