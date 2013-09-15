
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QDate>
#include <QVariant>
#include <QList>
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
    void testFindContributionByMemberIdAndYear();
    void testCalculateSum();
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
    balance->setValuta(QDate(2006,10,15));
    balance->setPurpose("foo bar");
    balance->setAccount(12);
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(-15.0);
    balance->setValuta(QDate(2006,6,14));
    balance->setPurpose("foo bar");
    balance->setAccount(-11);
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(-15.0);
    balance->setValuta(QDate(2007,12,5));
    balance->setPurpose("foo bar");
    balance->setAccount(-11);
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(2);
    balance->setValue(155.0);
    balance->setValuta(QDate(2006,6,15));
    balance->setPurpose("foo bar");
    balance->setAccount(12);
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(15.0);
    balance->setAccount(11);
    balance->setValuta(QDate(2006,12,5));
    balance->setPurpose("foo bar");
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(-10.0);
    balance->setAccount(-12);
    balance->setValuta(QDate(2009,10,15));
    balance->setPurpose("foo bar");
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(-5.0);
    balance->setAccount(-4);
    balance->setValuta(QDate(2010,10,15));
    balance->setPurpose("foo bar");
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(-6.0);
    balance->setAccount(-3);
    balance->setValuta(QDate(2011,10,15));
    balance->setPurpose("foo bar");
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(10);
    balance->setAccount(11);
    balance->setValuta(QDate(2012,10,15));
    balance->setPurpose("foo bar");
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(2);
    balance->setValue(600.0);
    balance->setAccount(11);
    balance->setValuta(QDate(2013,10,15));
    balance->setPurpose("foo bar");
    balance->save();
    delete balance;
}

void BalanceTableModelTest::testCreateModel()
{
    QSqlTableModel *model = membermanager::dao::BalanceTableModel::createModel(2);
    QCOMPARE(model->rowCount(), 2);
    delete model;
}

void BalanceTableModelTest::testFindContributionByMemberIdAndYear()
{
    QList<membermanager::entity::Balance *> list = membermanager::dao::BalanceTableModel::findContributionByMemberIdAndYear(1, 2006);
    QCOMPARE(list.size(), 2);

    for(membermanager::entity::Balance *balance : list) {
        delete balance;
    }
}

void BalanceTableModelTest::testCalculateSum()
{
    double sum = membermanager::dao::BalanceTableModel::calculateFeeSumByMemberId(1);
    QCOMPARE(sum, -16.0);
}



}
}

QTEST_MAIN(test::dao::BalanceTableModelTest)
#include "moc_balancetablemodeltest.cpp"
