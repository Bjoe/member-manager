
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QDate>
#include <QVariant>

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
    void testFindByMemberId();
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
    contribution->setFee(15.0);
    contribution->setAdditionalFee(0);
    contribution->setDonation(0);
    contribution->setValidFrom(QDate::currentDate());
    contribution->save();
    delete contribution;
}

void ContributionTableModelTest::testFindByMemberId()
{
    membermanager::entity::Contribution *contribution = membermanager::dao::ContributionTableModel::findByMemberId(1);
    double fee = 15.0;
    QCOMPARE(contribution->fee(), fee);
}

}
}

QTEST_MAIN(test::dao::ContributionTableModelTest)
#include "moc_contributiontablemodeltest.cpp"
