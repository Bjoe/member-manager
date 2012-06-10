#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "ui_mainwindow.h"
#include "gui/memberdetailview.h"
#include "dao/memberdao.h"

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
    void saveMember();
    void updateMemberDetailView(const QItemSelection &aSelected, const QItemSelection &aDeselected);
    void managerSummary();
    void memberCollectionWithBooking();
    void memberCollectionWithoutBooking();

private:
    Ui::MainWindow ui;
    dao::MemberDao memberDao;
    MemberDetailView memberDetailView;
    bool showDeleted;

    void showMembers();
    void updateTableView();
    void memberCollection(bool isBooking);
};

}
}

#endif // MAINWINDOW_H
