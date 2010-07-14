/*
 * TestData.cpp
 *
 *  Created on: Mar 17, 2010
 *      Author: joerg
 */
#include <QtTest>
#include "TestData.h"

namespace ClubFrontendTest {

void TestData::execStatement(const QString & aSql) {
	QSqlQuery sqlQuery;
	if (!sqlQuery.exec(aSql)) {
		QCOMPARE(sqlQuery.lastError().text(), aSql);
	}
}

void TestData::createFakeAdressTable() {
	execStatement("DROP TABLE adresse");
	execStatement("CREATE TABLE adresse ("
			"  adresse_pkey serial NOT NULL,"
			"  dorfmitglied_pkey integer,"
			"  strasse text,  plz integer,"
			"  ort character varying(20),"
			"  CONSTRAINT adresse_pkey PRIMARY KEY (adresse_pkey)"
			")");
	execStatement("INSERT INTO adresse("
			"            adresse_pkey, dorfmitglied_pkey, strasse, plz, ort)"
			"    VALUES (1,1025,'Industriestr. 23',90546,'Bloedeldorf')");
}

void TestData::createFakeCashKontoTable() {
	execStatement("DROP TABLE barkonto");
	execStatement("CREATE TABLE barkonto ("
			"  konto integer,"
			"  info character varying(100),"
			"  CONSTRAINT barkonto_konto_key UNIQUE (konto))");
	/*
	 *
INSERT INTO barkonto(
            konto, info)
    VALUES (?, ?);


	 *
	 */
}

void TestData::createFakeContributionTable() {
	execStatement("DROP TABLE beitragstab");

	execStatement("CREATE TABLE beitragstab ("
			"  beitragstab_pkey serial NOT NULL,"
			"  dorfmitglied_pkey integer,"
			"  beitrag numeric(10,2),"
			"  spende numeric(10,2),"
			"  schulden numeric(10,2),"
			"  gueltigab date,"
			"  info text,"
			"  CONSTRAINT beitragstab_pkey PRIMARY KEY (beitragstab_pkey))");

	execStatement("INSERT INTO beitragstab("
			"            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,"
			"            gueltigab, info)"
			"    VALUES (1,1025,15.00,0.00,0.00,date('2007-05-01'),'Spende wird eingestellt')");
}

void TestData::createFakeMemberTable() {
	execStatement("DROP TABLE dorfmitglied");

	execStatement("CREATE TABLE dorfmitglied ("
			"  dorfmitglied_pkey serial NOT NULL,"
			"  deleted boolean DEFAULT false,"
			"  vorname character varying(20),"
			"  name character varying(20),"
			"  nickname character varying(20),"
			"  chaosdorfadr character varying(50),"
			"  intern character varying(50),"
			"  ccc character varying(50),"
			"  shell character varying(50),"
			"  einzug boolean DEFAULT false,"
			"  chaosnr smallint,"
			"  eintrittsdatum date,"
			"  info text,"
			"  CONSTRAINT dorfmitglied_pkey PRIMARY KEY (dorfmitglied_pkey))");

	execStatement("INSERT INTO dorfmitglied ("
			"            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,"
			"            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)"
			"    VALUES (1025,0,'James T','Kirk','Capt. Kirk','kirk@chaosdorf.de','kirk@chaosdorf.de','kirk@chaosdorf.de','kirk',1,2193,date('2001-04-24'),'')");

}

void TestData::createFakeKassaTable() {
	execStatement("DROP TABLE kasse");

	execStatement("CREATE TABLE kasse ("
			"  kasse_pkey serial NOT NULL,"
			"  deleted boolean DEFAULT false,"
			"  einlesedatum date,"
			"  einleseid integer,"
			"  auszug smallint,"
			"  zwshkenn60 character varying(10),"
			"  zwbudatum60 date,"
			"  zwischensaldo60 numeric(10,2),"
			"  zwshkenn62 character varying(10),"
			"  zwbudatum62 date,"
			"  zwischensaldo62 numeric(10,2),"
			"  valutadatum date,  buchungsdatum date,"
			"  shkenn character varying(10),"
			"  betrag numeric(10,2),"
			"  buschl smallint,"
			"  bankbuschl smallint,"
			"  fremdblz integer,"
			"  fremdktnr bigint,"
			"  fremdname text,"
			"  bezeichnung text,"
			"  barkonto integer,"
			"  konten integer,"
			"  dorfmitglied_pkey integer,"
			"  erfasst boolean DEFAULT false,"
			"  CONSTRAINT kasse_pkey PRIMARY KEY (kasse_pkey))");

	execStatement("INSERT INTO kasse ("
			"            kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,"
			"            zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,"
			"            valutadatum, buchungsdatum, shkenn, betrag, buschl, bankbuschl,"
			"            fremdblz, fremdktnr, fremdname, bezeichnung, barkonto, konten,"
			"            dorfmitglied_pkey, erfasst)"
			"    VALUES (1,0,'',1,1,'credit',date('2006-01-12'),3519.92,'credit',date('2006-01-23'),3423.02,date('2006-01-23'),date('2006-01-23'),'debit',34.90,5,"
			"37010050,5820507,'ISH NRW GMBH','LASTSCHRIFT  KDNR 4039458011 RGN 2495227',,,,0");

	execStatement("INSERT INTO kasse ("
			"            kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,"
			"            zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,"
			"            valutadatum, buchungsdatum, shkenn, betrag, buschl, bankbuschl,"
			"            fremdblz, fremdktnr, fremdname, bezeichnung, barkonto, konten,"
			"            dorfmitglied_pkey, erfasst)"
			"    VALUES (2,0,'',1,1,'credit',date('2006-01-12'),3519.92,'credit',date('2006-01-23'),3423.02,date('2006-01-23'),date('2006-01-23')"
			",'debit',62.00,,5,30050110,10012433,'STADTWERKE DUESSELDORF AG','LASTSCHRIFT  313001563692 VK020009330101 ABSCHLAG FAELLIG 23.01.06 FUERSTENWALL 232',,,,0)");

	execStatement("INSERT INTO kasse ("
			"            kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,"
			"            zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,"
			"            valutadatum, buchungsdatum, shkenn, betrag, buschl, bankbuschl,"
			"            fremdblz, fremdktnr, fremdname, bezeichnung, barkonto, konten,"
			"            dorfmitglied_pkey, erfasst)"
			"    VALUES (3,0,'',1,1,'credit',date('2006-01-23'),3423.02,'credit',date('2006-01-27'),3318.16,date('2006-01-27'),date('2006-01-27'),'debit',104.86,,820,30050110,21236716,'BOEHME, JOERG-CHRISTIAN',"
			"'UMBUCHUNG  ATELCO RECHNUNG VOM 12.1.06 LIEFERSCHNR. L4592165 DATUM 27.01.2006, 00.50 UHR 1.TAN 783978',,,,"
			"0)");

	execStatement("INSERT INTO kasse ("
			"            kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,"
			"            zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,"
			"            valutadatum, buchungsdatum, shkenn, betrag, buschl, bankbuschl,"
			"            fremdblz, fremdktnr, fremdname, bezeichnung, barkonto, konten,"
			"            dorfmitglied_pkey, erfasst)"
			"    VALUES (4,0,'',1,1,'credit',date('2006-01-27'),3318.16,'credit',date('2006-01-31'),"
			"3374.56,date('2006-02-01'),date('2006-01-31'),'debit',4.74,,805,30050110;0,'-',"
			"'ABSCHLUSS  Abrechnung 30.01.2006 siehe Anlage',,,,0)");
}

void TestData::createFakeRessourcenTable() {
	execStatement("DROP TABLE kommunikation");

	execStatement("CREATE TABLE kommunikation ("
			"  kommunikation_pkey serial NOT NULL,"
			"  dorfmitglied_pkey integer,"
			"  email character varying(50),"
			"  schluessel text,"
			"  publickey text,"
			"  CONSTRAINT kommunikation_pkey PRIMARY KEY (kommunikation_pkey))");

	execStatement("INSERT INTO kommunikation ("
			"            kommunikation_pkey, dorfmitglied_pkey, email, schluessel, publickey)"
			"    VALUES (1,1025,'fooo@baaar.xx','Keinen','')");

}

void TestData::createFakeKontenTable() {
	execStatement("DROP TABLE konten");

	execStatement("CREATE TABLE konten ("
			"  kenz smallint,"
			"  info character(50),"
			"  CONSTRAINT konten_kenz_key UNIQUE (kenz))");

	/*
	execStatement("INSERT INTO konten("
			"            kenz, info)"
			"    VALUES (?, ?)");
	*/
}

void TestData::createFakeBankTable() {
	execStatement("DROP TABLE kontodaten");

	execStatement("CREATE TABLE kontodaten ("
			"  kontodaten_pkey serial NOT NULL, "
			"  dorfmitglied_pkey integer,"
			"  kontonr bigint,"
			"  bank text,"
			"  blz integer,"
			"  CONSTRAINT kontodaten_pkey PRIMARY KEY (kontodaten_pkey))");

	execStatement("INSERT INTO kontodaten ("
			"            kontodaten_pkey, dorfmitglied_pkey, kontonr, bank, blz)"
			"    VALUES (1,1025,12234569,'sparstrumpf',9004010)");
}

void TestData::createFakeBalanceTable() {
	execStatement("DROP TABLE saldo");

	execStatement("CREATE TABLE saldo ("
			"  saldo_pkey serial NOT NULL,"
			"  dorfmitglied_pkey integer,"
			"  betrag numeric(10,2),"
			"  datum date,"
			"  bezeichnung text,"
			"  barkonto integer,"
			"  konten smallint,"
			"  kasse_pkey integer,"
			"  info text,"
			"  CONSTRAINT saldo_pkey PRIMARY KEY (saldo_pkey))");

	execStatement("INSERT INTO saldo ("
			"            saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, barkonto,"
			"            konten, kasse_pkey, info)"
			"    VALUES (1,1025,0.00,date('2005-08-11'),'Start Saldo',,,,'Start Saldo')");

	execStatement("INSERT INTO saldo ("
			"            saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, barkonto,"
			"            konten, kasse_pkey, info)"
			"    VALUES (90,1025,-15.00,date('2005-09-18'),'Mitgliedsbeitrag Sep',,,,'Automatische Monats Abbuchung')");

}

}
