#include "SaldoDialogTest.h"

#include "SaldoDialog.h"

#include "TestData.h"
#include "SaldoModel.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPoint>
#include <QVariant>
#include <QString>
#include <QLabel>

#include <QDebug>

namespace ClubFrontendTest
{

    void SaldoDialogTest::initTestCase()
    {
        TestData testData;
        testData.createFakeBalanceTable();
    }

    void SaldoDialogTest::testShowDialog()
    {
        ClubFrontend::SaldoModel saldoModel(QSqlDatabase::database(), 1025);
        ClubFrontend::SaldoDialog dialog(saldoModel);

        QTableView* tableView = dialog.findChild<QTableView* >("saldoTableView");
        const QAbstractItemModel* model = tableView->model();
        QVERIFY(model != 0);
        QCOMPARE(model->rowCount(), 2);
		QModelIndex index = model->index(0,3);
        QVariant value = model->data(index);
        QCOMPARE(value.toString(), QString("2005-09-18"));
    }
    
    void SaldoDialogTest::testShowSum()
    {
        ClubFrontend::SaldoModel saldoModel(QSqlDatabase::database(), 1025);
        ClubFrontend::SaldoDialog dialog(saldoModel);

	QLabel* sumLabel = dialog.findChild<QLabel* >("sumLabel");
	QCOMPARE(sumLabel->text(), QString("Summe: -15"));
    }
}
