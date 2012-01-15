#include "saldomodeltest.h"

#include "model/saldomodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"
#include "model/memberfilter.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QString>

namespace membermanagertest
{
namespace model
{

void SaldoModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void SaldoModelTest::testModel()
{
    membermanager::model::SaldoModel saldoModel(1025, QSqlDatabase::database(), this);

    using membermanager::model::SaldoTable;
    const QSqlTableModel *model = saldoModel.getModel();
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(1);
    QCOMPARE(record.value(SaldoTable::bezeichnung).toString(), QString("Start Saldo"));
    QCOMPARE(record.value(SaldoTable::betrag).toString(), QString("0"));
}

void SaldoModelTest::testAmount()
{
    membermanager::model::SaldoModel saldoModel(1025, QSqlDatabase::database());

    double sum = saldoModel.amount();
    double expected = -15;
    QCOMPARE(sum, expected);
}

void SaldoModelTest::testGetMemberId()
{
    membermanager::model::SaldoModel saldoModel(1025, QSqlDatabase::database());

    QCOMPARE(saldoModel.getMemberId(), 1025);
}

void SaldoModelTest::testInsertAndDeleteRow()
{
    membermanager::model::SaldoModel saldoModel(1025, QSqlDatabase::database(), this);

    QSqlTableModel *model = saldoModel.getModel();
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);


    QModelIndex index = saldoModel.insertNewRow();

    model->select();
    QCOMPARE(model->rowCount(), 3);
    QCOMPARE(index.row(), 2);

    QVERIFY(saldoModel.deleteRow(index));
    model->select();
    QCOMPARE(model->rowCount(), 2);
}

}
}

QTEST_MAIN(membermanagertest::model::SaldoModelTest)
#include "saldomodeltest.moc"
