#include "cashimporter.h"

#include <QSettings>

#include "swift/importer.h"

#include "entity/cashaccount.h"

namespace membermanager {
namespace accounting {

CashImporter::CashImporter()
{
}

QList<qiabanking::swift::Transaction *> CashImporter::loadFromFilename(const QString &filename)
{
    QSettings settings;
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();

    qiabanking::swift::Importer importer(bankCode, accountNumber);
    return importer.importMt940Swift(filename);
}

void CashImporter::import(QList<qiabanking::swift::Transaction *> transactions)
{
    entity::CashAccount *cashaccount = nullptr;
    for(qiabanking::swift::Transaction *transaction : transactions) {
        cashaccount = new entity::CashAccount();
        cashaccount->setValuta(transaction->getValutaDate());
        cashaccount->setDate(transaction->getDate());
        cashaccount->setRemoteName(transaction->getRemoteName());
        cashaccount->setRemoteBankCode(transaction->getRemoteBankCode());
        cashaccount->setRemoteAccountNumber(transaction->getRemoteAccountNumber());
        cashaccount->setValue(transaction->getValue());
        cashaccount->setPurpose(transaction->getPurpose());
        cashaccount->setTransactionCode(transaction->getTransactionCode());
        cashaccount->setTransactionText(transaction->getTransactionText());
        cashaccount->setState("imported");
        cashaccount->save();
        delete cashaccount;
    }
}

} // namespace accounting
} // namespace membermanager
