
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QDate>
#include <QVariant>
#include <QSqlTableModel>
#include <QSqlRecord>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/contribution.h"

#include "dao/contributiontablemodel.h"

namespace test {
namespace dao {

class ContributionTableModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateModel();
    void testFindLastEntryByMemberId();
    void testFindByMemberIdAndPointInTime();
};

void ContributionTableModelTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Contribution>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Contribution *contribution = new membermanager::entity::Contribution();
    contribution->setMemberId(1);
    contribution->setFee(1.0);
    contribution->setAdditionalFee(0);
    contribution->setDonation(0);
    contribution->setValidFrom(QDate(2013, 1, 1));
    contribution->save();
    delete contribution;

    contribution = new membermanager::entity::Contribution();
    contribution->setMemberId(1);
    contribution->setFee(2.0);
    contribution->setAdditionalFee(0);
    contribution->setDonation(0);
    contribution->setValidFrom(QDate(2013, 9, 1));
    contribution->save();
    delete contribution;

    contribution = new membermanager::entity::Contribution();
    contribution->setMemberId(1);
    contribution->setFee(3.0);
    contribution->setAdditionalFee(0);
    contribution->setDonation(0);
    contribution->setValidFrom(QDate(2013, 5, 1));
    contribution->save();
    delete contribution;
}

void ContributionTableModelTest::testCreateModel()
{
    QSqlTableModel* model = membermanager::dao::ContributionTableModel::createModel(1);
    QCOMPARE(model->rowCount(), 3);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(7).toString(), QString("2013-09-01"));
    delete model;
}

void ContributionTableModelTest::testFindLastEntryByMemberId()
{
    membermanager::entity::Contribution* contribution = membermanager::dao::ContributionTableModel::findLastEntryByMemberId(1);
    QCOMPARE(contribution->fee(), 2.0);
    delete contribution;
}

void ContributionTableModelTest::testFindByMemberIdAndPointInTime()
{
    membermanager::entity::Contribution* contribution = membermanager::dao::ContributionTableModel::findByMemberIdWithPointInTime(1, QDate(2013, 8, 1));
    QCOMPARE(contribution->fee(), 3.0);
    delete contribution;
}

}
}

QTEST_MAIN(test::dao::ContributionTableModelTest)
#include "moc_contributiontablemodeltest.cpp"
