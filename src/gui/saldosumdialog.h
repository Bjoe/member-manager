#ifndef SALDOSUMDIALOG_H
#define SALDOSUMDIALOG_H

#include <QtGui/QDialog>
#include "ui_saldosumdialog.h"

#include "model/saldosummodel.h"

namespace membermanager
{
namespace gui
{

class SaldoSumDialog : public QDialog
{
    Q_OBJECT

public:
    SaldoSumDialog(model::SaldoSumModel &aModel, QWidget *aParent = 0);

private:
    Ui::SaldoSumDialog ui;
};

}
}

#endif  /* // SALDOSUMDIALOG_H */
