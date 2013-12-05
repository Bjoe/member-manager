#ifndef MEMBERMANAGER_ACCOUNTING_TRANSACTIONEXPORTER_H
#define MEMBERMANAGER_ACCOUNTING_TRANSACTIONEXPORTER_H

#include <QObject>
#include <QString>
#include <QTextStream>

#include "dtaus/transaction.h"
#include "dtaus/exporter.h"

#include "sepa/transaction.h"
#include "sepa/exporter.h"

#include "accounting/transactioncreator.h"
#include "accounting/memberaccountingdata.h"

namespace membermanager {
namespace accounting {

class TransactionExporter : public QObject
{
    Q_OBJECT

public:
    TransactionExporter(QString creditorId, QString iban, QString bic, QString name, QString bankAccountNumber, QString bankName, QString bankCode);
    void addTransaction(MemberAccountingData* accountingData);
    void out(QTextStream &sepaStream, QTextStream &dtausStream, QTextStream &csvStream);

signals:
    void logMessage(QString);

private:
    TransactionCreator m_transactionCreator;
    qaqbanking::sepa::Exporter m_exporter;
    qaqbanking::dtaus::Exporter m_dtausExporter;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_TRANSACTIONEXPORTER_H
