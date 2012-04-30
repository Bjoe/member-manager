#include "kassamodeltest.h"

#include "dao/kassamodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "dao/databasestructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace membermanagertest
{
namespace dao
{

void KassaModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void KassaModelTest::testModel()
{
    membermanager::dao::KassaModel kassaModel(QSqlDatabase::database());

    using membermanager::dao::KassaTable;
    const QSqlTableModel *model = kassaModel.findChild<QSqlTableModel *> (KassaTable::TABLENAME);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 3);
    QSqlRecord record = model->record(1);
    QCOMPARE(record.value(KassaTable::betrag).toString(), QString("104.86"));
}

}
}

QTEST_MAIN(membermanagertest::dao::KassaModelTest)
#include "kassamodeltest.moc"
