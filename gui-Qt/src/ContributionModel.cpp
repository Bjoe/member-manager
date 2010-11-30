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

#include "DatabaseStructure.h"

namespace ClubFrontend
{

ContributionModel::ContributionModel(const QSqlDatabase& aDb):
  model(new QSqlTableModel(this, aDb))
{
  model->setTable(ContributionTable::TABLENAME);
  model->setHeaderData(ContributionTable::Fee, Qt::Horizontal, tr("Beitrag"));
  model->setHeaderData(ContributionTable::Donation, Qt::Horizontal, tr("Spende"));
  model->setHeaderData(ContributionTable::ValidFrom, Qt::Horizontal, tr("Gültig ab:"));
  model->setHeaderData(ContributionTable::Info, Qt::Horizontal, tr("Info"));
}

ContributionModel::~ContributionModel()
{
}

void ContributionModel::setMemberId(const int aMemberId)
{
  QString columname = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
  QString filter = QString(columname + " = %1").arg(aMemberId);
  model->setFilter(filter);
  model->setSort(ContributionTable::ValidFrom, Qt::DescendingOrder);
  refresh();
}

void ContributionModel::refresh()
{
  model->select();
}

QString ContributionModel::getDonation() const
{
  return returnValue(ContributionTable::Donation).toString();
}

QString ContributionModel::getFee() const
{
  return returnValue(ContributionTable::Fee).toString();
}

QString ContributionModel::getInfo() const
{
  return returnValue(ContributionTable::Info).toString();
}

QVariant ContributionModel::returnValue(int aColumn) const
{
  QSqlRecord record = model->record(0);
  return record.value(aColumn);
}

QSqlTableModel* ContributionModel::getContributionTableModel() const
{
  return model;
}

}
