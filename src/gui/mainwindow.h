#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "ui_mainwindow.h"
#include "gui/membermapper.h"
#include "model/membermodel.h"

namespace ClubFrontend
{
namespace Gui
{

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QSqlDatabase &aDatabase,
               QWidget *parent = 0);

private slots:
    void showDeletedMemberView();
    void showMemberView();
    void showSaldo();
    void updateMemberMapper(const QItemSelection &aSelected, const QItemSelection &aDeselected);

private:
    Ui::MainWindow ui;
    Gui::MemberMapper memberMapper;
    Model::MemberModel memberModel;

    void showMembers(const bool aBoolean);
    int getSelection() const;
};

}
}

#endif // MAINWINDOW_H
