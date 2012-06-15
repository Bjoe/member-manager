#include "pay.h"

#include "contributionentry.h"
#include "balanceentry.h"
#include "dtaustransactionbuilder.h"
#include "transaction.h"

namespace membermanager {
namespace accounting {

Pay::Pay(const QString &anAccountNumber, const QString &aBankName, const QString &aBankCode) :
   exporter(anAccountNumber,aBankName,aBankCode,"EUR"), data(), sum(), contributionDao(), balanceDao(),
    accountNumber(anAccountNumber), bankCode(aBankCode), bankName(aBankName)
{
    sum << 0.0 << 0.0;
}

bool Pay::payment(const Member &aMember, const QString &aMonth, const QDate &aDate, bool withBooking)
{
    bool isOk = false;

    int memberId = aMember.getMemberId();

    ContributionEntry contributionEntry = contributionDao.findByMemberIdWithPointInTime(memberId, aDate);
    double fee = contributionEntry.getFee();
    double donation = contributionEntry.getDonation();

    if(aMember.isCollection()) {
        QString name;
        name.append(aMember.getName()).append(' ').append(aMember.getFirstname());

        data.append(QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag %2;%3\n").arg(aDate.toString("dd.MM.yyyy")).arg(name).arg(fee));
        sum[0] += fee;

        QString withDonation = "";
        if(donation > 0) {
            withDonation = "und Spende ";
            sum[1] += donation;
            data.append(QString("%1;Lastschrift Einzug 012;012 Spende %2;%3\n").arg(aDate.toString("dd.MM.yyyy")).arg(name).arg(donation));
        }

        QString purpose = QString("%1 Mitgliedsbeitrag %2%3").arg(memberId).arg(withDonation).arg(aMonth);
        qiabanking::Transaction transaction = qiabanking::DtausTransactionBuilder()
                .withLocalName(bankName)
                .withLocalAccountNumber(accountNumber)
                .withLocalBankCode(bankCode)
                .withRemoteName(name)
                .withRemoteAccountNumber(aMember.getAccountNr())
                .withRemoteBankCode(aMember.getCode())
                .withValue(fee + donation)
                .withTextKey(5)
                .withPurpose(purpose)
                .build();
        exporter.addTransaction(transaction);
    }

    if(withBooking) {
        BalanceEntry balanceEntry(memberId);
        balanceEntry.setValuta(aDate);
        balanceEntry.setValue(fee * -1);
        balanceEntry.setPurpose(QString("Mitgliedsbeitrag %1").arg(aMonth));
        balanceEntry.setInfo("Automatische Monats Abbuchung");
        balanceDao.saveRecord(balanceEntry);
        if(aMember.isCollection()) {
            balanceEntry.setValue(fee);
            balanceEntry.setInfo("Automatische Monats Lastschrift");
            balanceEntry.setAccount(11);
            balanceDao.saveRecord(balanceEntry);
        }

        if(donation > 0) {
            BalanceEntry donationEntry(memberId);
            donationEntry.setValuta(aDate);
            donationEntry.setValue(donation * -1);
            donationEntry.setPurpose(QString("Spende %1").arg(aMonth));
            donationEntry.setInfo("Automatische Monats Abbuchung");
            balanceDao.saveRecord(donationEntry);
            if(aMember.isCollection()) {
                donationEntry.setValue(donation);
                donationEntry.setInfo("Automatische Monats Lastschrift");
                donationEntry.setAccount(12);
                balanceDao.saveRecord(donationEntry);
            }
        }
   }

    return isOk;
}

QList<double> Pay::balancing(const QString &aFilename)
{
    QString dtausFilename = QString("%1.txt").arg(aFilename);
    exporter.createDtausFile(dtausFilename);

    QString csvFilename = QString("%1.csv").arg(aFilename);
    QFile csvFile(csvFilename);

    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&csvFile);
        out << data;
        csvFile.close();
    }
    return sum;
}

} // namespace accounting
} // namespace membermanager
