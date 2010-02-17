#include <QtGui>
#include <gmock/gmock.h>

#include "mainwindowtest.h"

#include "controllermock.h"
#include "membermock.h"

using ::testing::Return;

namespace ClubFrontendTest
{

void MainWindowTest::instanz()
{
	GuiManagement::MainWindow mainWindow;
}

void MainWindowTest::loadMembers()
{
	GuiManagement::MainWindow mainWindow;
	
	MemberMock member1;
	EXPECT_CALL(member1, getId())
		.Times(1)
		.WillOnce(Return(23));
	EXPECT_CALL(member1, getName())
		.Times(1)
		.WillOnce(Return("Foo"));
	EXPECT_CALL(member1, getFirstname())
		.Times(1)
		.WillOnce(Return("Bar"));
	EXPECT_CALL(member1, getNickname())
		.Times(1)
		.WillOnce(Return("Fobi"));
		
	MemberMock member2;
	EXPECT_CALL(member2, getId())
		.Times(1)
		.WillOnce(Return(123));
	EXPECT_CALL(member2, getName())
		.Times(1)
		.WillOnce(Return("FFoo"));
	EXPECT_CALL(member2, getFirstname())
		.Times(1)
		.WillOnce(Return("BBar"));
	EXPECT_CALL(member2, getNickname())
		.Times(1)
		.WillOnce(Return("FoFo"));

	std::vector<ClubFrontend::Member*> memberlist;
	memberlist.push_back(&member1);
	memberlist.push_back(&member2);
		
	ControllerMock controller;
	EXPECT_CALL(controller, getMembers())
		.Times(1)
		.WillOnce(Return(memberlist));
	
	mainWindow.loadMembers(&controller);
			
	QTableWidget* table = mainWindow.tableWidget;
	QTableWidgetItem* item1 = table->itemAt(1,1);
	QVERIFY(item1 != 0);
	QVariant variant1 = item1->data(Qt::DisplayRole);
	QCOMPARE(variant1.toString(), QString("23"));

	QTableWidgetItem* item2 = table->item(0,1);
	QVERIFY(item2 != 0);
	QCOMPARE(item2->text(), QString("Foo"));
		
	QTableWidgetItem* item3 = table->item(0,2);
	QVERIFY(item3 != 0);
	QCOMPARE(item3->text(), QString("Bar"));
		
	QTableWidgetItem* item4 = table->item(0,3);
	QVERIFY(item4 != 0);
	QCOMPARE(item4->text(), QString("Fobi"));
		
	QTableWidgetItem* item5 = table->item(1,0);
	QVERIFY(item5 != 0);
	QCOMPARE(item5->text(), QString("123"));
		
	QTableWidgetItem* item6 = table->item(1,1);
	QVERIFY(item6 != 0);
	QCOMPARE(item6->text(), QString("FFoo"));
		
	QTableWidgetItem* item7 = table->item(1,2);
	QVERIFY(item7 != 0);
	QCOMPARE(item7->text(), QString("BBar"));
		
	QTableWidgetItem* item8 = table->item(1,3);
	QVERIFY(item8 != 0);
	QCOMPARE(item8->text(), QString("FoFo"));
}

}

