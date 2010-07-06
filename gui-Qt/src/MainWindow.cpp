#include "MainWindow.h"

namespace ClubFrontend
{

MainWindow::MainWindow(DataSource & aDataSource, QWidget *parent) :
	QMainWindow(parent), dataSource(aDataSource)
{
	setupUi(this);
}

}

