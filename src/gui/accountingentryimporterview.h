#ifndef MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H
#define MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H

#include <QWidget>
#include <QTableWidget>

#include "dao/cashaccountdao.h"

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
    void import();
    void book();

private:
    Ui::AccountingEntryImporterView *ui;
    dao::CashAccountDao cashAccountdao;
};


} // namespace gui
} // namespace membermanager
#endif // MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H
