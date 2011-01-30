#include "MemberModelTest.h"

#include "Model/MemberModel.h"

#include "Model/Member.h"
#include "TestConfig.h"
#include "TestUtils/DatabaseUtils.h"
#include "Model/MemberDetailModel.h"

#include <QtCore>
#include <QtSql>

namespace ClubFrontendTest
{

void MemberModelTest::initTestCase()
{
    Utils::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void MemberModelTest::testGetLastError()
{
    ClubFrontend::MemberModel dataSource ( QSqlDatabase::database() );
    // Fehler Produzieren ? QCOMPARE(memberModel.getLastError(),QString());
}

void MemberModelTest::testGetMemberModel()
{
    ClubFrontend::MemberModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.findChild<QSqlTableModel* >( "model" );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 1 );
    QCOMPARE ( record.value ( "name" ).toString(), QString ( "Spock" ) );
}

void MemberModelTest::testSetFilter()
{
    ClubFrontend::MemberModel memberModel ( QSqlDatabase::database() );

    memberModel.setFilter ( "deleted='false'" );

    const QSqlTableModel* model = memberModel.findChild<QSqlTableModel* >( "model" );
    QCOMPARE ( model->rowCount(), 1 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "name" ).toString(), QString ( "Kirk" ) );
}

void MemberModelTest::testGetMemberId()
{
    ClubFrontend::MemberModel memberModel ( QSqlDatabase::database() );

    const QSqlTableModel* model = memberModel.findChild<QSqlTableModel* >( "model" );

    const QModelIndex index = model->index ( 0,5 );

    const int id = memberModel.getMemberId ( index );

    QCOMPARE ( id, 1025 );
}

void MemberModelTest::testGetSelectedMembers()
{
    ClubFrontend::MemberModel memberModel ( QSqlDatabase::database() );

    QVector< ClubFrontend::Member > *memberList = memberModel.getSelectedMembers();

    QCOMPARE ( memberList->size(), 2 );
}


}

QTEST_MAIN ( ClubFrontendTest::MemberModelTest )
#include "MemberModelTest.moc"
