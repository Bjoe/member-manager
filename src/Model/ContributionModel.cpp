/*
    Copyright (c) <year>, <copyright holder>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "ContributionModel.h"

#include "Model/DatabaseStructure.h"
#include "Model/TableDao.h"

namespace ClubFrontend
{

ContributionModel::ContributionModel ( const QSqlDatabase& aDb ) :
        model ( new QSqlTableModel ( this, aDb ) ), record(), memberId ( 0 )
{
    model->setObjectName ( "model" );
    record = model->record ( 0 );

    model->setTable ( ContributionTable::TABLENAME );
    model->setHeaderData ( ContributionTable::Fee, Qt::Horizontal, tr ( "Beitrag" ) );
    model->setHeaderData ( ContributionTable::Donation, Qt::Horizontal, tr ( "Spende" ) );
    model->setHeaderData ( ContributionTable::ValidFrom, Qt::Horizontal, tr ( "Gültig ab:" ) );
    model->setHeaderData ( ContributionTable::Info, Qt::Horizontal, tr ( "Info" ) );
}

ContributionModel::~ContributionModel()
{
}

//! \todo Refactor selectMemberId
void ContributionModel::setMemberId ( const int aMemberId )
{
    QString columname = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    QString filter = QString ( columname + " = %1" ).arg ( aMemberId );
    model->setFilter ( filter );
    model->setSort ( ContributionTable::ValidFrom, Qt::DescendingOrder );
    refresh();
    memberId = aMemberId;
}

int ContributionModel::insertMemberId ( const QVariant& aMemberId )
{
    model->setFilter ( "" );
    model->select();
    Model::TableDao tableDao;
    int row = tableDao.insertNewRow ( model, ContributionTable::MemberId, aMemberId );
    setMemberId ( aMemberId.toInt() );
    return row;
}

void ContributionModel::refresh()
{
    model->select();
    record = model->record ( 0 );
}

QString ContributionModel::getDonation() const
{
    return getDonationValue().toString();
}

QVariant ContributionModel::getDonationValue() const
{
    return record.value ( ContributionTable::Donation );
}

QString ContributionModel::getFee() const
{
    return getFeeValue().toString();
}

QVariant ContributionModel::getFeeValue() const
{
    return record.value ( ContributionTable::Fee );
}

QString ContributionModel::getInfo() const
{
    return getInfoValue().toString();
}

QVariant ContributionModel::getInfoValue() const
{
    return record.value ( ContributionTable::Info );
}


// TODO Refactor: In DAO Klasse Refactoren
void ContributionModel::submit ( const QString &aFee, const QString &aDonation, const QString &anInfo )
{
    QString fee = getFee();
    QString donation = getDonation();

    if ( fee.compare ( aFee ) != 0 || donation.compare ( aDonation ) != 0 )
    {
        QSqlRecord newRecord = model->record();
        newRecord.setValue ( ContributionTable::MemberId, memberId );
        newRecord.setValue ( ContributionTable::Fee, QVariant ( aFee ) );
        newRecord.setValue ( ContributionTable::Donation, QVariant ( aDonation ) );
        newRecord.setValue ( ContributionTable::Info, QVariant ( anInfo ) );
        QDate date = QDate::currentDate();
        newRecord.setValue ( ContributionTable::ValidFrom, QVariant ( date.toString ( Qt::ISODate ) ) );
        model->insertRecord ( -1, newRecord );
    }
    else
    {
        record.setValue ( ContributionTable::Info, QVariant ( anInfo ) );
        model->setRecord ( 0,record );
    }
    model->submitAll();
}

void ContributionModel::initTableView ( QTableView* aTableView ) const
{
    aTableView->setModel ( model );

    aTableView->setColumnHidden ( ContributionTable::ContributionId, true );
    aTableView->setColumnHidden ( ContributionTable::MemberId, true );
    aTableView->setColumnHidden ( ContributionTable::Debit, true );
}

}
