#ifndef MEMBERMANAGER_ACCOUNTING_TRANSACTIONCREATOR_H
#define MEMBERMANAGER_ACCOUNTING_TRANSACTIONCREATOR_H

#include <QString>
#include <QTextStream>
#include <QDate>

#include "dtaus/exporter.h"
#include "dtaus/transaction.h"

#include "sepa/exporter.h"
#include "sepa/transaction.h"

#include "accounting/memberaccountingdata.h"

namespace membermanager {
namespace accounting {

class TransactionCreator
{
public:
    TransactionCreator(QString accountNumber, QString bankCode, QString bankName,
                       QString name, QString creditorId, QString iban, QString bic);

    qaqbanking::dtaus::TransactionPtr createDtausTransaction(const MemberAccountingData* memberData);
    qaqbanking::sepa::TransactionPtr createTransaction(const MemberAccountingData* accountingData);

    void out(QTextStream& stream);

private:
    QString m_accountNumber;
    QString m_bankCode;
    QString m_bankName;
    QString m_name;
    QString m_creditorId;
    QString m_iban;
    QString m_bic;
    QString m_transaction;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_TRANSACTIONCREATOR_H
