/*
 * ConnectionDialogTest.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: joerg
 */

#include "ConnectionDialogTest.h"

#include "Gui/ConnectionDialog.h"

#include <QtGui>

namespace ClubFrontendTest
{

void ConnectionDialogTest::testGetUsername()
{
	ClubFrontend::ConnectionDialog dialog;
	dialog.setUsername("bj");

	QLineEdit* username = dialog.findChild<QLineEdit*> ("username");
	QTest::keyClicks(username, "oe");

	QCOMPARE(dialog.getUsername(), QString("bjoe"));
}

void ConnectionDialogTest::testGetPassword()
{
	ClubFrontend::ConnectionDialog dialog;

	QLineEdit* password = dialog.findChild<QLineEdit*> ("passwd");
	QTest::keyClicks(password, "1234");

	QCOMPARE(dialog.getPassword(), QString("1234"));
}

void ConnectionDialogTest::testGetDatebaseName()
{
	ClubFrontend::ConnectionDialog dialog;
	dialog.setDatabaseName("Data");

	QLineEdit* databaseName = dialog.findChild<QLineEdit*> ("databaseName");
	QTest::keyClicks(databaseName, "basename");

	QCOMPARE(dialog.getDatabaseName(), QString("Databasename"));
}

void ConnectionDialogTest::testGetHostname()
{
	ClubFrontend::ConnectionDialog dialog;
	dialog.setHostname("Foo");

	QLineEdit* hostname = dialog.findChild<QLineEdit*> ("hostname");
	QTest::keyClicks(hostname, "Bar");

	QCOMPARE(dialog.getHostname(), QString("FooBar"));
}

void ConnectionDialogTest::testGetDriverName()
{
	ClubFrontend::ConnectionDialog dialog;
	QComboBox* driverName = dialog.findChild<QComboBox*> ("driver");

	QCOMPARE(dialog.getDriver(), QString("QSQLITE"));
}

void ConnectionDialogTest::testSetDriverName()
{
	ClubFrontend::ConnectionDialog dialog;
	dialog.setDriver("QSQLITE");

	QComboBox* driverName = dialog.findChild<QComboBox*> ("driver");

	QCOMPARE(dialog.getDriver(), QString("QSQLITE"));
}

void ConnectionDialogTest::testSetWrongDriverName()
{
	ClubFrontend::ConnectionDialog dialog;
	dialog.setDriver("FOO");

	QComboBox* driverName = dialog.findChild<QComboBox*> ("driver");

	QCOMPARE(dialog.getDriver(), QString("QSQLITE"));
}

void ConnectionDialogTest::testGetPort()
{
	ClubFrontend::ConnectionDialog dialog;
	QSpinBox* port = dialog.findChild<QSpinBox*> ("port");

	QTest::keyClicks(port, "23");

	QCOMPARE(dialog.getPort(), 23);
}

void ConnectionDialogTest::testOkButton()
{
	ClubFrontend::ConnectionDialog dialog;
	QDialogButtonBox* buttonBox = dialog.findChild<QDialogButtonBox *> (
			"buttonBox");

	QPushButton* okButton = buttonBox->button(QDialogButtonBox::Ok);
	QTest::mouseClick(okButton, Qt::LeftButton);

	QVERIFY(dialog.result() == QDialog::Accepted);
}

void ConnectionDialogTest::testCancelButton()
{
	ClubFrontend::ConnectionDialog dialog;
	QDialogButtonBox* buttonBox = dialog.findChild<QDialogButtonBox *> (
			"buttonBox");

	QPushButton* cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
	QTest::mouseClick(cancelButton, Qt::LeftButton);

	QVERIFY(dialog.result() == QDialog::Rejected);

}

}

QTEST_MAIN(ClubFrontendTest::ConnectionDialogTest)
#include "ConnectionDialogTest.moc"
