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

void AccountingHandler::setMemberList(const QList<QObject *> &memberList)
{
    m_memberList = memberList;
    emit memberListChanged();
}

QList<QObject *> AccountingHandler::memberList() const
{
    return m_memberList;
}

void AccountingHandler::setAccountingInfo(const QString &accountingInfo)
{
    m_accountingInfo = accountingInfo;
}

void AccountingHandler::setPurposeInfo(const QString &purposeInfo)
{
    m_purposeInfo = purposeInfo;
}

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

    for(QObject* object : m_memberList) {
        entity::Member* member = qobject_cast<entity::Member *>(object);
        accounting::MemberAccountingData data(member);

        transaction.accounting(data, m_accountingInfo);

        if(data.canCharge()) {
            qiabanking::dtaus::Transaction dtausTransaction = transaction.createDtausTransaction(data, m_accountingInfo);
            exporter.addTransaction(dtausTransaction);
            transaction.collectionAccounting(data, m_accountingInfo);
        }
    }

    QString dtausFilename = QString("%1.txt").arg(filename);
    exporter.createDtausFile(dtausFilename);
}

} // namespace gui
} // namespace membermanager
