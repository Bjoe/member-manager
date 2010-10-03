#include "MainWindow.h"
#include "MemberFilter.h"
#include "MemberDialog.h"

namespace ClubFrontend
{

MainWindow::MainWindow(MemberModel& aMemberModel, KassaModel& aKassaModel,
		QWidget* parent) :
	QMainWindow(parent), ui(), memberModel(aMemberModel), kassaModel(
			aKassaModel)
{
	ui.setupUi(this);
	showDeletedMember(false);

	connect(ui.actionShowDeletedMember, SIGNAL(triggered()), this,
			SLOT(showDeletedMemberView()));
	connect(ui.actionShowMember, SIGNAL(triggered()), this,
			SLOT(showMemberView()));
	connect(ui.actionShowKassa, SIGNAL(triggered()), this,
			SLOT(showKassaView()));
	connect(ui.actionNewMember, SIGNAL(triggered()), this, SLOT(newMember()));
}

void MainWindow::newMember()
{
	MemberDetailModel model;
	model.newMember();

	showMemberDialog(model);
}

void MainWindow::editMember(const QModelIndex& anIndex)
{
	int id = memberModel.getMemberId(anIndex);

	MemberDetailModel model;
	model.setMemberId(id);

	showMemberDialog(model);
}

void MainWindow::showDeletedMemberView()
{
	showDeletedMember(true);
}

void MainWindow::showMemberView()
{
	showDeletedMember(false);
}

void MainWindow::showDeletedMember(const bool aBoolean)
{
	MemberFilter filter;
	filter.setDeleted(aBoolean);
	memberModel.setFilter(filter.getFilter());
	ui.tableView->setModel(memberModel.getMemberTableModel());

	if (aBoolean)
	{
		ui.actionShowDeletedMember->setChecked(true);
		ui.actionShowMember->setChecked(false);
		ui.actionShowKassa->setChecked(false);
	}
	else
	{
		ui.actionShowDeletedMember->setChecked(false);
		ui.actionShowMember->setChecked(true);
		ui.actionShowKassa->setChecked(false);
	}
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this,
			SLOT(editMember(const QModelIndex&)), Qt::UniqueConnection);
}

void MainWindow::showKassaView()
{
	disconnect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this,
			SLOT(editMember(const QModelIndex&)));
	ui.actionShowDeletedMember->setChecked(false);
	ui.actionShowMember->setChecked(false);
	ui.actionShowKassa->setChecked(true);

	ui.tableView->setModel(kassaModel.getKassaTableModel());
	// TODO Unoetige Tabellen Felder auf Hidden setzen.
}

void MainWindow::showMemberDialog(MemberDetailModel& aModel)
{
	MemberDialog dialog(aModel, this);
	dialog.show();
	dialog.exec();

	memberModel.refresh();
}

}
