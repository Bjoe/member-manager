#include "debitsumsummarytest.h"

#include "debitsumsummary.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"
#include "member.h"
#include "memberfactory.h"
#include "summarywriter.h"

#include <QString>
#include <QSqlTableModel>

namespace membermanagertest
{

void DebitSumSummaryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void DebitSumSummaryTest::testDebitSum()
{
    class : public membermanager::SummaryWriter
    {
    public:
        QString content;

        virtual void writeContent(const QString &aContent)
        {
            content.append(aContent);
        }
    } writer;

    QSqlTableModel model;
    model.setTable(membermanager::model::MemberTable::TABLENAME);
    model.select();

    QList<membermanager::Member> memberList = membermanager::MemberFactory::createMemberList(&model);
    membermanager::DebitSumSummary debitSum(memberList);

    QCOMPARE(debitSum.getTitle(), QString("Saldo"));

    debitSum.setWriter(&writer);
    debitSum.handleHtmlText();

    QCOMPARE(writer.content, QString("To:  fooo@baaar.xx<br>Name  Kirk<br>Mitgliedschulden -15<br><br>Gesamt Saldo: -15<br>"));
}

}

QTEST_MAIN(membermanagertest::DebitSumSummaryTest)
#include "debitsumsummarytest.moc"
