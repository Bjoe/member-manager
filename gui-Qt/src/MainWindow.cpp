#include "MainWindow.h"

namespace ClubFrontend
{

MainWindow::MainWindow(MemberModel & aDataSource, QWidget *parent) :
	QMainWindow(parent), dataSource(aDataSource)
{
	setupUi(this);

	memberTableView->setModel(dataSource.getMemberTableModel());
}

}

