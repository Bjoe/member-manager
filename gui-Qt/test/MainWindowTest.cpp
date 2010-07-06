
#include "MainWindowTest.h"

#include "TestData.h"

#include "MainWindow.h"

namespace ClubFrontendTest
{


void MainWindowTest::initTestCase() {
	TestData testData;
	testData.createFakeMemberTable();
}

void MainWindowTest::testMemberView() {
	ClubFrontend::DataSource dataSource(QSqlDatabase::database());
	ClubFrontend::MainWindow mainWindow(dataSource);

	QTableView * view = mainWindow.memberTableView;
	QAbstractItemModel * model = view->model();
	QVERIFY(model != 0);
	QCOMPARE(model->rowCount(), 1);
	// TODO Test erweitern auf Tabellen inhalt.
}



}

