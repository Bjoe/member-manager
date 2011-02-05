#ifndef SALDODIALOG_H
#define SALDODIALOG_H

#include <QtGui/QDialog>
#include "ui_SaldoDialog.h"

#include "Model/SaldoModel.h"

namespace ClubFrontend
{
namespace Gui
{

class SaldoDialog : public QDialog
{
    Q_OBJECT

public:
    SaldoDialog ( Model::SaldoModel& aSaldoModel, QWidget *parent = 0 );
    ~SaldoDialog();

private:
    Ui::SaldoDialogClass ui;
    Model::SaldoModel& saldoModel;
};

}
}

#endif // SALDODIALOG_H
