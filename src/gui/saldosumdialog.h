#ifndef SALDOSUMDIALOG_H
#define SALDOSUMDIALOG_H

#include <QtGui/QDialog>
#include "ui_saldosumdialog.h"

#include "model/saldosummodel.h"

namespace ClubFrontend
{
namespace Gui
{

class SaldoSumDialog : public QDialog
{
    Q_OBJECT

public:
    SaldoSumDialog(Model::SaldoSumModel &aModel, QWidget *aParent = 0);

private:
    Ui::SaldoSumDialog ui;
};

}
}

#endif  /* // SALDOSUMDIALOG_H */
