#include "MemberDetailModelTest.h"

#include "Model/MemberDetailModel.h"
#include "Model/Member.h"

#include "TestConfig.h"
#include <DatabaseUtils.h>
#include "Model/DatabaseStructure.h"

#include <QDebug>
#include <QSqlRecord>

namespace ClubFrontendTest
{
namespace Model
{

void MemberDetailModelTest::initTestCase()
{
    TestUtils::Database::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void MemberDetailModelTest::testGetAddressModel()
{
    ClubFrontend::Model::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.findChild<QSqlTableModel* > ( ClubFrontend::Model::AddressTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "ort" ).toString(), QString ( "Bloedeldorff" ) );
}

void MemberDetailModelTest::testGetBankAccountModel()
{
    ClubFrontend::Model::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.findChild<QSqlTableModel* > ( ClubFrontend::Model::BankAccountTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 1 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "bank" ).toString(), QString ( "sparstrumpf" ) );
}

void MemberDetailModelTest::testGetContributionModel()
{
    ClubFrontend::Model::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.getContributionModel()->findChild<QSqlTableModel* > ( ClubFrontend::Model::ContributionTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 0 );

    dataSource.setMemberId ( 1025 );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    double fee = 15.00;
    QCOMPARE ( record.value ( "beitrag" ).toDouble(), fee );
}

void MemberDetailModelTest::testGetRessourcenModel()
{
    ClubFrontend::Model::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.findChild<QSqlTableModel* > ( ClubFrontend::Model::RessourcenTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 1 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "email" ).toString(), QString ( "fooo@baaar.xx" ) );
}

void MemberDetailModelTest::testGetMemberModel()
{
    ClubFrontend::Model::MemberDetailModel memberModel ( QSqlDatabase::database() );

    const QSqlTableModel* model = memberModel.findChild<QSqlTableModel* > ( ClubFrontend::Model::MemberTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "name" ).toString(), QString ( "Kirk" ) );
}

void MemberDetailModelTest::testGetMember()
{
    ClubFrontend::Model::MemberDetailModel memberModel ( QSqlDatabase::database() );

    memberModel.setMemberId ( 1025 );
    ClubFrontend::Member member = memberModel.exportMember();

    QCOMPARE ( member.getMemberId(), 1025 );
    QCOMPARE ( member.getName(), QString ( "Kirk" ) );
    QCOMPARE ( member.getFirstname(), QString ( "James T" ) );
    QCOMPARE ( member.getNickname(), QString ( "Capt. Kirk" ) );
    float donation = 1;
    QCOMPARE ( member.getDonation(), donation );
    float fee = 15;
    QCOMPARE ( member.getFee(), fee );

}

void MemberDetailModelTest::testSetMemberId()
{
    ClubFrontend::Model::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* ressourcenModel =
        dataSource.findChild<QSqlTableModel* > ( ClubFrontend::Model::RessourcenTable::TABLENAME );
    const QSqlTableModel* addressModel = dataSource.findChild<QSqlTableModel* > ( ClubFrontend::Model::AddressTable::TABLENAME );
    const QSqlTableModel* contributionModel =
        dataSource.getContributionModel()->findChild<QSqlTableModel* > ( ClubFrontend::Model::ContributionTable::TABLENAME );
    const QSqlTableModel* accountModel = dataSource.findChild<QSqlTableModel* > ( ClubFrontend::Model::BankAccountTable::TABLENAME );
    const QSqlTableModel* memberModel = dataSource.findChild<QSqlTableModel* > ( ClubFrontend::Model::MemberTable::TABLENAME );

    dataSource.setMemberId ( 1025 );

    QCOMPARE ( memberModel->rowCount(), 1 );
    QSqlRecord record = memberModel->record ( 0 );
    QCOMPARE ( record.value ( "name" ).toString(), QString ( "Kirk" ) );

    QCOMPARE ( addressModel->rowCount(), 1 );
    record = addressModel->record ( 0 );
    QCOMPARE ( record.value ( "ort" ).toString(), QString ( "Bloedeldorf" ) );

    QCOMPARE ( accountModel->rowCount(), 1 );
    record = accountModel->record ( 0 );
    QCOMPARE ( record.value ( "bank" ).toString(), QString ( "sparstrumpf" ) );

    QCOMPARE ( contributionModel->rowCount(), 2 );
    record = contributionModel->record ( 0 );
    double fee = 15.00;
    QCOMPARE ( record.value ( "beitrag" ).toDouble(), fee );

    QCOMPARE ( ressourcenModel->rowCount(), 1 );
    record = ressourcenModel->record ( 0 );
    QCOMPARE ( record.value ( "email" ).toString(), QString ( "fooo@baaar.xx" ) );

    QCOMPARE ( dataSource.getMemberId(), 1025 );
}

void MemberDetailModelTest::testNewMember()
{
    ClubFrontend::Model::MemberDetailModel memberDetailModel ( QSqlDatabase::database() );
    int id = memberDetailModel.newMember();

    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* > ( ClubFrontend::Model::MemberTable::TABLENAME ),
                             ClubFrontend::Model::MemberTable::MemberId ), id );
    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* > ( ClubFrontend::Model::AddressTable::TABLENAME ),
                             ClubFrontend::Model::AddressTable::MemberId ), id );
    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* > ( ClubFrontend::Model::BankAccountTable::TABLENAME ),
                             ClubFrontend::Model::BankAccountTable::MemberId ), id );
    const ClubFrontend::Model::ContributionModel* contributionModel = memberDetailModel.getContributionModel();
    const QSqlTableModel* contributionTableModel = contributionModel->findChild<QSqlTableModel* > ( ClubFrontend::Model::ContributionTable::TABLENAME );
    QCOMPARE ( getMemberId ( contributionTableModel,
                             ClubFrontend::Model::ContributionTable::MemberId ), id );
    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* > ( ClubFrontend::Model::RessourcenTable::TABLENAME ),
                             ClubFrontend::Model::RessourcenTable::MemberId ), id );
}

void MemberDetailModelTest::testDeleteMember()
{
    ClubFrontend::Model::MemberDetailModel memberDetailModel ( QSqlDatabase::database() );
    int id = memberDetailModel.newMember();

    memberDetailModel.deleteMember();

    const QString whereClause = QString ( " where dorfmitglied_pkey=%1" ).arg ( id );

    using ClubFrontend::Model::MemberTable;
    QSqlQuery query;
    query.exec ( "select * from " + MemberTable::TABLENAME + whereClause );
    QVERIFY ( !query.next() );


}

int MemberDetailModelTest::getMemberId ( const QSqlTableModel* aModel,
        const int& aColumnId )
{
    QSqlRecord record = aModel->record ( 0 );
    return record.value ( aColumnId ).toInt();
}

}
}

QTEST_MAIN ( ClubFrontendTest::Model::MemberDetailModelTest )
#include "MemberDetailModelTest.moc"
