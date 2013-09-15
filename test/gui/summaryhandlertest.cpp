
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QObject>
#include <QChar>
#include <QString>
#include <QDate>
#include <QVariant>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "gui/summaryhandler.h"

#include "entity/member.h"

namespace test {
namespace gui {

class SummaryHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCalculate();
};

void SummaryHandlerTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Member>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Member *member = new membermanager::entity::Member();
    member->setMemberId(1);
    member->setName("Kirk");
    member->setFirstname("James T.");
    member->setEmail("enterprise@startrek.com");
    member->setEntryDate(QDate(2013,8,10));
    member->setStreet("universe");
    member->setCity("NCC");
    member->setZipCode("1701");
    member->setCollectionState(membermanager::entity::Member::CollectionState::known);
    member->setState(membermanager::entity::Member::State::deleted);
    member->save();
    delete member;

}

void SummaryHandlerTest::testCalculate()
{
    QSKIP("Test fehlt noch");
}

}
}

QTEST_MAIN(test::gui::SummaryHandlerTest)
#include "moc_summaryhandlertest.cpp"
