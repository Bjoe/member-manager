#include "transactionexporter.h"

namespace membermanager {
namespace accounting {

TransactionExporter::TransactionExporter(QString creditorId, QString iban, QString bic, QString name, QString bankAccountNumber, QString bankName, QString bankCode)
    : m_transactionCreator(bankAccountNumber, bankCode, bankName, name, creditorId, iban, bic),
      m_exporter(iban, bic, name),
      m_dtausExporter(bankAccountNumber, bankName, bankCode, "EUR")
{
    connect(&m_exporter, &qaqbanking::sepa::Exporter::logMessage, this, &TransactionExporter::logMessage);
    connect(&m_dtausExporter, &qaqbanking::dtaus::Exporter::logMessage, this, &TransactionExporter::logMessage);
}

void TransactionExporter::addTransaction(MemberAccountingData* accountingData)
{
    qaqbanking::sepa::TransactionPtr transaction = m_transactionCreator.createTransaction(accountingData);
    m_exporter.addTransaction(transaction);

    qaqbanking::dtaus::TransactionPtr dtausTransaction = m_transactionCreator.createDtausTransaction(accountingData);
    m_dtausExporter.addTransaction(dtausTransaction);
}

void TransactionExporter::out(QTextStream& sepaStream, QTextStream& dtausStream, QTextStream& csvStream)
{
    m_exporter.createSepaDirectDebitStream(&sepaStream);
    m_dtausExporter.createDtausStream(&dtausStream);
    m_transactionCreator.out(csvStream);
}

} // namespace accounting
} // namespace membermanager
