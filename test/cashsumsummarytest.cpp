#include "cashsumsummarytest.h"

#include "cashsumsummary.h"

#include "testconfig.h"
#include "dao/databasestructure.h"
#include "database/databaseutil.h"
#include "member.h"
#include "summarywriter.h"
#include "dao/memberdao.h"

#include <QString>
#include <QSqlTableModel>
#include <QDate>

namespace membermanagertest
{

void CashSumSummaryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void CashSumSummaryTest::testCashSum()
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

    membermanager::dao::MemberDao memberDao;
    QList<membermanager::Member> memberList = memberDao.findByDeleted(false);

    membermanager::CashSumSummary cashSum(memberList);

    QCOMPARE(cashSum.getTitle(), QString("Einahmen"));

    cashSum.setWriter(&writer);

    QDate date = QDate::currentDate();
    cashSum.handleHtmlText();

    QCOMPARE(writer.content, QString("Anzahl 2 * Beitrag 0 Gesamt = 0<br>Anzahl 1 * Beitrag 99 Gesamt = 99<br><br>Gesamt Spenden: 1.5<br><br>Gesamt Mitglieder: 3 Einahmen: 100.5<br><br>Gesamt Einzuege Mitglieder: 2 Einahmen: 100.5<br><br>Gesamt Saldo: -10<br>Stand: %1<br>").arg(date.toString()));
}

}

QTEST_MAIN(membermanagertest::CashSumSummaryTest)
#include "cashsumsummarytest.moc"
