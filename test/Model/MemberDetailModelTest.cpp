#include "MemberDetailModelTest.h"

#include "Model/MemberDetailModel.h"
#include "Model/Member.h"

#include "TestConfig.h"
#include "TestUtils/DatabaseUtils.h"
#include "Model/DatabaseStructure.h"

#include <QDebug>
#include <QSqlRecord>

namespace ClubFrontendTest
{

void MemberDetailModelTest::initTestCase()
{
    Utils::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void MemberDetailModelTest::testGetAddressModel()
{
    ClubFrontend::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.findChild<QSqlTableModel* >( ClubFrontend::AddressTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "ort" ).toString(), QString ( "Bloedeldorff" ) );
}

void MemberDetailModelTest::testGetBankAccountModel()
{
    ClubFrontend::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.findChild<QSqlTableModel* >( ClubFrontend::BankAccountTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 1 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "bank" ).toString(), QString ( "sparstrumpf" ) );
}

void MemberDetailModelTest::testGetContributionModel()
{
    ClubFrontend::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.getContributionModel()->findChild<QSqlTableModel* > ( "model" );
    QCOMPARE ( model->rowCount(), 0 );

    dataSource.setMemberId ( 1025 );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    double fee = 15.00;
    QCOMPARE ( record.value ( "beitrag" ).toDouble(), fee );
}

void MemberDetailModelTest::testGetRessourcenModel()
{
    ClubFrontend::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* model = dataSource.findChild<QSqlTableModel* >( ClubFrontend::RessourcenTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 1 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "email" ).toString(), QString ( "fooo@baaar.xx" ) );
}

void MemberDetailModelTest::testGetMemberModel()
{
    ClubFrontend::MemberDetailModel memberModel ( QSqlDatabase::database() );

    const QSqlTableModel* model = memberModel.findChild<QSqlTableModel* >( ClubFrontend::MemberTable::TABLENAME );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( "name" ).toString(), QString ( "Kirk" ) );
}

void MemberDetailModelTest::testGetMember()
{
    ClubFrontend::MemberDetailModel memberModel ( QSqlDatabase::database() );

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
    ClubFrontend::MemberDetailModel dataSource ( QSqlDatabase::database() );

    const QSqlTableModel* ressourcenModel =
        dataSource.getRessourcenTableModel();
    const QSqlTableModel* addressModel = dataSource.findChild<QSqlTableModel* >( ClubFrontend::AddressTable::TABLENAME );
    const QSqlTableModel* contributionModel =
        dataSource.getContributionModel()->findChild<QSqlTableModel* > ( "model" );
    const QSqlTableModel* accountModel = dataSource.findChild<QSqlTableModel* >( ClubFrontend::BankAccountTable::TABLENAME );
    const QSqlTableModel* memberModel = dataSource.findChild<QSqlTableModel* >( ClubFrontend::MemberTable::TABLENAME );

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
    ClubFrontend::MemberDetailModel memberDetailModel ( QSqlDatabase::database() );
    int id = memberDetailModel.newMember();

    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* >( ClubFrontend::MemberTable::TABLENAME ),
                             ClubFrontend::MemberTable::MemberId ), id );
    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* >( ClubFrontend::AddressTable::TABLENAME ),
                             ClubFrontend::AddressTable::MemberId ), id );
    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* >( ClubFrontend::BankAccountTable::TABLENAME ),
                             ClubFrontend::BankAccountTable::MemberId ), id );
    const ClubFrontend::ContributionModel* contributionModel = memberDetailModel.getContributionModel();
    const QSqlTableModel* contributionTableModel = contributionModel->findChild<QSqlTableModel* > ( "model" );
    QCOMPARE ( getMemberId ( contributionTableModel,
                             ClubFrontend::ContributionTable::MemberId ), id );
    QCOMPARE ( getMemberId ( memberDetailModel.findChild<QSqlTableModel* >( ClubFrontend::RessourcenTable::TABLENAME ),
                             ClubFrontend::RessourcenTable::MemberId ), id );
}

void MemberDetailModelTest::testDeleteMember()
{
    ClubFrontend::MemberDetailModel memberDetailModel ( QSqlDatabase::database() );
    int id = memberDetailModel.newMember();

    memberDetailModel.deleteMember();

    const QString whereClause = QString ( " where dorfmitglied_pkey=%1" ).arg ( id );

    using ClubFrontend::MemberTable;
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

QTEST_MAIN ( ClubFrontendTest::MemberDetailModelTest )
#include "MemberDetailModelTest.moc"
