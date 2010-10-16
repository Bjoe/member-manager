#ifndef SALDODIALOG_H
#define SALDODIALOG_H

#include <QtGui/QDialog>
#include "ui_SaldoDialog.h"

#include "SaldoModel.h"

namespace ClubFrontend
{

class SaldoDialog : public QDialog
{
    Q_OBJECT

public:
    SaldoDialog(SaldoModel& aSaldoModel, QWidget *parent = 0);
    ~SaldoDialog();

private:
    Ui::SaldoDialogClass ui;
    SaldoModel& saldoModel;
};

}

#endif // SALDODIALOG_H
