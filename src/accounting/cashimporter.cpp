#include "cashimporter.h"

#include <QSettings>

#include "swift/importer.h"

#include "entity/cashaccount.h"

namespace membermanager {
namespace accounting {

CashImporter::CashImporter()
{
}

QList<qaqbanking::swift::Transaction *> CashImporter::loadFromFilename(const QString &filename)
{
    QSettings settings;
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();

    qaqbanking::swift::Importer importer(bankCode, accountNumber);
    return importer.importMt940Swift(filename);
}

void CashImporter::import(QList<qaqbanking::swift::Transaction *> transactions)
{
    entity::CashAccount *cashaccount = nullptr;
    for(qaqbanking::swift::Transaction *transaction : transactions) {
        cashaccount = new entity::CashAccount();
        cashaccount->setValuta(transaction->valutaDate());
        cashaccount->setDate(transaction->date());
        cashaccount->setRemoteName(transaction->remoteName());
        cashaccount->setRemoteBankCode(transaction->remoteBankCode());
        cashaccount->setRemoteAccountNumber(transaction->remoteAccountNumber());
        cashaccount->setValue(transaction->value());
        cashaccount->setPurpose(transaction->purpose());
        cashaccount->setTransactionCode(transaction->transactionCode());
        cashaccount->setTransactionText(transaction->transactionText());
        cashaccount->setState("imported");
        cashaccount->save();
        delete cashaccount;
    }
}

} // namespace accounting
} // namespace membermanager
