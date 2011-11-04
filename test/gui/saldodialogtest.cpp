#include "saldodialogtest.h"

#include "gui/saldodialog.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "triggerthread.h"
#include "gui/dialogbuttonboxhandler.h"
#include "model/saldomodel.h"
#include "model/memberfilter.h"

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

void SaldoDialogTest::testShowDialog()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::model::SaldoModel saldoModel(filter, QSqlDatabase::database());
    membermanager::gui::SaldoDialog dialog(&saldoModel);

    QTableView *tableView = dialog.findChild<QTableView *> ("saldoTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 2);
    QModelIndex index = model->index(0, 3);
    QVariant value = model->data(index);
    QCOMPARE(value.toString(), QString("2005-09-18"));
}

void SaldoDialogTest::testShowSum()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::model::SaldoModel saldoModel(filter, QSqlDatabase::database());
    membermanager::gui::SaldoDialog dialog(&saldoModel);

    QLabel *sumLabel = dialog.findChild<QLabel *> ("sumLabel");
    QCOMPARE(sumLabel->text(), QString("Summe: -15"));
}

}
}

QTEST_MAIN(membermanagertest::gui::SaldoDialogTest)
#include "saldodialogtest.moc"
