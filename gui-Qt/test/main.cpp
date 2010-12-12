/*
Einige Todos:
- Source Code einheitlich Formatieren.
- Source Dokumentieren mit Doxygen.
- Einpaar Denglisch Datenbankfelder auf Englisch Refactoren.
- Refactor: QTableView den Model uebergeben.
- Einige unsinnige Datenbankfelder rauswerfen und Tabellen mergen. (Wird erst nach der ersten lauffaehigen Version umgesetzt)

Fehlende Features:
- Moeglichkeit Bankeinzug auszusetzen
- Gesamt Status uebersicht ueber den Verein: Gesamt Einahemen, Gesamt Mitglieder etc.
- Wie sollen die Umsaetze eingelesen werden? Per KMyMoney oder Aq API einbinden?
- Matchen der Umsaetze und auf die Mitgliedskonten buchen.
- DTAUS erstellen? Aq API?

*/
#include "MemberModelTest.h"
#include "KassaModelTest.h"
#include "SaldoModelTest.h"
#include "SaldoSumModelTest.h"
#include "MemberDetailModelTest.h"
#include "MemberFilterTest.h"
#include "MemberDialogTest.h"
#include "MainWindowTest.h"
#include "ConnectionDialogTest.h"
#include "SaldoDialogTest.h"
#include "SaldoSumDialogTest.h"
#include "ContributionDialogTest.h"
#include "ContributionModelTest.h"
#include "SummaryWindowTest.h"
#include "TestData.h"

#include <QtTest/QtTest>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("dorfverw.dat");
	if (!db.open())
	{
		qDebug() << db.lastError().text();
		return 1;
	}

	ClubFrontendTest::MemberModelTest sourceTest;
	QTest::qExec(&sourceTest);

	ClubFrontendTest::MemberFilterTest filterTest;
	QTest::qExec(&filterTest);

	ClubFrontendTest::MainWindowTest mainWindowTest;
	QTest::qExec(&mainWindowTest);

	ClubFrontendTest::MemberDialogTest dialogTest;
	QTest::qExec(&dialogTest);

	ClubFrontendTest::MemberDetailModelTest memberDialogTest;
	QTest::qExec(&memberDialogTest);

	ClubFrontendTest::ConnectionDialogTest connectionDialogTest;
	QTest::qExec(&connectionDialogTest);

	ClubFrontendTest::KassaModelTest kassaModelTest;
	QTest::qExec(&kassaModelTest);

	ClubFrontendTest::SaldoModelTest saldoModelTest;
	QTest::qExec(&saldoModelTest);

	ClubFrontendTest::SaldoDialogTest saldoDialogTest;
	QTest::qExec(&saldoDialogTest);

    ClubFrontendTest::ContributionModelTest contributionModelTest;
    QTest::qExec(&contributionModelTest);

    ClubFrontendTest::ContributionDialogTest contributionDialogTest;
    QTest::qExec(&contributionDialogTest);
    
    ClubFrontendTest::SaldoSumDialogTest saldoSumDialogTest;
    QTest::qExec(&saldoSumDialogTest);
    
    ClubFrontendTest::SaldoSumModelTest saldoSumModelTest;
    QTest::qExec(&saldoSumModelTest);
    
    ClubFrontendTest::SummaryWindowTest summaryTest;
    QTest::qExec(&summaryTest);

	return 0;
}
