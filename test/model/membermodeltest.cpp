#include "membermodeltest.h"

#include "model/membermodel.h"

#include "member.h"
#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"

#include <QtCore>
#include <QtSql>

namespace membermanagertest
{
namespace model
{

void MemberModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberModelTest::testGetLastError()
{
    membermanager::model::MemberModel dataSource(this, QSqlDatabase::database());
    // Fehler Produzieren ? QCOMPARE(memberModel.getLastError(),QString());
}

void MemberModelTest::testGetMemberModel()
{
    membermanager::model::MemberModel dataSource(this, QSqlDatabase::database());

    QSqlTableModel *model = dataSource.getModel();
    model->select();
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(1);
    QCOMPARE(record.value("name").toString(), QString("Spock"));
}

void MemberModelTest::testSetFilter()
{
    membermanager::model::MemberModel memberModel(this, QSqlDatabase::database());

    memberModel.setFilter("deleted='false'");

    const QSqlTableModel *model = memberModel.getModel();
    QCOMPARE(model->rowCount(), 1);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value("name").toString(), QString("Kirk"));
}

void MemberModelTest::testGetMemberId()
{
    membermanager::model::MemberModel memberModel(this, QSqlDatabase::database());

    QSqlTableModel *model = memberModel.getModel();
    model->select();

    const QModelIndex index = model->index(0, 1);

    const int id = memberModel.getMemberId(index.row());

    QCOMPARE(id, 1025);
}

}
}

QTEST_MAIN(membermanagertest::model::MemberModelTest)
#include "membermodeltest.moc"
