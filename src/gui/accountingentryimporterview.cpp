#include "accountingentryimporterview.h"
#include "ui_accountingentryimporterview.h"

namespace membermanager {
namespace gui {

AccountingEntryImporterView::AccountingEntryImporterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountingEntryImporterView)
{
    ui->setupUi(this);
}

AccountingEntryImporterView::~AccountingEntryImporterView()
{
    delete ui;
}

} // namespace gui
} // namespace membermanager
