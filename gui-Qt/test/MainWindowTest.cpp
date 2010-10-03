#include "MainWindowTest.h"

#include "MainWindow.h"

#include "TestData.h"
#include "TriggerThread.h"
#include "MemberModel.h"

#include <QTableView>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QVariant>
#include <QAction>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QApplication>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QLabel>

#include <QDebug>

namespace ClubFrontendTest
{

void MainWindowTest::init()
{
	TestData testData;
	testData.createFakeMemberTable();
}

void MainWindowTest::testNewMember()
{
	ClubFrontend::MemberModel memberModel(QSqlDatabase::database());
	ClubFrontend::MainWindow mainWindow(memberModel);

	QAction* actionNewMember = mainWindow.findChild<QAction*> (
			"actionNewMember");
	TriggerThread thread(this, this);
	connect(&thread, SIGNAL(triggered()), actionNewMember, SLOT(trigger()));
	thread.syncStart();

	QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
			"actionShowDeletedMember");
	actionShowDeletedMember->trigger();

	QSqlTableModel* model = memberModel.getMemberTableModel();
	QCOMPARE(model->rowCount(), 2);

	QCOMPARE(id, QString("1027"));
}

void MainWindowTest::testEditMember()
{
	ClubFrontend::MemberModel memberModel(QSqlDatabase::database());
	ClubFrontend::MainWindow mainWindow(memberModel);

	QSqlTableModel* model = memberModel.getMemberTableModel();
	QModelIndex index = model->index(0, 3);

	TriggerThread thread(this, this, index);
	connect(&thread, SIGNAL(triggered(const QModelIndex&)), &mainWindow, SLOT(editMember(const QModelIndex&)));
	thread.syncStart();

	QCOMPARE(id, QString("1025"));
}

void MainWindowTest::doWork()
{
	sleep(1);
	bool next = true;
	do
	{
		QWidget* widget = QApplication::activeWindow();
		if (widget)
		{
			QLabel* memberId = widget->findChild<QLabel* >("memberId");
			id = memberId->text();
			widget->close();
			next = false;
		}
	} while (next);
}

void MainWindowTest::testMemberView()
{
	ClubFrontend::MemberModel memberModel(QSqlDatabase::database());
	ClubFrontend::MainWindow mainWindow(memberModel);

	QAction* actionSelectMember = mainWindow.findChild<QAction*> (
			"actionShowMember");
	actionSelectMember->trigger();

	QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
			"actionShowDeletedMember");
	QVERIFY(!actionShowDeletedMember->isChecked());

	QTableView* view = mainWindow.findChild<QTableView*> ("tableView");

	QModelIndex index = view->indexAt(QPoint(0, 0));
	QVERIFY(index.isValid());
	const QAbstractItemModel * model = index.model();
	QVERIFY(model != 0);
	QCOMPARE(model->rowCount(), 1);
	QVariant value = model->data(index);
	QCOMPARE(value.toInt(),1025);

	// XXX QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
	// XXX QModelIndex index = view->currentIndex();
}

void MainWindowTest::testDeletedMemberView()
{
	ClubFrontend::MemberModel memberModel(QSqlDatabase::database());
	ClubFrontend::MainWindow mainWindow(memberModel);

	QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
			"actionShowDeletedMember");
	actionShowDeletedMember->trigger();

	QAction* actionSelectMember = mainWindow.findChild<QAction*> (
			"actionShowMember");
	QVERIFY(!actionSelectMember->isChecked());

	QTableView* view = mainWindow.findChild<QTableView*> ("tableView");

	QModelIndex index = view->indexAt(QPoint(0, 0));
	QVERIFY(index.isValid());
	const QAbstractItemModel * model = index.model();
	QVERIFY(model != 0);
	QCOMPARE(model->rowCount(), 1);
	QVariant value = model->data(index);
	QCOMPARE(value.toInt(),1026);

	// XXX QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
	// XXX QModelIndex index = view->currentIndex();
}

}
