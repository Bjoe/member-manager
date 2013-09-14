#ifndef MEMBERMANAGER_ACCOUNTING_CASHIMPORTER_H
#define MEMBERMANAGER_ACCOUNTING_CASHIMPORTER_H

#include <QString>
#include <QList>

#include "swift/transaction.h"

namespace membermanager {
namespace accounting {

class CashImporter
{
public:
    CashImporter();

    QList<qiabanking::swift::Transaction *> loadFromFilename(const QString &filename);

    void import(QList<qiabanking::swift::Transaction *> transactions);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_CASHIMPORTER_H