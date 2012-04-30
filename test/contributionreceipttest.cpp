#include "contributionreceipttest.h"

#include "contributionreceipt.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "dao/databasestructure.h"
#include "summarywriter.h"
#include "member.h"
#include "dao/memberdao.h"

#include <QString>
#include <QSqlTableModel>

namespace membermanagertest
{

void ContributionReceiptTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionReceiptTest::testContribution()
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
    model.setTable(membermanager::dao::MemberTable::TABLENAME);
    model.select();

    membermanager::dao::MemberDao memberDao;
    QList<membermanager::Member> memberList = memberDao.findByDeleted(false);

    membermanager::ContributionReceipt contributionReceipt(memberList);

    QSKIP("Test macht noch nichts.", SkipAll);
    QCOMPARE(contributionReceipt.getTitle(), QString(""));

    contributionReceipt.setWriter(&writer);
    contributionReceipt.handleHtmlText();

    /// \todo fix test
    QCOMPARE(writer.content, QString(""));
}

}

QTEST_MAIN(membermanagertest::ContributionReceiptTest)
#include "contributionreceipttest.moc"
