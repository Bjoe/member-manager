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

#include "ContributionModelTest.h"

#include "ContributionModel.h"

#include "TestConfig.h"
#include "DatabaseUtils.h"
#include "DatabaseStructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{

void ContributionModelTest::initTestCase()
{
    Utils::DatabaseUtils database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionModelTest::testModel()
{
  ClubFrontend::ContributionModel contributionModel(QSqlDatabase::database());
  
  contributionModel.setMemberId(1025);  
  const QSqlTableModel* model = contributionModel.getContributionTableModel();
  QCOMPARE(model->rowCount(), 2);
  QSqlRecord record = model->record(0);
  using ClubFrontend::ContributionTable;
  QCOMPARE(record.value(ContributionTable::Info).toString(), QString("Beitragsaenderung"));
  QCOMPARE(record.value(ContributionTable::Fee).toString(), QString("15"));
}

void ContributionModelTest::testGetColumns()
{
  ClubFrontend::ContributionModel contributionModel(QSqlDatabase::database());
  
  contributionModel.setMemberId(1025);
  QCOMPARE(contributionModel.getInfo(), QString("Beitragsaenderung"));
  QCOMPARE(contributionModel.getDonation(), QString("1"));
  QCOMPARE(contributionModel.getFee(), QString("15"));
}

void ContributionModelTest::testChangeInfo()
{
  ClubFrontend::ContributionModel contributionModel(QSqlDatabase::database());
  
  contributionModel.setMemberId(1025);
  
  contributionModel.submit("15","1","Foo");
  
  QCOMPARE(contributionModel.getDonation(), QString("1"));
  QCOMPARE(contributionModel.getFee(), QString("15"));
  QCOMPARE(contributionModel.getInfo(), QString("Foo"));
}

void ContributionModelTest::testNewFeeDonation()
{
  ClubFrontend::ContributionModel contributionModel(QSqlDatabase::database());
  
  contributionModel.setMemberId(1025);
  
  QSqlTableModel *model = contributionModel.getContributionTableModel();
  QCOMPARE(model->rowCount(), 2);
  
  contributionModel.submit("90", "50", "bar");
 
  QCOMPARE(model->rowCount(), 3);
  
  contributionModel.refresh();
  QCOMPARE(contributionModel.getDonation(), QString("50"));
  QCOMPARE(contributionModel.getFee(), QString("90"));
  QCOMPARE(contributionModel.getInfo(), QString("bar"));
  
  const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(1025);
  QSqlQuery query;
  using ClubFrontend::ContributionTable;
  query.exec("select * from " + ContributionTable::TABLENAME + whereClause + 
    " order by " + ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " desc");
  query.next();
  QCOMPARE(query.value(ContributionTable::Fee).toInt(), 90);
  QCOMPARE(query.value(ContributionTable::Donation).toInt(), 50);
  QCOMPARE(query.value(ContributionTable::Info).toString(), QString("bar"));
  
  // TODO Test auf ValidFrom mit QDate::currentDate()
}

}

QTEST_MAIN(ClubFrontendTest::ContributionModelTest)
#include "ContributionModelTest.moc"
