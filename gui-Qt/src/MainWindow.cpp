#include "MainWindow.h"
#include "MemberFilter.h"
#include "MemberDetailModel.h"
#include "MemberDialog.h"

namespace ClubFrontend
{

MainWindow::MainWindow(MemberModel& aDataSource, QWidget* parent) :
	QMainWindow(parent), ui(), dataSource(aDataSource)
{
	ui.setupUi(this);

	showDeletedMember(false);

	ui.memberTableView->setModel(dataSource.getMemberTableModel());

	connect(ui.actionShowDeletedMember, SIGNAL(triggered()), this,
			SLOT(deletedView()));
	connect(ui.actionSelectMember, SIGNAL(triggered()), this,
			SLOT(refreshTable()));
	connect(ui.actionNewMember, SIGNAL(triggered()), this, SLOT(newMember()));
}

void MainWindow::newMember()
{
	MemberDetailModel memberDetailModel;
	memberDetailModel.newMember();

	MemberDialog dialog(memberDetailModel);
	dialog.show();
	dialog.exec();
}

void MainWindow::deletedView()
{
	showDeletedMember(true);
}

void MainWindow::refreshTable()
{
	showDeletedMember(false);
}

void MainWindow::showDeletedMember(const bool aBoolean)
{
	MemberFilter filter;
	filter.setDeleted(aBoolean);
	dataSource.setFilter(filter.getFilter());

	if (aBoolean)
	{
		ui.actionShowDeletedMember->setChecked(true);
		ui.actionSelectMember->setChecked(false);
	}
	else
	{
		ui.actionShowDeletedMember->setChecked(false);
		ui.actionSelectMember->setChecked(true);
	}
}

}
