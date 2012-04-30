#include "cashsumsummary.h"

#include <QSqlDatabase>
#include <QDate>
#include <QMap>

#include "dao/contributiondao.h"
#include "dao/balancedao.h"
#include "accounting/contributionentry.h"
#include "accounting/balanceentry.h"

namespace membermanager
{

CashSumSummary::CashSumSummary(const QList<Member> &aMemberList) :
    memberList(aMemberList), writer(0)
{
}

QString CashSumSummary::getTitle() const
{
    return QString("Einahmen");
}

void CashSumSummary::setWriter(SummaryWriter *aWriter)
{
    writer = aWriter;
}

void CashSumSummary::handleHtmlText()
{
    QDate date = QDate::currentDate();
    dao::ContributionDao contributionDao(QSqlDatabase::database());
    dao::BalanceDao balanceDao(QSqlDatabase::database());
    QMap<double, double> sumMap;
    QMap<double, int> countMember;
    double total = 0;
    double donationTotal = 0;
    double saldoSum = 0;
    int memberSum = 0;
    int memberCollection = 0;
    double totalCollection = 0;

    foreach(Member member, memberList) {
         int memberId = member.getMemberId();
         memberSum++;

        QList<accounting::BalanceEntry> balanceList = balanceDao.findByMemberId(memberId);
        accounting::BalanceEntry balanceEntry;
        foreach(balanceEntry, balanceList) {
            saldoSum += balanceEntry.getValue();
        }

        accounting::ContributionEntry contributionEntry = contributionDao.findByMemberIdWithPointInTime(memberId, date);
        double donation = contributionEntry.getDonation();
        donationTotal += donation;
        double fee = contributionEntry.getFee();
        total += fee;

        if(member.isCollection()) {
            memberCollection++;
            totalCollection = totalCollection + fee + donation;
        }

        if(sumMap.contains(fee)) {
            double sum = sumMap.value(fee);
            sum += fee;
            sumMap.insert(fee, sum);
            int count = countMember.value(fee);
            count++;
            countMember.insert(fee, count);
        } else {
            sumMap.insert(fee, fee);
            countMember.insert(fee, 1);
        }

    }
    total += donationTotal;

    foreach(double feeKey, sumMap.keys()) {
        QString htmlText = QString(tr("Anzahl %1 * Beitrag %2 Gesamt = %3<br>"))
                .arg(countMember.value(feeKey)).arg(feeKey).arg(sumMap.value(feeKey));
        writer->writeContent(htmlText);
    }
    QString htmlTextDonation = QString(tr("<br>Gesamt Spenden: %1<br><br>")).arg(donationTotal);
    writer->writeContent(htmlTextDonation);
    QString htmlTextSum = QString(tr("Gesamt Mitglieder: %1 Einahmen: %2<br><br>")).arg(memberSum).arg(total);
    writer->writeContent(htmlTextSum);
    QString htmlTextCollection = QString(tr("Gesamt Einzuege Mitglieder: %1 Einahmen: %2<br><br>")).arg(memberCollection).arg(totalCollection);
    writer->writeContent(htmlTextCollection);
    QString htmlTextSaldoSum = QString(tr("Gesamt Saldo: %1<br>")).arg(saldoSum);
    writer->writeContent(htmlTextSaldoSum);
    QString htmlTextDate = QString(tr("Stand: %1<br>")).arg(date.toString());
    writer->writeContent(htmlTextDate);
}

}
