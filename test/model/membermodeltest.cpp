#include "membermodeltest.h"

#include "model/membermodel.h"

#include "member.h"
#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"

#include <QtCore>
#include <QtSql>

namespace ClubFrontendTest
{
namespace Model
{

void MemberModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberModelTest::testGetLastError()
{
    ClubFrontend::Model::MemberModel dataSource(QSqlDatabase::database());
    // Fehler Produzieren ? QCOMPARE(memberModel.getLastError(),QString());
}

void MemberModelTest::testGetMemberModel()
{
    ClubFrontend::Model::MemberModel dataSource(QSqlDatabase::database());

    const QSqlTableModel *model = dataSource.findChild<QSqlTableModel *> (ClubFrontend::Model::MemberTable::TABLENAME);
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(1);
    QCOMPARE(record.value("name").toString(), QString("Spock"));
}

void MemberModelTest::testSetFilter()
{
    ClubFrontend::Model::MemberModel memberModel(QSqlDatabase::database());

    memberModel.setFilter("deleted='false'");

    const QSqlTableModel *model = memberModel.findChild<QSqlTableModel *> (ClubFrontend::Model::MemberTable::TABLENAME);
    QCOMPARE(model->rowCount(), 1);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value("name").toString(), QString("Kirk"));
}

void MemberModelTest::testGetMemberId()
{
    ClubFrontend::Model::MemberModel memberModel(QSqlDatabase::database());

    const QSqlTableModel *model = memberModel.findChild<QSqlTableModel *> (ClubFrontend::Model::MemberTable::TABLENAME);

    const QModelIndex index = model->index(0, 5);

    const int id = memberModel.getMemberId(index);

    QCOMPARE(id, 1025);
}

}
}

QTEST_MAIN(ClubFrontendTest::Model::MemberModelTest)
#include "membermodeltest.moc"