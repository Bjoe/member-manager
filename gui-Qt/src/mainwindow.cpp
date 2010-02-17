#include "mainwindow.h"

#include <vector>

#include "member.h"

namespace GuiManagement
{

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);
}

void MainWindow::loadMembers(const ClubFrontend::Controller *aController) const
{
	std::vector<ClubFrontend::Member*> memberList = aController->getMembers();
	std::vector<ClubFrontend::Member*>::iterator it;
	
	int row = 0;
	for(it = memberList.begin(); it != memberList.end(); ++row, ++it) {
		ClubFrontend::Member* member = *it;
			
		QTableWidgetItem* itemId = new QTableWidgetItem;
		itemId->setData(Qt::DisplayRole, member->getId());
		tableWidget->setItem(row, 0, itemId);
			
		QTableWidgetItem* itemName = new QTableWidgetItem;
		QString name = QString::fromStdString(member->getName());
		itemName->setData(Qt::DisplayRole, name);
		tableWidget->setItem(row, 1, itemName);
			
		QTableWidgetItem* itemFirstname = new QTableWidgetItem;
		QString firstname = QString::fromStdString(member->getFirstname());
		itemFirstname->setData(Qt::DisplayRole, firstname);
		tableWidget->setItem(row, 2, itemFirstname);
			
		QTableWidgetItem* itemNickname = new QTableWidgetItem;
		QString nickname = QString::fromStdString(member->getNickname());
		itemNickname->setData(Qt::DisplayRole, nickname);
		tableWidget->setItem(row, 3, itemNickname);
	}
}

}

