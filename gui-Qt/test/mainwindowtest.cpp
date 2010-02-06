#include <QtGui>
#include <gmock/gmock.h>

#include "mainwindowtest.h"

namespace ClubFrontendTest
{

void MainWindowTest::instanz()
{
	GuiManagement::MainWindow mainWindow;
}

void MainWindowTest::loadMembers()
{
	GuiManagement::MainWindow mainWindow;
	
	mainWindow.loadMembers();
	
}

}

