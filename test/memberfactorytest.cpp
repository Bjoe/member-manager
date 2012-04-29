#include "memberfactorytest.h"

#include "memberfactory.h"

#include <QList>
#include <QSqlTableModel>

#include "member.h"
#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"

namespace membermanagertest
{

void MemberFactoryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberFactoryTest::testCreateNewMember()
{
    membermanager::Member member = membermanager::MemberFactory::createNewMember();
    QCOMPARE(member.getMemberId(), 1027);
}

void MemberFactoryTest::testCreateExistsMember()
{
    membermanager::Member member = membermanager::MemberFactory::createMember(1025);
    QCOMPARE(member.getMemberId(), 1025);
}

void MemberFactoryTest::testCreateMemberList()
{
    QSqlTableModel model;
    model.setTable(membermanager::model::MemberTable::TABLENAME);
    QString columname = membermanager::model::MemberTable::COLUMNNAME[membermanager::model::MemberTable::Deleted];
    model.setFilter(QString("%1 = 'false'").arg(columname));
    model.select();

    QList<membermanager::Member> list = membermanager::MemberFactory::createMemberList(&model);

    QCOMPARE(list.size(), 1);
}

}

QTEST_MAIN(membermanagertest::MemberFactoryTest)
#include "memberfactorytest.moc"
