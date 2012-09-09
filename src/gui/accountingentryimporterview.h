#ifndef MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H
#define MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H

#include <QWidget>

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
    
private:
    Ui::AccountingEntryImporterView *ui;
};


} // namespace gui
} // namespace membermanager
#endif // MEMBERMANAGER_GUI_ACCOUNTINGENTRYIMPORTERVIEW_H
