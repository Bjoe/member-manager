#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "ui_mainwindow.h"
#include "gui/memberdetailview.h"
#include "model/membermodel.h"

namespace membermanager
{
namespace gui
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
    void newMember();
    void updateMemberDetailView(const QItemSelection &aSelected, const QItemSelection &aDeselected);

private:
    Ui::MainWindow ui;
    MemberDetailView memberDetailView;
    model::MemberModel memberModel;

    void showMembers(const bool aBoolean);
    int getSelection() const;
};

}
}

#endif // MAINWINDOW_H
