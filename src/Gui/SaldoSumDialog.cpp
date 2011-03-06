#include "Gui/SaldoSumDialog.h"

#include <QSqlDatabase>

namespace ClubFrontend
{
namespace Gui
{
  
SaldoSumDialog::SaldoSumDialog ( Model::SaldoSumModel& aModel, QWidget* aParent )
        : QDialog ( aParent )
{
    ui.setupUi ( this );

    aModel.initTableView ( ui.tableView );
}

}
}
