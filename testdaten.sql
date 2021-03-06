DROP TABLE adresse;

CREATE TABLE adresse (
adresse_pkey INTEGER PRIMARY KEY AUTOINCREMENT, 
dorfmitglied_pkey integer, 
strasse text,  
plz integer, 
ort character varying(20));

INSERT INTO adresse(adresse_pkey, dorfmitglied_pkey, strasse, plz, ort)
VALUES (1,1024,'Industriestr. 24',90547,'Bloedeldorff');

INSERT INTO adresse(adresse_pkey, dorfmitglied_pkey, strasse, plz, ort)
VALUES (2,1025,'Industriestr. 23',90546,'Bloedeldorf');



DROP TABLE barkonto;

CREATE TABLE barkonto (
konto integer,
info character varying(100),
CONSTRAINT barkonto_konto_key UNIQUE (konto));




DROP TABLE beitragstab;

CREATE TABLE beitragstab (
  beitragstab_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
  dorfmitglied_pkey integer,
  beitrag numeric(10,2),
  spende numeric(10,2),
  schulden numeric(10,2),
  gueltigab date,
  info text);

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (4,1025,80.00,1.50,0.00,date('2006-03-10'),'Beitragsaenderung');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (6,1026,101.00,1.50,0.00,date('2009-03-10'),'Beitragsaenderung');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (9,1025,9.00,1.50,0.00,date('2006-02-1'),'Beitragsaenderung');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (10,1025,99.00,1.50,0.00,date('2009-03-10'),'Beitragsaenderung');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (5,1025,10.00,1.00,0.00,date('2007-10-23'),'Beitragsaenderung');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (3,1025,14.00,1.00,5.00,date('2007-03-10'),'Beitragsaenderung');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (2,1025,15.00,1.00,0.00,date('2007-05-01'),'Beitragsaenderung');


INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (1,1025,13.00,0.00,2.00,date('2006-05-01'),'Spende wird eingestellt');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (20,1030,80.00,0.00,0.00,date('2006-03-10'),'Beitragsaenderung');

INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (21,1033,80.00,1.50,0.00,date('2006-03-10'),'Beitragsaenderung');



DROP TABLE dorfmitglied;

CREATE TABLE dorfmitglied (
  dorfmitglied_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
  deleted character varying(6) DEFAULT 'false',
  vorname character varying(20),
  name character varying(20),
  nickname character varying(20),
  chaosdorfadr character varying(50),
  intern character varying(50),
  ccc character varying(50),
  shell character varying(50),
  einzug character varying(6) DEFAULT 'false',
  chaosnr smallint,
  eintrittsdatum date,
  info text);

INSERT INTO dorfmitglied (
            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,
            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)
    VALUES (1025,'false','James T','Kirk','Capt. Kirk','kirk@chaosdorf.de',
            'kirk@chaosdorf.de','kirk@chaosdorf.de','kirk','true',2193,date('2001-04-24'),'Captain of the ncc-1701');

INSERT INTO dorfmitglied (
            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,
            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)
    VALUES (1026,'true','Spock','Spock','Spock','spock@chaosdorf.de',
            'spock@chaosdorf.de','spock@chaosdorf.de','spock','false',1234,date('2002-05-26'),'Strange vulcanier');

INSERT INTO dorfmitglied (
            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,
            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)
    VALUES (1030,'false','Montgomery','Scott','Scotty','scott@chaosdorf.de',
            'scott@chaosdorf.de','scott@chaosdorf.de','scott','true',9876,date('2001-04-24'),'Ingenuer');

INSERT INTO dorfmitglied (
            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,
            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)
    VALUES (1031,'true','Spock','Spock','Spock','spock@chaosdorf.de',
            'spock@chaosdorf.de','spock@chaosdorf.de','spock','false',5678,date('2004-02-20'),'Strange vulcanier');

INSERT INTO dorfmitglied (
            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,
            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)
    VALUES (1033,'false','Leonard H.','McCoy','Dr. McCoy','mccoy@chaosdorf.de',
            'mccoy@chaosdorf.de','mccoy@chaosdorf.de','mccoy','false',8765,date('2003-010-15'),'Strange vulcanier');

DROP TABLE kasse;

CREATE TABLE kasse (
  kasse_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
  deleted character varying(6) DEFAULT 'false',
  einlesedatum date,
  einleseid integer,
  auszug smallint,
  zwshkenn60 character varying(10),
  zwbudatum60 date,
  zwischensaldo60 numeric(10,2),
  zwshkenn62 character varying(10),
  zwbudatum62 date,
  zwischensaldo62 numeric(10,2),
  valutadatum date,  buchungsdatum date,
  shkenn character varying(10),
  betrag numeric(10,2),
  buschl smallint,
  bankbuschl smallint,
  fremdblz integer,
  fremdktnr bigint,
  fremdname text,
  bezeichnung text,
  barkonto integer,
  konten integer,
  dorfmitglied_pkey integer,
  erfasst character varying(6) DEFAULT 'false');

INSERT INTO kasse (
            kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,
            zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,
            valutadatum, buchungsdatum, shkenn, betrag, bankbuschl,
            fremdblz, fremdktnr, fremdname, bezeichnung, erfasst)
     VALUES (1,'false','',1,1,'credit',date('2006-01-12'),519.92,'credit',date('2006-01-23'),423.02,date('2006-01-23'),date('2006-01-23'),'debit',34.90,5,
               58010050,7624502,'INTERNET GMBH','LASTSCHRIFT  KDNR 1234 RGN 987','false');

INSERT INTO kasse (
            kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,
            zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,
            valutadatum, buchungsdatum, shkenn, betrag, bankbuschl,
            fremdblz, fremdktnr, fremdname, bezeichnung, erfasst)
    VALUES (2,'true','',1,1,'credit',date('2006-01-12'),519.92,'credit',date('2006-01-23'),423.02,date('2006-01-23'),date('2006-01-23')
              ,'debit',62.00,5,10090110,30092423,'WERKE AG','LASTSCHRIFT  2837572829 VK98765432 ABSCHLAG FAELLIG 23.01.06 HANSAALLEE 123','false');


INSERT INTO kasse (
                    kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,
                    zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,
                    valutadatum, buchungsdatum, shkenn, betrag, bankbuschl,
                    fremdblz, fremdktnr, fremdname, bezeichnung, erfasst)
            VALUES (3,'false','',1,1,'credit',date('2006-01-23'),423.02,'credit',date('2006-01-27'),318.16,date('2006-01-27'),date('2006-01-27'),'debit',104.86,820,40020150,82938216,'MUELLER, MUSTERMANN',
        'UMBUCHUNG  SHOP RECHNUNG VOM 12.1.06 LIEFERSCHNR. L123456 DATUM 27.01.2006, 00.50 UHR 1.TAN 987654','false'
        );


INSERT INTO kasse (
                    kasse_pkey, deleted, einlesedatum, einleseid, auszug, zwshkenn60,
                    zwbudatum60, zwischensaldo60, zwshkenn62, zwbudatum62, zwischensaldo62,
                    valutadatum, buchungsdatum, shkenn, betrag, bankbuschl,
                    fremdblz, fremdktnr, fremdname, bezeichnung, erfasst)
            VALUES (4,'false','',1,1,'credit',date('2006-01-27'),318.16,'credit',date('2006-01-31'),
        374.56,date('2006-02-01'),date('2006-01-31'),'debit',4.74,805,80020510,0,'-',
        'ABSCHLUSS  Abrechnung 30.01.2006 siehe Anlage','true');

insert into kasse ("kasse_pkey", "deleted", "einlesedatum", "einleseid", "auszug", "zwshkenn60", "zwbudatum60", 
		    "zwischensaldo60", "zwshkenn62", "zwbudatum62", "zwischensaldo62", "valutadatum", "buchungsdatum", 
		    "shkenn", "betrag", "buschl", "bankbuschl", "fremdblz", "fremdktnr", "fremdname", "bezeichnung", "barkonto", 
		    "konten", "dorfmitglied_pkey", "erfasst") 
	  values ('5', 'false', '2012-12-30T17:41:13', 'abc123', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
          '2012-11-19T10:30:00', '2012-11-22T00:05:30', NULL, 81.5, 'DAUERAUFRTAG', '23', '80070011', '1234567890',
		  'Scott', 'Mitgliedsbeitrag', NULL, NULL, NULL, 'false');

insert into kasse ("kasse_pkey", "deleted", "einlesedatum", "einleseid", "auszug", "zwshkenn60", "zwbudatum60", 
		    "zwischensaldo60", "zwshkenn62", "zwbudatum62", "zwischensaldo62", "valutadatum", "buchungsdatum", 
		    "shkenn", "betrag", "buschl", "bankbuschl", "fremdblz", "fremdktnr", "fremdname", "bezeichnung", "barkonto", 
		    "konten", "dorfmitglied_pkey", "erfasst") 
	  values ('6', 'false', '2012-12-31T18:41:13', '123abc', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
          '2012-11-20T10:30:00', '2012-11-23T00:05:30', NULL, 100.5, 'DAUERAUFRTAG', '23', '90070024', '01194837',
		  'Kirk', 'mein Mitgliedsbeitrag', NULL, NULL, NULL, 'false');

insert into kasse ("kasse_pkey", "deleted", "einlesedatum", "einleseid", "auszug", "zwshkenn60", "zwbudatum60", 
		    "zwischensaldo60", "zwshkenn62", "zwbudatum62", "zwischensaldo62", "valutadatum", "buchungsdatum", 
		    "shkenn", "betrag", "buschl", "bankbuschl", "fremdblz", "fremdktnr", "fremdname", "bezeichnung", "barkonto", 
		    "konten", "dorfmitglied_pkey", "erfasst") 
	  values ('7', 'false', '2012-12-30T17:41:13', 'abc123', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
          '2012-11-19T10:30:00', '2012-11-22T00:05:30', NULL, 81.5, 'DAUERAUFRTAG', '23', '80070011', '1234567890',
		  'Scott', 'Mitgliedsbeitrag', NULL, NULL, NULL, 'false');

		  insert into kasse ("kasse_pkey", "deleted", "einlesedatum", "einleseid", "auszug", "zwshkenn60", "zwbudatum60", 
		    "zwischensaldo60", "zwshkenn62", "zwbudatum62", "zwischensaldo62", "valutadatum", "buchungsdatum", 
		    "shkenn", "betrag", "buschl", "bankbuschl", "fremdblz", "fremdktnr", "fremdname", "bezeichnung", "barkonto", 
		    "konten", "dorfmitglied_pkey", "erfasst") 
	  values ('8', 'false', '2012-12-30T17:41:13', 'abc123', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
          '2012-11-19T10:30:00', '2012-11-22T00:05:30', NULL, 81.5, 'DAUERAUFRTAG', '23', '80070011', '1234567890',
		  'McCoy', 'Mitgliedsbeitrag', NULL, NULL, '1033', 'true');


DROP TABLE kommunikation;

CREATE TABLE kommunikation (
                  kommunikation_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
                  dorfmitglied_pkey integer,
                  email character varying(50),
                  schluessel text,
                  publickey text);


INSERT INTO kommunikation (
                    kommunikation_pkey, dorfmitglied_pkey, email, schluessel, publickey)
            VALUES (1,1025,'fooo@baaar.xx','Keinen','');



DROP TABLE konten;

CREATE TABLE konten (
                  kenz smallint,
                  info character(50),
                  CONSTRAINT konten_kenz_key UNIQUE (kenz));



DROP TABLE kontodaten;

CREATE TABLE kontodaten (
                  kontodaten_pkey INTEGER PRIMARY KEY AUTOINCREMENT, 
                  dorfmitglied_pkey integer,
                  kontonr bigint,
                  bank text,
                  blz integer);

INSERT INTO kontodaten (
        kontodaten_pkey, dorfmitglied_pkey, kontonr, bank, blz)
VALUES (1,1025,12234569,'sparstrumpf',9004010);
INSERT INTO kontodaten (
        kontodaten_pkey, dorfmitglied_pkey, kontonr, bank, blz)
VALUES (2,1030,19779,'sparsocke',2940284);
INSERT INTO kontodaten (
        kontodaten_pkey, dorfmitglied_pkey, kontonr, bank, blz)
VALUES (3,1033,123629,'Kasse',90035410);
INSERT INTO kontodaten (
        kontodaten_pkey, dorfmitglied_pkey, kontonr, bank, blz)
VALUES (5,1026,345634569,'Stadt Socke',10835810);




DROP TABLE saldo;

CREATE TABLE saldo (
                  saldo_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
                  dorfmitglied_pkey integer,
                  betrag numeric(10,2),
                  datum date,
                  bezeichnung text,
                  barkonto integer,
                  konten smallint,
                  kasse_pkey integer,
                  info text);


INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info)
            VALUES (1,1025,0.00,date('2005-08-11'),'Start Saldo','Start Saldo');

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (2,1025,-15.00,date('2005-09-18'),'Mitgliedsbeitrag Sep','Automatische Monats Abbuchung', -11);


INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (3,1026,-15.00,date('2005-09-18'),'Mitgliedsbeitrag Sep','Automatische Monats Abbuchung', -11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (4,1026,15.00,date('2007-09-18'),'Mitgliedsbeitrag Sep','Automatische Monats Abbuchung', 11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (5,1025,-15.00,date('2007-03-08'),'Mitgliedsbeitrag Mar','Automatische Monats Abbuchung ', -11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (6,1025,-10.00,date('2007-03-08'),'Spende Mar','Automatische Monats Abbuchung ', -12);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (7,1025,15.00,date('2007-03-08'),'Mitgliedsbeitrag Mar','Automatische Monats Lastschrift', 11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (8,1025,10.00,date('2007-03-08'),'Spende Mar','Automatische Monats Lastschrift', 12);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (9,1025,-15.00,date('2007-04-05'),'Mitgliedsbeitrag Apr','Automatische Monats Abbuchung ', -11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (10,1025,-10.00,date('2007-04-05'),'Spende Apr','Automatische Monats Abbuchung ', 11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (11,1025,15.00,date('2007-04-05'),'Mitgliedsbeitrag Apr','Automatische Monats Lastschrift', 11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (12,1025,10.00,date('2007-04-05'),'Spende Apr','Automatische Monats Lastschrift', 12);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (13,1025,5.00,date('2012-01-09'),'Mitgliedsbeitrag Jan','Automatische Monats Lastschrift', 11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (14,1025,-8.00,date('2012-01-10'),'RÜCKBELASTUNG  1025 MITGLIEDSBEITRAG JAN VORGELEGT AM 10.01.12 NICHT BEZAHLT EU         5,00ENT- GELT FREMD00,00EIGEN03,00EU','Automatische Buchung', 11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (15,1025,-5.00,date('2012-02-08'),'Mitgliedsbeitrag Feb','Automatische Monats Abbuchung ', -11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (20,1025,5.00,date('2012-02-08'),'Mitgliedsbeitrag Feb','Automatische Monats Lastschrift', 11);

INSERT INTO saldo (
                    saldo_pkey, dorfmitglied_pkey, betrag, datum, bezeichnung, 
                     info, konten)
            VALUES (21,1025,8.00,date('2012-02-10'),'ZAHLUNGSEINGANG  1025 Ali Baba MITGLIEDSSCHULDEN','Automatische Buchung', 11);

