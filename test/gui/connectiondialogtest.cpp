#include "connectiondialogtest.h"

#include "gui/connectiondialog.h"

#include <QtGui>

namespace membermanagertest
{
namespace gui
{

void ConnectionDialogTest::testGetUsername()
{
    membermanager::gui::ConnectionDialog dialog;
    dialog.setUsername("bj");

    QLineEdit *username = dialog.findChild<QLineEdit *> ("username");
    QTest::keyClicks(username, "oe");

    QCOMPARE(dialog.getUsername(), QString("bjoe"));
}

void ConnectionDialogTest::testGetPassword()
{
    membermanager::gui::ConnectionDialog dialog;

    QLineEdit *password = dialog.findChild<QLineEdit *> ("passwd");
    QTest::keyClicks(password, "1234");

    QCOMPARE(dialog.getPassword(), QString("1234"));
}

void ConnectionDialogTest::testGetDatebaseName()
{
    membermanager::gui::ConnectionDialog dialog;
    dialog.setDatabaseName("Data");

    QLineEdit *databaseName = dialog.findChild<QLineEdit *> ("databaseName");
    QTest::keyClicks(databaseName, "basename");

    QCOMPARE(dialog.getDatabaseName(), QString("Databasename"));
}

void ConnectionDialogTest::testGetHostname()
{
    membermanager::gui::ConnectionDialog dialog;
    dialog.setHostname("Foo");

    QLineEdit *hostname = dialog.findChild<QLineEdit *> ("hostname");
    QTest::keyClicks(hostname, "Bar");

    QCOMPARE(dialog.getHostname(), QString("FooBar"));
}

void ConnectionDialogTest::testGetDriverName()
{
    membermanager::gui::ConnectionDialog dialog;
    QComboBox *driverName = dialog.findChild<QComboBox *> ("driver");

    QCOMPARE(dialog.getDriver(), QString("QSQLITE"));
}

void ConnectionDialogTest::testSetDriverName()
{
    membermanager::gui::ConnectionDialog dialog;
    dialog.setDriver("QSQLITE");

    QComboBox *driverName = dialog.findChild<QComboBox *> ("driver");

    QCOMPARE(dialog.getDriver(), QString("QSQLITE"));
}

void ConnectionDialogTest::testSetWrongDriverName()
{
    membermanager::gui::ConnectionDialog dialog;
    dialog.setDriver("FOO");

    QComboBox *driverName = dialog.findChild<QComboBox *> ("driver");

    QCOMPARE(dialog.getDriver(), QString("QSQLITE"));
}

void ConnectionDialogTest::testGetPort()
{
    membermanager::gui::ConnectionDialog dialog;
    QSpinBox *port = dialog.findChild<QSpinBox *> ("port");

    QTest::keyClicks(port, "23");

    QCOMPARE(dialog.getPort(), 23);
}

void ConnectionDialogTest::testOkButton()
{
    membermanager::gui::ConnectionDialog dialog;
    QDialogButtonBox *buttonBox = dialog.findChild<QDialogButtonBox *> (
                                      "buttonBox");

    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    QTest::mouseClick(okButton, Qt::LeftButton);

    QVERIFY(dialog.result() == QDialog::Accepted);
}

void ConnectionDialogTest::testCancelButton()
{
    membermanager::gui::ConnectionDialog dialog;
    QDialogButtonBox *buttonBox = dialog.findChild<QDialogButtonBox *> (
                                      "buttonBox");

    QPushButton *cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
    QTest::mouseClick(cancelButton, Qt::LeftButton);

    QVERIFY(dialog.result() == QDialog::Rejected);

}

}
}

QTEST_MAIN(membermanagertest::gui::ConnectionDialogTest)
#include "connectiondialogtest.moc"
