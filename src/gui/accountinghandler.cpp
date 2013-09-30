#include "accountinghandler.h"

#include <QSettings>
#include <QTextStream>
#include <QFile>

#include "dtaus/exporter.h"
#include "dtaus/transaction.h"

#include "entity/member.h"

#include "accounting/memberaccountingdata.h"
#include "accounting/accounttransaction.h"

namespace membermanager {
namespace gui {

AccountingHandler::AccountingHandler(QObject *parent) :
    QObject(parent)
{
}

void AccountingHandler::setAccountingDataList(const QList<QObject *> &list)
{
    m_memberAccountingDataList = list;
    emit accountingDataListChanged();
}

QList<QObject *> AccountingHandler::accountingDataList() const
{
    return m_memberAccountingDataList;
}

/*
 *    m_memberId = QVariant(member->memberId());
    m_name = member->name();
    m_firstname = member->firstname();
    m_collectionState = member->collectionState();

    entity::BankAccount *bankaccount = dao::BankAccountTableModel::findByMemberId(m_memberId);
    m_bankAccountNumber = bankaccount->accountNumber();
    m_bankCode = bankaccount->code();

    entity::Contribution *contribution = dao::ContributionTableModel::findByMemberIdWithPointInTime(m_memberId, date);
    m_fee = contribution->fee();
    m_donation = contribution->donation();
    m_additionalFee = contribution->additionalFee();
    m_additionalDonation = contribution->additionalDonation();
    m_amortization = contribution->amortization();

 */

void AccountingHandler::book(const QString &filename)
{
    QString csvFilename = QString("%1.csv").arg(filename);
    QFile csvFile(csvFilename);

    if(! csvFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&csvFile);

    QSettings settings;
    QString bankAccountNumber = settings.value("bank/account").toString();
    QString bankName = settings.value("bank/name").toString();
    QString bankCode = settings.value("bank/code").toString();

    accounting::AccountTransaction transaction(bankAccountNumber, bankCode, bankName, stream);

    qiabanking::dtaus::Exporter exporter(bankAccountNumber, bankName,bankCode, "EUR");

    for(QObject* object : m_memberAccountingDataList) {
        accounting::MemberAccountingData* data = qobject_cast<accounting::MemberAccountingData *>(object);

        transaction.accounting(data);

        if(data->canCharge()) {
            qiabanking::dtaus::Transaction dtausTransaction = transaction.createDtausTransaction(data);
            exporter.addTransaction(dtausTransaction);
            transaction.collectionAccounting(data);
        }
    }

    QString dtausFilename = QString("%1.txt").arg(filename);
    exporter.createDtausFile(dtausFilename);
}

} // namespace gui
} // namespace membermanager
