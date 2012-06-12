#include "memberdetailviewtest.h"

#include "gui/memberdetailview.h"

#include "ui_mainwindow.h"
#include "member.h"
#include "dao/databasestructure.h"
#include "testconfig.h"
#include "triggerthread.h"
#include "gui/dialogbuttonboxhandler.h"

#include <QtCore>
#include <QtSql>
#include <QtGui>

namespace membermanagertest
{
namespace gui
{

MemberDetailViewTest::MemberDetailViewTest() :
    database(DATABASEDRIVER)
{}

void MemberDetailViewTest::initTestCase()
{
    database.open(DATABASE);
}

void MemberDetailViewTest::initTest()
{
    database.read(SQLTESTFILE);
}

void MemberDetailViewTest::testNewMember()
{
    membermanager::gui::MemberDetailView detailView(true);
    QTableView *view = detailView.findChild<QTableView *> ("tableView");
    QAbstractItemModel *model = view->model();
    QCOMPARE(model->rowCount(), 2);

    QPushButton *pushButton = detailView.findChild<QPushButton *> ("pushButton");
    QTest::mouseClick(pushButton, Qt::LeftButton);
    QPushButton *saveButton = detailView.findChild<QPushButton *> ("saveButton");
    QTest::mouseClick(saveButton, Qt::LeftButton);

    QCOMPARE(model->rowCount(), 3);
}


void MemberDetailViewTest::testSelectedMember()
{
    membermanager::gui::MemberDetailView detailView(false);

    QTableView *view = detailView.findChild<QTableView *> ("tableView");
    QItemSelectionModel *selectionModel = view->selectionModel();
    QAbstractItemModel *model = view->model();
    QModelIndex index = model->index(0, 3);
    QItemSelection selection(index, index);
    selectionModel->select(selection, QItemSelectionModel::Select);

    QLabel *memberId = detailView.findChild<QLabel *>("memberId");
    QCOMPARE(memberId->text() , QString("1025"));
}


void MemberDetailViewTest::testMemberView()
{
    membermanager::gui::MemberDetailView detailView(false);

    QTableView *view = detailView.findChild<QTableView *> ("tableView");

    QModelIndex index = view->indexAt(QPoint(0, 0));
    QVERIFY(index.isValid());
    const QAbstractItemModel *model = index.model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 3);
    QVariant value = model->data(index);
    QCOMPARE(value.toInt(), 1025);

    // \todo QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // \todo QModelIndex index = view->currentIndex();
}

void MemberDetailViewTest::testDeletedMemberView()
{
    membermanager::gui::MemberDetailView detailView(true);

    QTableView *view = detailView.findChild<QTableView *> ("tableView");

    QModelIndex index = view->indexAt(QPoint(0, 0));
    QVERIFY(index.isValid());
    const QAbstractItemModel *model = index.model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 2);
    QVariant value = model->data(index);
    QCOMPARE(value.toInt(), 1026);

    // \todo QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // \todo QModelIndex index = view->currentIndex();
}

void MemberDetailViewTest::testShowMember()
{
    membermanager::gui::MemberDetailView detailView(false);

    detailView.showMember(1025);

    QLabel *memberId = detailView.findChild<QLabel *> ("memberId");
    QLineEdit *firstName = detailView.findChild<QLineEdit *> ("firstName");
    QLineEdit *memberName = detailView.findChild<QLineEdit *> ("memberName");
    QLineEdit *nickname = detailView.findChild<QLineEdit *> ("nickname");
    QLineEdit *reference = detailView.findChild<QLineEdit *> ("reference");
    QPlainTextEdit *info = detailView.findChild<QPlainTextEdit *> ("info");
    QLineEdit *city = detailView.findChild<QLineEdit *> ("city");
    QLineEdit *street = detailView.findChild<QLineEdit *> ("street");
    QLineEdit *zipcode = detailView.findChild<QLineEdit *> ("zipcode");
    QLineEdit *email = detailView.findChild<QLineEdit *> ("email");
    QDateEdit *entryDate = detailView.findChild<QDateEdit *> ("entryDate");
    QLineEdit *contributionInfo = detailView.findChild<QLineEdit *> ("contributionInfo");
    QLineEdit *donation = detailView.findChild<QLineEdit *> ("donation");
    QLineEdit *fee = detailView.findChild<QLineEdit *> ("fee");
    QDateEdit *validFrom = detailView.findChild<QDateEdit *> ("validFrom");
    QLineEdit *account = detailView.findChild<QLineEdit *> ("account");
    QLineEdit *code = detailView.findChild<QLineEdit *> ("code");
    QLineEdit *bankName = detailView.findChild<QLineEdit *> ("bankName");
    QCheckBox *collection = detailView.findChild<QCheckBox *> ("collection");
    QCheckBox *deleted = detailView.findChild<QCheckBox *> ("deleted");

    QCOMPARE(memberId->text(), QString("1025"));
    QCOMPARE(firstName->text(), QString("James T"));
    QCOMPARE(memberName->text(), QString("Kirk"));
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));
    QCOMPARE(reference->text(), QString("2193"));
    QCOMPARE(info->toPlainText(), QString("Captain of the ncc-1701"));
    QCOMPARE(city->text(), QString("Bloedeldorf"));
    QCOMPARE(street->text(), QString("Industriestr. 23"));
    QCOMPARE(zipcode->text(), QString("90546"));
    QCOMPARE(email->text(), QString("fooo@baaar.xx"));
    QCOMPARE(entryDate->text(), QString("24.04.01"));
    QCOMPARE(contributionInfo->text(), QString("Beitragsaenderung"));
    QCOMPARE(donation->text(), QString("1.5"));
    QCOMPARE(fee->text(), QString("99"));
    QCOMPARE(validFrom->text(), QString("10.03.09"));
    QCOMPARE(account->text(), QString("12234569"));
    QCOMPARE(code->text(), QString("9004010"));
    QCOMPARE(bankName->text(), QString("sparstrumpf"));
    QVERIFY(collection->isChecked() == true);
    QVERIFY(deleted->isChecked() == false);
}

void MemberDetailViewTest::testChangeMember()
{
    membermanager::gui::MemberDetailView detailView(false);

    detailView.showMember(1025);

    QLabel *id = detailView.findChild<QLabel *> ("memberId");
    QLineEdit *firstName = detailView.findChild<QLineEdit *> ("firstName");
    QLineEdit *memberName = detailView.findChild<QLineEdit *> ("memberName");
    QLineEdit *nickname = detailView.findChild<QLineEdit *> ("nickname");
    QLineEdit *reference = detailView.findChild<QLineEdit *> ("reference");
    QPlainTextEdit *info = detailView.findChild<QPlainTextEdit *> ("info");
    QLineEdit *city = detailView.findChild<QLineEdit *> ("city");
    QLineEdit *street = detailView.findChild<QLineEdit *> ("street");
    QLineEdit *zipcode = detailView.findChild<QLineEdit *> ("zipcode");
    QLineEdit *email = detailView.findChild<QLineEdit *> ("email");
    QDateEdit *entryDate = detailView.findChild<QDateEdit *> ("entryDate");
    QLineEdit *contributionInfo = detailView.findChild<QLineEdit *> ("contributionInfo");
    QLineEdit *donation = detailView.findChild<QLineEdit *> ("donation");
    QLineEdit *fee = detailView.findChild<QLineEdit *> ("fee");
    QDateEdit *validFrom = detailView.findChild<QDateEdit *> ("validFrom");
    QLineEdit *account = detailView.findChild<QLineEdit *> ("account");
    QLineEdit *code = detailView.findChild<QLineEdit *> ("code");
    QLineEdit *bankName = detailView.findChild<QLineEdit *> ("bankName");
    QCheckBox *collection = detailView.findChild<QCheckBox *> ("collection");
    QCheckBox *deleted = detailView.findChild<QCheckBox *> ("deleted");

    QCOMPARE(id->text(), QString("1025"));
    QCOMPARE(firstName->text(), QString("James T"));
    QCOMPARE(memberName->text(), QString("Kirk"));
    QCOMPARE(reference->text(), QString("2193"));
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));
    QCOMPARE(info->toPlainText(), QString("Captain of the ncc-1701"));
    QCOMPARE(city->text(), QString("Bloedeldorf"));
    QCOMPARE(street->text(), QString("Industriestr. 23"));
    QCOMPARE(zipcode->text(), QString("90546"));
    QCOMPARE(email->text(), QString("fooo@baaar.xx"));
    QCOMPARE(entryDate->text(), QString("24.04.01"));
    QCOMPARE(contributionInfo->text(), QString("Beitragsaenderung"));
    QCOMPARE(donation->text(), QString("1.5"));
    QCOMPARE(fee->text(), QString("99"));
    QCOMPARE(validFrom->text(), QString("10.03.09"));
    QCOMPARE(account->text(), QString("12234569"));
    QCOMPARE(code->text(), QString("9004010"));
    QCOMPARE(bankName->text(), QString("sparstrumpf"));
    QVERIFY(collection->isChecked() == true);
    QVERIFY(deleted->isChecked() == false);

    memberName->clear();
    QTest::keyClicks(memberName, "Archer");
    firstName->clear();
    QTest::keyClicks(firstName, "Jonathan");
    nickname->clear();
    QTest::keyClicks(nickname, "Captain");
    reference->clear();
    QTest::keyClicks(reference, "2323");

    street->clear();
    QTest::keyClicks(street, "NCC-1701");
    city->clear();
    QTest::keyClicks(city, "Dtown");
    zipcode->clear();
    QTest::keyClicks(zipcode, "98765");

    email->clear();
    QTest::keyClicks(email, "foo@bar.tx");
    QTest::keyClicks(entryDate, "15.07.06");

    fee->clear();
    QTest::keyClicks(fee, "105");
    donation->clear();
    QTest::keyClicks(donation, "100");
    contributionInfo->clear();
    QTest::keyClicks(contributionInfo, "Kohle");

    account->clear();
    QTest::keyClicks(account, "123456789");
    bankName->clear();
    QTest::keyClicks(bankName, "Galaxy");
    code->clear();
    QTest::keyClicks(code, "98765432");

    info->clear();
    QTest::keyClicks(info, "Lalala");

    collection->setChecked(false);
    deleted->setChecked(true);

    detailView.saveMember();

/*    QCOMPARE(firstName->text(), QString("Jonathan"));
    QCOMPARE(memberName->text(), QString("Archer"));
    QCOMPARE(nickname->text(), QString("Captain"));
    QCOMPARE(reference->text(), QString("2323"));
    QCOMPARE(id->text(), QString("1025"));
    QCOMPARE(city->text(), QString("Dtown"));
    QCOMPARE(street->text(), QString("NCC-1701"));
    QCOMPARE(zipcode->text(), QString("98765"));
    QCOMPARE(email->text(), QString("foo@bar.tx"));
    //QCOMPARE(entryDate->text(), QString("15.07.06"));
    QCOMPARE(contributionInfo->text(), QString("Kohle"));
    QCOMPARE(donation->text(), QString("100"));
    QCOMPARE(fee->text(), QString("105"));
    QCOMPARE(account->text(), QString("123456789"));
    QCOMPARE(bankName->text(), QString("Galaxy"));
    QCOMPARE(code->text(), QString("98765432"));
    QCOMPARE(info->toPlainText(), QString("Lalala"));
    QVERIFY(collection->isChecked() == false);
    QVERIFY(deleted->isChecked() == true);
*/
    using membermanager::dao::MemberTable;
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(1025);

    using membermanager::dao::MemberTable;
    QSqlQuery query;
    query.exec("select * from " + MemberTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
    QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
    QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));
    QCOMPARE(query.value(MemberTable::FOO_ChaosNr).toString(), QString("2323"));
    QVERIFY(query.value(MemberTable::Deleted).toBool() == true);
    QVERIFY(query.value(MemberTable::FOO_Einzug).toBool() == false);

    using membermanager::dao::AddressTable;
    query.exec("select * from " + AddressTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
    QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
    QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

    using membermanager::dao::ContributionTable;
    query.exec("select * from " + ContributionTable::TABLENAME + whereClause +
               " order by " + ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " desc");
    query.next();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 105);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 100);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("Kohle"));

    using membermanager::dao::BankAccountTable;
    query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
    QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
    QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

    using membermanager::dao::RessourcenTable;
    query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

void MemberDetailViewTest::testChangeMemberWithNewContribution()
{
    membermanager::gui::MemberDetailView detailView(false);

    detailView.showMember(1025);

    QLabel *id = detailView.findChild<QLabel *> ("memberId");
    QLineEdit *firstName = detailView.findChild<QLineEdit *> ("firstName");
    QLineEdit *memberName = detailView.findChild<QLineEdit *> ("memberName");
    QLineEdit *nickname = detailView.findChild<QLineEdit *> ("nickname");
    QLineEdit *reference = detailView.findChild<QLineEdit *> ("reference");
    QPlainTextEdit *info = detailView.findChild<QPlainTextEdit *> ("info");
    QLineEdit *city = detailView.findChild<QLineEdit *> ("city");
    QLineEdit *street = detailView.findChild<QLineEdit *> ("street");
    QLineEdit *zipcode = detailView.findChild<QLineEdit *> ("zipcode");
    QLineEdit *email = detailView.findChild<QLineEdit *> ("email");
    QDateEdit *entryDate = detailView.findChild<QDateEdit *> ("entryDate");
    QLineEdit *contributionInfo = detailView.findChild<QLineEdit *> ("contributionInfo");
    QLineEdit *donation = detailView.findChild<QLineEdit *> ("donation");
    QLineEdit *fee = detailView.findChild<QLineEdit *> ("fee");
    QDateEdit *validFrom = detailView.findChild<QDateEdit *> ("validFrom");
    QLineEdit *account = detailView.findChild<QLineEdit *> ("account");
    QLineEdit *code = detailView.findChild<QLineEdit *> ("code");
    QLineEdit *bankName = detailView.findChild<QLineEdit *> ("bankName");
    QCheckBox *collection = detailView.findChild<QCheckBox *> ("collection");
    QCheckBox *deleted = detailView.findChild<QCheckBox *> ("deleted");

    QCOMPARE(id->text(), QString("1025"));
    QCOMPARE(firstName->text(), QString("James T"));
    QCOMPARE(memberName->text(), QString("Kirk"));
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));
    QCOMPARE(info->toPlainText(), QString("Captain of the ncc-1701"));
    QCOMPARE(city->text(), QString("Bloedeldorf"));
    QCOMPARE(street->text(), QString("Industriestr. 23"));
    QCOMPARE(zipcode->text(), QString("90546"));
    QCOMPARE(email->text(), QString("fooo@baaar.xx"));
    QCOMPARE(entryDate->text(), QString("24.04.01"));
    QCOMPARE(contributionInfo->text(), QString("Beitragsaenderung"));
    QCOMPARE(donation->text(), QString("1.5"));
    QCOMPARE(fee->text(), QString("99"));
    QCOMPARE(validFrom->text(), QString("10.03.09"));
    QCOMPARE(account->text(), QString("12234569"));
    QCOMPARE(code->text(), QString("9004010"));
    QCOMPARE(bankName->text(), QString("sparstrumpf"));

    detailView.newFee();

    QCOMPARE(validFrom->date(), QDate::currentDate());
    QCOMPARE(donation->text(), QString("0"));
    QCOMPARE(fee->text(), QString("15"));
    QCOMPARE(contributionInfo->text(), QString("Beitragsänderung"));

    memberName->clear();
    QTest::keyClicks(memberName, "Archer");
    firstName->clear();
    QTest::keyClicks(firstName, "Jonathan");
    nickname->clear();
    QTest::keyClicks(nickname, "Captain");

    street->clear();
    QTest::keyClicks(street, "NCC-1701");
    city->clear();
    QTest::keyClicks(city, "Dtown");
    zipcode->clear();
    QTest::keyClicks(zipcode, "98765");

    email->clear();
    QTest::keyClicks(email, "foo@bar.tx");
    QTest::keyClicks(entryDate, "15.07.06");

    account->clear();
    QTest::keyClicks(account, "123456789");
    bankName->clear();
    QTest::keyClicks(bankName, "Galaxy");
    code->clear();
    QTest::keyClicks(code, "98765432");

    info->clear();
    QTest::keyClicks(info, "Lalala");

    detailView.saveMember();

    QCOMPARE(firstName->text(), QString("Jonathan"));
    QCOMPARE(memberName->text(), QString("Archer"));
    QCOMPARE(nickname->text(), QString("Captain"));
    QCOMPARE(id->text(), QString("1025"));
    QCOMPARE(city->text(), QString("Dtown"));
    QCOMPARE(street->text(), QString("NCC-1701"));
    QCOMPARE(zipcode->text(), QString("98765"));
    QCOMPARE(email->text(), QString("foo@bar.tx"));
    //QCOMPARE(entryDate->text(), QString("15.07.06"));
    QCOMPARE(contributionInfo->text(), QString("Beitragsänderung"));
    QCOMPARE(donation->text(), QString("0"));
    QCOMPARE(fee->text(), QString("15"));
    QCOMPARE(account->text(), QString("123456789"));
    QCOMPARE(bankName->text(), QString("Galaxy"));
    QCOMPARE(code->text(), QString("98765432"));
    QCOMPARE(info->toPlainText(), QString("Lalala"));

    using membermanager::dao::MemberTable;
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(1025);

    using membermanager::dao::MemberTable;
    QSqlQuery query;
    query.exec("select * from " + MemberTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
    QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
    QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));

    using membermanager::dao::AddressTable;
    query.exec("select * from " + AddressTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
    QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
    QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

    using membermanager::dao::ContributionTable;
    query.exec("select * from " + ContributionTable::TABLENAME + whereClause +
               " order by " + ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " desc");
    query.next();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 15);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 0);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("Beitragsänderung"));

    using membermanager::dao::BankAccountTable;
    query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
    QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
    QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

    using membermanager::dao::RessourcenTable;
    query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

void MemberDetailViewTest::testShowSaldoDialog()
{
    membermanager::gui::MemberDetailView memberDetailView(false);

    memberDetailView.showMember(1025);

    qttestutil::gui::DialogButtonBoxHandler handler(QDialogButtonBox::Close);
    qttestutil::TriggerThread thread(this, &handler);
    connect(&thread, SIGNAL(triggered()), &memberDetailView, SLOT(showSaldoDialog()));
    thread.syncStart();
}

void MemberDetailViewTest::testShowContributionDialog()
{
    membermanager::gui::MemberDetailView memberDetailView(false);

    memberDetailView.showMember(1025);

    qttestutil::gui::DialogButtonBoxHandler handler(QDialogButtonBox::Close);
    qttestutil::TriggerThread thread(this, &handler);
    connect(&thread, SIGNAL(triggered()), &memberDetailView, SLOT(showContributionDialog()));
    thread.syncStart();
}

void MemberDetailViewTest::testShowContributionReceiptDialog()
{
    membermanager::gui::MemberDetailView memberDetailView(false);

    memberDetailView.showMember(1025);

    qttestutil::gui::DialogButtonBoxHandler handler(QDialogButtonBox::Close);
    qttestutil::TriggerThread thread(this, &handler);
    connect(&thread, SIGNAL(triggered()), &memberDetailView, SLOT(showContributionReceiptDialog()));
    thread.syncStart();
}

void MemberDetailViewTest::handle()
{
    bool next = true;
    do {
        QWidget *widget = QApplication::activeWindow();
        if (widget) {
            QLabel *memberId = widget->findChild<QLabel *> ("memberId");
            id = memberId->text();
            QDialogButtonBox *buttonBox = widget->findChild<QDialogButtonBox *> (
                                              "buttonBox");
            QPushButton *button = buttonBox->button(QDialogButtonBox::Close);
            button->click();
            next = false;
        }
    } while (next);
}

}
}

QTEST_MAIN(membermanagertest::gui::MemberDetailViewTest)
#include "memberdetailviewtest.moc"
