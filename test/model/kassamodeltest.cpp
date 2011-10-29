#include "kassamodeltest.h"

#include "model/kassamodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace membermanagertest
{
namespace model
{

void KassaModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void KassaModelTest::testModel()
{
    membermanager::model::KassaModel kassaModel(QSqlDatabase::database());

    using membermanager::model::KassaTable;
    const QSqlTableModel *model = kassaModel.findChild<QSqlTableModel *> (KassaTable::TABLENAME);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 3);
    QSqlRecord record = model->record(1);
    QCOMPARE(record.value(KassaTable::betrag).toString(), QString("104.86"));
}

}
}

QTEST_MAIN(membermanagertest::model::KassaModelTest)
#include "kassamodeltest.moc"
