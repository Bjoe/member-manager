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

#include "ContributionDialogTest.h"

#include "Gui/ContributionDialog.h"

#include "TestConfig.h"
#include <DatabaseUtils.h>
#include "Model/DatabaseStructure.h"
#include "Model/ContributionModel.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPoint>
#include <QVariant>
#include <QString>

namespace ClubFrontendTest
{
namespace Gui
{

void ContributionDialogTest::initTestCase()
{
    TestUtils::Database::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void ContributionDialogTest::testShowDialog()
{
    ClubFrontend::Model::ContributionModel contributionModel ( QSqlDatabase::database() );
    contributionModel.setMemberId ( 1025 );
    ClubFrontend::Gui::ContributionDialog dialog ( &contributionModel );

    const QTableView* tableView = dialog.findChild<QTableView* > ( "contributionTableView" );
    const QAbstractItemModel* model = tableView->model();
    QVERIFY ( model != 0 );
    QCOMPARE ( model->rowCount(), 2 );
    using ClubFrontend::Model::ContributionTable;
    const QModelIndex index = model->index ( 0, ContributionTable::ValidFrom );
    const QVariant value = model->data ( index );
    QCOMPARE ( value.toString(), QString ( "2007-05-01" ) );
}


}
}

QTEST_MAIN ( ClubFrontendTest::Gui::ContributionDialogTest )
#include "ContributionDialogTest.moc"
