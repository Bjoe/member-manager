#include "MainWindow.h"

namespace ClubFrontend
{

MainWindow::MainWindow(MemberModel & aDataSource, QWidget *parent) :
	QMainWindow(parent), dataSource(aDataSource)
{
	ui.setupUi(this);

	ui.memberTableView->setModel(dataSource.getMemberTableModel());
}

}

