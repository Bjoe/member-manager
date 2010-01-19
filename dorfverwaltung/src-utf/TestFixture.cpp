#include "TestFixture.hpp"

MemberDB::MemberDB() : database("sqlite3", "database=test.db")
{
    //database.verbose = true;
    database.create();

    MemberManagement::Member han(database);
    han.memberId = 1024;
    han.firstName = "Han";
    han.surename = "Solo";
    han.nickname = "Wokii";
    han.update();

    MemberManagement::Balance balance(database);
    balance.amount = 42;
    //balance.date = 0;
    balance.description = "Beitrag";
    balance.info = "Erster Beitrag";
    balance.update();

    han.cashAccount().link(balance);

    MemberManagement::Bank bank(database);
    bank.account = 123456789;
    bank.name = "SpassStrumpf";
    bank.code = 30012378;
    bank.update();

    han.bankAccount().link(bank);

    MemberManagement::Contribution contribution(database);
    contribution.fee = 15;
    contribution.donation = 0;
    //contribution.validFrom = 0;
    contribution.info = "Monatsbeitrag";
    contribution.update();

    han.money().link(contribution);

    MemberManagement::Ressourcen ressourcen(database);
    ressourcen.emailIntern = "foo@bar.tg";
    ressourcen.emailCCC = "bar@tralala.cy";
    ressourcen.shellAccount = "hansolo";
    ressourcen.update();

    han.internalRessourcen().link(ressourcen);

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    MemberManagement::Member kirk(database);
    kirk.firstName = "James Tiberius";
    kirk.surename = "Kirk";
    kirk.nickname = "Captain";
    kirk.update();

    MemberManagement::Member foo(database);
    foo.firstName = "James";
    foo.surename = "Bond";
    foo.deleted = true;
    foo.update();
}

MemberDB::~MemberDB()
{
    database.drop();
}
