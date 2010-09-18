#include "MainWindow.h"
#include "MemberFilter.h"
#include <QDebug>

namespace ClubFrontend
{

MainWindow::MainWindow(MemberModel & aDataSource, QWidget *parent) :
	QMainWindow(parent), ui(), dataSource(aDataSource)
{
	ui.setupUi(this);

	MemberFilter filter;
	filter.setDeleted(false);
	dataSource.setFilter(filter.getFilter());

	qDebug() << dataSource.getLastError();

	ui.memberTableView->setModel(dataSource.getMemberTableModel());

	connect(ui.actionShowDeletedMember, SIGNAL(triggered()), this, SLOT(deletedView()));
	connect(ui.actionSelectMember, SIGNAL(triggered()), this, SLOT(refreshTable()));
}

void MainWindow::deletedView()
{
	MemberFilter filter;
	filter.setDeleted(true);
	dataSource.setFilter(filter.getFilter());
}

void MainWindow::refreshTable()
{
	MemberFilter filter;
	filter.setDeleted(false);
	dataSource.setFilter(filter.getFilter());
}

}

