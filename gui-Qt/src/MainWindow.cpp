#include "MainWindow.h"
#include "MemberFilter.h"
#include "MemberDialog.h"

namespace ClubFrontend
{

MainWindow::MainWindow(MemberModel& aMemberModel, QWidget* parent) :
	QMainWindow(parent), ui(), memberModel(aMemberModel)
{
	ui.setupUi(this);
	showDeletedMember(false);

	connect(ui.actionShowDeletedMember, SIGNAL(triggered()), this,
			SLOT(showDeletedMemberView()));
	connect(ui.actionShowMember, SIGNAL(triggered()), this,
			SLOT(showMemberView()));
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
	}
	else
	{
		ui.actionShowDeletedMember->setChecked(false);
		ui.actionShowMember->setChecked(true);
	}
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)),
			this, SLOT(editMember(const QModelIndex&)));
}

void MainWindow::showMemberDialog(MemberDetailModel& aModel)
{
	MemberDialog dialog(aModel, this);
	dialog.show();
	dialog.exec();

	memberModel.refresh();
}

}
