
#include <QtTest/QtTest>

#include <QString>
#include <QTextStream>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>

#include "QDjango.h"
#include "QDjangoQuerySet.h"

#include "testconfig.h"

#include "swift/importer.h"
#include "entity/cashaccount.h"

#include "accounting/cashimporter.h"

namespace test {
namespace accounting {

class CashImporterTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testImportStream();
};

void CashImporterTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::CashAccount>();

    QDjango::dropTables();
    QDjango::createTables();
}

void CashImporterTest::testImportStream()
{
    QString data = QString(":20:STARTUMSE\n"
                         ":25:29485723/0932104953\n"
                         ":28C:00016/001\n"
                         ":60F:C120928EUR9503,91\n"
                         ":61:1210011001DR199,00N012NONREF\n"
                         ":86:008?00DAUERAUFTRAG?107000?20KOHLE UND LK?3094392193?313945824\n"
                         "293?32HANZ MEIERSEN?34997\n"
                         ":62F:C121001EUR8493,91\n"
                         "-\n");
    QTextStream stream;
    stream.setString(&data);

    membermanager::accounting::CashImporter importer(&stream);

    importer.logMessageSlot(
        [] (QString message)
        {
            qDebug() << message;
        }
    );

    QVERIFY(importer.import("29485723", "0932104953"));

    QDjangoQuerySet<membermanager::entity::CashAccount> result;
    QCOMPARE(result.size(), 1);
    QList<QVariantMap> propertyMaps = result.values(QStringList() << "value" << "purpose");
    QVariantMap property = propertyMaps.at(0);
    QCOMPARE(property["value"], QVariant(-199.0));
    QCOMPARE(property["purpose"], QVariant("KOHLE UND LK"));
}

}
}

QTEST_MAIN(test::accounting::CashImporterTest)
#include "moc_cashimportertest.cpp"
