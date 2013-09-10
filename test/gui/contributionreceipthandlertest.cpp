
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/contribution.h"

#include "gui/contributionreceipthandler.h"

namespace test {
namespace gui {

class ContributionReceiptHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowReceipt();
};

void ContributionReceiptHandlerTest::initTestCase()
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
    contribution->save();
    delete contribution;
}

void ContributionReceiptHandlerTest::testShowReceipt()
{
    membermanager::gui::ContributionReceiptHandler handler;
    QString content = handler.showReceipt(1,2006);
    QSKIP("Add a test for content");
}

}
}

QTEST_MAIN(test::gui::ContributionReceiptHandlerTest)
#include "moc_contributionreceipthandlertest.cpp"

