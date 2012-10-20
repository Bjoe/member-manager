#include "accountingentryimportermain.h"

#include <QTableWidget>

namespace membermanager {
namespace accounting {

AccountingEntryImporterMain::AccountingEntryImporterMain(QWidget *parent) :
    QWidget(parent),
    view(new gui::AccountingEntryImporterView(this)),
    balancePersister(0),
    transactionImporter(0)
{
    QTableWidget *accountingEnrtyTable = view->getAccountingEntryTable();
    balancePersister = new BalancePersister(accountingEnrtyTable, this);

    connect(view, SIGNAL(bookClicked()), balancePersister, SLOT(booking()));
}

} // namespace accounting
} // namespace membermanager
