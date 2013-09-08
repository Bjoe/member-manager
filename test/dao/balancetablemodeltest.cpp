
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QDate>
#include <QVariant>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/balance.h"

#include "dao/balancetablemodel.h"

namespace test {
namespace dao {

class BalanceTableModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateModel();
};

void BalanceTableModelTest::initTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DATABASEDRIVER);
    db.setDatabaseName(DATABASE);
    if (!db.open()) {
        QSqlError err = db.lastError();
        if (err.type() != QSqlError::NoError) {
            qWarning() << err.text();
        }
    }
    QDjango::setDatabase(db);
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Balance *balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(155.0);
    balance->setValuta(QDate::currentDate());
    balance->setPurpose("foo bar");
    balance->setAccount(23);
    balance->save();
    delete balance;
}

void BalanceTableModelTest::testCreateModel()
{
    QSqlTableModel *model = membermanager::dao::BalanceTableModel::createModel(1);
    QCOMPARE(model->rowCount(), 1);
}

}
}

QTEST_MAIN(test::dao::BalanceTableModelTest)
#include "moc_balancetablemodeltest.cpp"
