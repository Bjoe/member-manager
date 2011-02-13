/*
 * MemberModel.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */
#include "MemberModel.h"

#include "Model/MemberDetailModel.h"
#include "Model/DatabaseStructure.h"

namespace ClubFrontend
{
namespace Model
{

MemberModel::MemberModel ( const QSqlDatabase& aDb ) :
        model ( new QSqlTableModel ( this, aDb ) )
{
    model->setObjectName ( MemberTable::TABLENAME );
    model->setTable ( MemberTable::TABLENAME );
    model->setHeaderData ( MemberTable::MemberId, Qt::Horizontal, tr ( "Nr." ) );
    model->setHeaderData ( MemberTable::FirstName, Qt::Horizontal, tr ( "Vorname" ) );
    model->setHeaderData ( MemberTable::Name, Qt::Horizontal, tr ( "Name" ) );
    model->setHeaderData ( MemberTable::NickName, Qt::Horizontal, tr ( "Nickname" ) );
    model->setHeaderData ( MemberTable::EntryDate, Qt::Horizontal, tr ( "Eintritts Datum" ) );
    model->setHeaderData ( MemberTable::Info, Qt::Horizontal, tr ( "Info" ) );
    refresh();
}

MemberModel::~MemberModel()
{
    delete model;
}

void MemberModel::setFilter ( const QString aSqlFilter )
{
    model->setFilter ( aSqlFilter );
    refresh();
}

void MemberModel::refresh()
{
    model->select();
}

int MemberModel::getMemberId ( const QModelIndex& anIndex )
{
    QSqlRecord record = model->record ( anIndex.row() );
    return record.value ( MemberTable::MemberId ).toInt();
}

QVector< Member > * MemberModel::getSelectedMembers()
{
    int size = model->rowCount();
    QVector< Member > *memberList = new QVector< Member > ( size );
    for ( int i = 0; i < size; i++ )
    {
        QSqlRecord record = model->record ( i );
        QVariant value = record.value ( MemberTable::MemberId );

        MemberDetailModel memberDetail;
        memberDetail.setMemberId ( value.toInt() );
        Member member = memberDetail.exportMember();
        memberList->replace ( i, member );
    }
    return memberList;
}

QString MemberModel::getLastError() const
{
    return model->lastError().text();
}

void MemberModel::initTableView ( QTableView* aTableView ) const
{
    aTableView->setModel ( model );
    aTableView->setColumnHidden ( MemberTable::Deleted, true );
    aTableView->setColumnHidden ( MemberTable::FOO_CCC, true );
    aTableView->setColumnHidden ( MemberTable::FOO_ChaosNr, true );
    aTableView->setColumnHidden ( MemberTable::FOO_ClubAdress, true );
    aTableView->setColumnHidden ( MemberTable::FOO_Einzug, true );
    aTableView->setColumnHidden ( MemberTable::FOO_intern, true );
    aTableView->setColumnHidden ( MemberTable::FOO_Shell, true );

    aTableView->sortByColumn ( MemberTable::MemberId, Qt::AscendingOrder );
}

}
}
