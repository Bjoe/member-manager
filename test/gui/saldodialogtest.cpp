#include "saldodialogtest.h"

#include "gui/saldodialog.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "triggerthread.h"
#include "gui/dialogbuttonboxhandler.h"
#include "model/saldomodel.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPoint>
#include <QVariant>
#include <QString>
#include <QLabel>

#include <QDebug>

namespace membermanagertest
{
namespace gui
{

void SaldoDialogTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void SaldoDialogTest::testShowNothing()
{
    membermanager::gui::SaldoDialog dialog;
    dialog.showSaldo(0);
}

void SaldoDialogTest::testShowDialog()
{
    membermanager::gui::SaldoDialog dialog;

    qttestutil::gui::DialogButtonBoxHandler handler(QDialogButtonBox::Close);
    qttestutil::TriggerThread thread(this, &handler);
    //connect(&thread, SIGNAL(triggered()), &dialog, SLOT(show()));
    //thread.syncStart();
    /// \todo Fix Test
    /*
        QTableView *tableView = dialog.findChild<QTableView *> ("saldoTableView");
        const QAbstractItemModel *model = tableView->model();
        QVERIFY(model != 0);
        QCOMPARE(model->rowCount(), 2);
        QModelIndex index = model->index(0, 3);
        QVariant value = model->data(index);
        QCOMPARE(value.toString(), QString("2005-09-18"));
        */
}

void SaldoDialogTest::testShowSum()
{
    membermanager::gui::SaldoDialog dialog;

    qttestutil::gui::DialogButtonBoxHandler handler(QDialogButtonBox::Close);
    qttestutil::TriggerThread thread(this, &handler);
    //connect(&thread, SIGNAL(triggered()), &dialog, SLOT(showSaldo()));
    //thread.syncStart();
    /// \todo Fix Test
    /*
    QLabel *sumLabel = dialog.findChild<QLabel *> ("sumLabel");
    QCOMPARE(sumLabel->text(), QString("Summe: -15"));
    */
}

}
}

QTEST_MAIN(membermanagertest::gui::SaldoDialogTest)
#include "saldodialogtest.moc"
