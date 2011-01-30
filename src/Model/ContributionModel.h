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

#ifndef CONTRIBUTIONMODEL_H
#define CONTRIBUTIONMODEL_H

#include <QtCore>
#include <QtSql>
#include <QTableView>

namespace ClubFrontend
{

class ContributionModel : public QObject
{
public:
    ContributionModel ( const QSqlDatabase& aDb );
    virtual ~ContributionModel();

    void setMemberId ( const int aMemberId );
    int insertMemberId ( const QVariant& aMemberId );
    void refresh();

    void setTableView ( QTableView* aTableView ) const;
    QSqlTableModel* getContributionTableModel() const;

    QString getInfo() const;
    QVariant getInfoValue() const;
    QString getDonation() const;
    QVariant getDonationValue() const;
    QString getFee() const;
    QVariant getFeeValue() const;

    void submit ( const QString& aFee, const QString& aDonation, const QString& anInfo );

private:
    QVariant returnValue ( int aColumn ) const;

    QSqlTableModel* model;
    QSqlRecord record;
    int memberId;
};

}

#endif // CONTRIBUTIONMODEL_H
