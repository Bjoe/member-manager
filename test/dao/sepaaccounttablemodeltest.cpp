
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QVariant>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/sepaaccount.h"

#include "dao/sepaaccounttablemodel.h"

namespace test {
namespace dao {

class SepaAccountTableModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testFindByMemberId();
    void testFindNothing();
};

void SepaAccountTableModelTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::SepaAccount>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::SepaAccount *sepaAccount = new membermanager::entity::SepaAccount();
    sepaAccount->setMemberId("1");
    sepaAccount->setBic("DUSSDEDDXXX");
    sepaAccount->setIban("DE26312345670012345678");
    sepaAccount->setMandateDate(QDate(2013,11,30));
    sepaAccount->setSequenceState("FIRST");
    sepaAccount->save();
    delete sepaAccount;
}

void SepaAccountTableModelTest::testFindByMemberId()
{
    membermanager::entity::SepaAccount *sepaAccount = membermanager::dao::SepaAccountTableModel::findByMemberId("1");
    QCOMPARE(sepaAccount->iban(), QString("DE26312345670012345678"));
}

void SepaAccountTableModelTest::testFindNothing()
{
    membermanager::entity::SepaAccount *sepaAccount = membermanager::dao::SepaAccountTableModel::findByMemberId("2");
    QCOMPARE(sepaAccount->iban(), QString(""));
}

}
}

QTEST_MAIN(test::dao::SepaAccountTableModelTest)
#include "moc_sepaaccounttablemodeltest.cpp"
