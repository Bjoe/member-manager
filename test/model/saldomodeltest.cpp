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
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::model::SaldoModel saldoModel(filter, QSqlDatabase::database(), this);

    using membermanager::model::SaldoTable;
    const QSqlTableModel *model = findChild<QSqlTableModel *> (SaldoTable::TABLENAME);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(SaldoTable::bezeichnung).toString(), QString("Start Saldo"));
    QCOMPARE(record.value(SaldoTable::betrag).toString(), QString("0"));
}

void SaldoModelTest::testAmount()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::model::SaldoModel saldoModel(filter, QSqlDatabase::database());

    double sum = saldoModel.amount();
    double expected = -15;
    QCOMPARE(sum, expected);
}

void SaldoModelTest::testGetMemberId()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::model::SaldoModel saldoModel(filter, QSqlDatabase::database());

    QCOMPARE(saldoModel.getMemberId(), QString("1025"));
}

void SaldoModelTest::testInsertAndDeleteRow()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::model::SaldoModel saldoModel(filter, QSqlDatabase::database(), this);

    using membermanager::model::SaldoTable;
    QSqlTableModel *model = findChild<QSqlTableModel *> (SaldoTable::TABLENAME);
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
