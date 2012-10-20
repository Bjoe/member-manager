#ifndef MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H
#define MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H

#include <QVariant>
#include <QWidget>

#include "accounting/balancepersister.h"

namespace membermanager
{
namespace gui
{

namespace Ui
{
class AccountingEntryImporterView;
}

class AccountingEntryImporterView : public QWidget
{
    Q_OBJECT
    
public:
    explicit AccountingEntryImporterView(QWidget *parent = 0);
    ~AccountingEntryImporterView();

private slots:
    void importTransactions();
    
private:
    Ui::AccountingEntryImporterView *ui;
    accounting::BalancePersister* balancePersister;
};


} // namespace gui
} // namespace membermanager
#endif // MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H
