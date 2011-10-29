#include "gui/saldosumdialog.h"

#include <QSqlDatabase>

namespace membermanager
{
namespace gui
{

SaldoSumDialog::SaldoSumDialog(model::SaldoSumModel &aModel, QWidget *aParent)
    : QDialog(aParent)
{
    ui.setupUi(this);

    aModel.initTableView(ui.tableView);
}

}
}
