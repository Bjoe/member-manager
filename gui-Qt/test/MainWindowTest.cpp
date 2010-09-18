#include "MainWindowTest.h"

#include "MainWindow.h"

#include "TestData.h"
#include "MemberModel.h"

#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QVariant>

namespace ClubFrontendTest
{

void MainWindowTest::initTestCase()
{
	TestData testData;
	testData.createFakeMemberTable();
}

void MainWindowTest::testMemberView()
{
	ClubFrontend::MemberModel dataSource(QSqlDatabase::database());
	ClubFrontend::MainWindow mainWindow(dataSource);

	QTableView* view = mainWindow.findChild<QTableView*> ("memberTableView");

	QModelIndex index = view->indexAt(QPoint(0, 0));
	// XXX SQLite does not have a separate Boolean storage class.
	QVERIFY(index.isValid());
	const QAbstractItemModel * model = index.model();
	QVERIFY(model != 0);
	QCOMPARE(model->rowCount(), 1);
	QVariant value = model->data(index);
	QCOMPARE(value.toInt(),1025);

	// XXX QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
	// XXX QModelIndex index = view->currentIndex();
}

}

