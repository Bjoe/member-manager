#ifndef MEMBERMANAGER_ACCOUNTING_ACCOUNTINGENTRYIMPORTERMAIN_H
#define MEMBERMANAGER_ACCOUNTING_ACCOUNTINGENTRYIMPORTERMAIN_H

#include <QWidget>

#include "gui/accountingentryimporterview.h"
#include "balancepersister.h"
#include "transactionimporter.h"

namespace membermanager {
namespace accounting {

class AccountingEntryImporterMain : public QWidget
{
    Q_OBJECT
public:
    explicit AccountingEntryImporterMain(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    gui::AccountingEntryImporterView *view;
    BalancePersister *balancePersister;
    TransactionImporter *transactionImporter;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_ACCOUNTINGENTRYIMPORTERMAIN_H
