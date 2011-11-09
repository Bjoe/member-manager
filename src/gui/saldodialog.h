#ifndef SALDODIALOG_H
#define SALDODIALOG_H

#include <QtGui/QDialog>
#include "ui_saldodialog.h"

#include "model/saldomodel.h"

namespace membermanager
{
namespace gui
{

class SaldoDialog : public QDialog
{
    Q_OBJECT

public:
    SaldoDialog(model::SaldoModel aSaldoModel, QWidget *parent = 0);
    ~SaldoDialog();

private slots:
    void insertRow();
    void deleteRow();

private:
    Ui::SaldoDialogClass ui;
    model::SaldoModel saldoModel;
};

}
}

#endif // SALDODIALOG_H
