#include "Model/MemberDetailModel.h"
#include "Model/DatabaseStructure.h"

namespace ClubFrontend
{
namespace Model
{
  
MemberDetailModel::MemberDetailModel ( const QSqlDatabase& aDb ) :
        addressModel ( new QSqlTableModel ( this, aDb ) ), bankAccountModel (
            new QSqlTableModel ( this, aDb ) ), ressourcenModel ( new QSqlTableModel (
                        this, aDb ) ), memberModel ( new QSqlTableModel ( this, aDb ) ),
        contributionModel ( new ContributionModel ( aDb ) ), id ( 0 )
{
    setTableModel ( AddressTable::TABLENAME, addressModel );
    setTableModel ( BankAccountTable::TABLENAME, bankAccountModel );
    setTableModel ( RessourcenTable::TABLENAME, ressourcenModel );
    setTableModel ( MemberTable::TABLENAME, memberModel );
}

MemberDetailModel::~MemberDetailModel()
{
}

void MemberDetailModel::setTableModel ( const QString& aTableName,
        QSqlTableModel* const aModel )
{
    aModel->setTable ( aTableName );
    aModel->setObjectName ( aTableName );
    aModel->select();
}

QString MemberDetailModel::getLastError() const
{
    //! \todo besser model->lastError()
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}

void MemberDetailModel::setMemberId ( int anId )
{
    id = anId;

    QString pkey = MemberTable::COLUMNNAME[MemberTable::MemberId];
    QString filter = QString ( pkey + " = %1" ).arg ( id );
    addressModel->setFilter ( filter );
    addressModel->select();
    bankAccountModel->setFilter ( filter );
    bankAccountModel->select();
    ressourcenModel->setFilter ( filter );
    ressourcenModel->select();
    memberModel->setFilter ( filter );
    memberModel->select();

    contributionModel->setMemberId ( id );
}

int MemberDetailModel::getMemberId() const
{
    return id;
}

Member MemberDetailModel::exportMember() const
{
    QSqlRecord memberRecord = memberModel->record ( 0 );
    QVariant name = memberRecord.value ( MemberTable::Name );
    QVariant firstname = memberRecord.value ( MemberTable::FirstName );
    QVariant nickname = memberRecord.value ( MemberTable::NickName );
    QVariant fee = contributionModel->getFeeValue();
    QVariant donation = contributionModel->getDonationValue();

    return Member ( id, name.toString(), firstname.toString(), nickname.toString(),
                    donation.toFloat(), fee.toFloat() );
}

//! \todo Refactor: In DAO Klasse Refactoren
int MemberDetailModel::newMember()
{
    // Dirty Hack um ein Neues Mitglied einzutragen.
    QVariant variant ( true );
    int row = insertNewMember ( memberModel, MemberTable::Deleted, variant );
    QSqlRecord record = memberModel->record ( row );
    QVariant valueId = record.value ( MemberTable::MemberId );

    insertNewMember ( addressModel, AddressTable::MemberId, valueId );
    insertNewMember ( bankAccountModel, BankAccountTable::MemberId, valueId );
    contributionModel->insertMemberId ( valueId );
    insertNewMember ( ressourcenModel, RessourcenTable::MemberId, valueId );

    int newId = valueId.toInt();
    setMemberId ( newId );
    return newId;
}

//! \todo Refactor: In DAO Klasse Refactoren
int MemberDetailModel::insertNewMember ( QSqlTableModel* aModel,
        const int& aColumnId, const QVariant& aValue )
{
    QSqlRecord record = aModel->record();
    record.setValue ( aColumnId, aValue );
    int row = aModel->rowCount();
    aModel->insertRow ( row );
    aModel->setRecord ( row, record );
    aModel->submitAll();
    return row;
}

//! \todo Refactor: In DAO Klasse Refactoren
void MemberDetailModel::deleteMember()
{
    if ( id == 0 )
        return;

    const QString whereClause = QString ( " where %1=%2" ).arg (
                                    MemberTable::COLUMNNAME[MemberTable::MemberId] ).arg ( id );
    const QString columnDeteled = MemberTable::COLUMNNAME[MemberTable::Deleted];

    QSqlQuery query ( "select * from " + MemberTable::TABLENAME + whereClause
                      + " AND " + columnDeteled + "='false'" );
    if ( query.next() )
    {
        query .exec ( "update " + MemberTable::TABLENAME + " set "
                      + columnDeteled + "='true' " + whereClause + " AND "
                      + columnDeteled + "='false'" );
    }
    else
    {
        query.exec ( "delete from " + MemberTable::TABLENAME + whereClause );
        query.exec ( "delete from " + AddressTable::TABLENAME + whereClause );
        query.exec ( "delete from " + BankAccountTable::TABLENAME + whereClause );
        query.exec ( "delete from " + ContributionTable::TABLENAME + whereClause
                     + " AND " + ContributionTable::COLUMNNAME[ContributionTable::Fee] + " isNull AND " +
                     ContributionTable::COLUMNNAME[ContributionTable::Donation] + " isNull AND " +
                     ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " isNull AND" +
                     ContributionTable::COLUMNNAME[ContributionTable::Info] + " isNull" );
        query.exec ( "delete from " + RessourcenTable::TABLENAME + whereClause );
    }
}

void MemberDetailModel::initAddressMapper ( QDataWidgetMapper* aMapper ) const
{
    aMapper->setModel ( addressModel );
}

void MemberDetailModel::initBankAccountMapper ( QDataWidgetMapper* aMapper ) const
{
    aMapper->setModel ( bankAccountModel );
}

void MemberDetailModel::initMemberMapper ( QDataWidgetMapper* aMapper ) const
{
    aMapper->setModel ( memberModel );
}

void MemberDetailModel::initRessourcenMapper ( QDataWidgetMapper* aMapper ) const
{
    aMapper->setModel ( ressourcenModel );
}

ContributionModel* MemberDetailModel::getContributionModel() const
{
    return contributionModel;
}

}
}
