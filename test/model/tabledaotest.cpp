#include "tabledaotest.h"

#include "model/tabledao.h"

#include <QtSql>
#include "testconfig.h"
#include "model/databasestructure.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace model
{

void TableDaoTest::initTest()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void TableDaoTest::testInsertNewRow()
{
    using membermanager::model::SaldoTable;
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(SaldoTable::TABLENAME);
    model->select();
    int size = model->rowCount();

    QVariant id(123);

    membermanager::model::TableDao tableDao;
    int row = tableDao.insertNewRow(model, SaldoTable::dorfmitglied_pkey, id);
    QCOMPARE(row, 2);

    QCOMPARE(model->rowCount(), (size + 1));
    const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(123);
    QSqlQuery query;
    query.exec("select * from " + SaldoTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(SaldoTable::dorfmitglied_pkey).toInt(), 123);
}

}
}

QTEST_MAIN(membermanagertest::model::TableDaoTest)
#include "tabledaotest.moc"
