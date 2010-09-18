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
}

}

