#include "cashimporter.h"

#include <QSettings>

#include "entity/cashaccount.h"

namespace membermanager {
namespace accounting {

CashImporter::CashImporter(QTextStream *stream) : m_stream(stream), m_logCb([](QString){})
{
}

void CashImporter::logMessageSlot(std::function<void (QString)> logCb)
{
    m_logCb = logCb;
}

bool CashImporter::import(const QString bankCode, const QString accountNumber)
{
    qaqbanking::swift::Importer importer(bankCode, accountNumber);
    QObject::connect(&importer, &qaqbanking::swift::Importer::logMessage, m_logCb);

    return importer.importMt940Swift(m_stream,
        [](qaqbanking::swift::TransactionPtr transaction)
        {
            entity::CashAccount* cashAccount = new entity::CashAccount();

            cashAccount->setRemoteName(transaction->remoteName());
            cashAccount->setRemoteBankCode(transaction->remoteBankCode());
            cashAccount->setRemoteAccountNumber(transaction->remoteAccountNumber());
            cashAccount->setValue(transaction->value());
            cashAccount->setValuta(transaction->valutaDate());
            cashAccount->setDate(transaction->date());
            cashAccount->setPurpose(transaction->purpose());
            cashAccount->setTransactionText(transaction->transactionText());
            cashAccount->setTransactionCode(transaction->transactionCode());
            cashAccount->setPrimanota(transaction->primanota());
            cashAccount->setState("imported");

            cashAccount->save();
            delete cashAccount;
        }
    );
}

} // namespace accounting
} // namespace membermanager
