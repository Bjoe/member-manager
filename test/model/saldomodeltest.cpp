#include "saldomodeltest.h"

#include "model/saldomodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"
#include "model/memberfilter.h"

#include <QSqlTableModel>
#include <QSqlRecord>
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
    membermanager::model::SaldoModel saldoModel(filter, QSqlDatabase::database());

    using membermanager::model::SaldoTable;
    const QSqlTableModel *model = saldoModel.findChild<QSqlTableModel *> (SaldoTable::TABLENAME);
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

}
}

QTEST_MAIN(membermanagertest::model::SaldoModelTest)
#include "saldomodeltest.moc"
