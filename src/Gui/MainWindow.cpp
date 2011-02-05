
#include "Gui/MainWindow.h"
#include "Model/MemberFilter.h"
#include "Gui/MemberDialog.h"
#include "Model/MemberDetailModel.h"
#include "Gui/SaldoDialog.h"
#include "Model/DatabaseStructure.h"

#include <QModelIndexList>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QClipboard>
#include <QItemSelectionModel>
#include <QVariant>
#include <QString>

namespace ClubFrontend
{
namespace Gui
{

MainWindow::MainWindow ( Model::MemberModel& aMemberModel, Model::KassaModel& aKassaModel,
                         QWidget* parent ) :
        QMainWindow ( parent ), ui(), memberModel ( aMemberModel ), kassaModel (
            aKassaModel )
{
    ui.setupUi ( this );
    showMembers ( false );

    connect ( ui.actionShowDeletedMember, SIGNAL ( triggered() ), this,
              SLOT ( showDeletedMemberView() ) );
    connect ( ui.actionShowMember, SIGNAL ( triggered() ), this,
              SLOT ( showMemberView() ) );
    connect ( ui.actionShowKassa, SIGNAL ( triggered() ), this,
              SLOT ( showKassaView() ) );
    connect ( ui.actionNewMember, SIGNAL ( triggered() ), this,
              SLOT ( newMember() ) );
    connect ( ui.actionEditMember, SIGNAL ( triggered() ), this,
              SLOT ( selectedMember() ) );
    connect ( ui.actionShowSaldo, SIGNAL ( triggered() ), this,
              SLOT ( showSaldo() ) );
}

void MainWindow::newMember()
{
    Model::MemberDetailModel model;
    model.newMember();

    showMemberDialog ( model );
}

void MainWindow::selectedMember()
{
    editMember ( getSelection() );
}

void MainWindow::editMember ( const QModelIndex& anIndex )
{
    int id = memberModel.getMemberId ( anIndex );

    Model::MemberDetailModel model;
    model.setMemberId ( id );

    showMemberDialog ( model );
}

void MainWindow::showDeletedMemberView()
{
    showMembers ( true );
}

void MainWindow::showMemberView()
{
    showMembers ( false );
}

void MainWindow::showMembers ( const bool aBoolean )
{
    Model::MemberFilter filter;
    filter.setDeleted ( aBoolean );
    memberModel.setFilter ( filter.getFilter() );
    memberModel.initTableView ( ui.tableView );
    ui.tableView->resizeColumnsToContents();

    ui.tableView->addAction ( ui.actionEditMember );
    ui.tableView->addAction ( ui.actionCopyMailAdr );
    ui.tableView->addAction ( ui.actionShowSaldo );

    if ( aBoolean )
    {
        ui.actionShowDeletedMember->setChecked ( true );
        ui.actionShowMember->setChecked ( false );
        ui.actionShowKassa->setChecked ( false );
    }
    else
    {
        ui.actionShowDeletedMember->setChecked ( false );
        ui.actionShowMember->setChecked ( true );
        ui.actionShowKassa->setChecked ( false );
    }
    connect ( ui.tableView, SIGNAL ( doubleClicked ( const QModelIndex& ) ), this,
              SLOT ( editMember ( const QModelIndex& ) ), Qt::UniqueConnection );
}

void MainWindow::showKassaView()
{
    disconnect ( ui.tableView, SIGNAL ( doubleClicked ( const QModelIndex& ) ), this,
                 SLOT ( editMember ( const QModelIndex& ) ) );
    ui.tableView->removeAction ( ui.actionEditMember );
    ui.tableView->removeAction ( ui.actionCopyMailAdr );
    ui.tableView->removeAction ( ui.actionShowSaldo );

    ui.actionShowDeletedMember->setChecked ( false );
    ui.actionShowMember->setChecked ( false );
    ui.actionShowKassa->setChecked ( true );

    kassaModel.initTableView ( ui.tableView );
    ui.tableView->resizeColumnsToContents();
}

void MainWindow::showMemberDialog ( Model::MemberDetailModel& aModel )
{
    MemberDialog dialog ( aModel, this );
    dialog.show();
    dialog.exec();

    memberModel.refresh();
}

void MainWindow::showSaldo()
{
    int id = memberModel.getMemberId ( getSelection() );

    Model::SaldoModel model ( QSqlDatabase::database(), id );
    SaldoDialog dialog ( model, this );
    dialog.show();
    dialog.exec();
}

QModelIndex MainWindow::getSelection() const
{
    QItemSelectionModel* selectionModel = ui.tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();
    return indexes.first();
}

}
}
