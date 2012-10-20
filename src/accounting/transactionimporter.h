#ifndef MEMBERMANAGER_ACCOUNTING_TRANSACTIONIMPORTER_H
#define MEMBERMANAGER_ACCOUNTING_TRANSACTIONIMPORTER_H

#include <QObject>

namespace membermanager
{
namespace accounting
{

class TransactionImporter : public QObject
{
    Q_OBJECT

public:
    TransactionImporter(QObject *parent = 0);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_TRANSACTIONIMPORTER_H
