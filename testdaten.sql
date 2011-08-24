
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





CREATE TABLE barkonto (
konto integer,
info character varying(100),
CONSTRAINT barkonto_konto_key UNIQUE (konto));






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
    VALUES (2,1025,15.00,1.00,0.00,date('2007-05-01'),'Beitragsaenderung');


INSERT INTO beitragstab(
            beitragstab_pkey, dorfmitglied_pkey, beitrag, spende, schulden,
            gueltigab, info)
    VALUES (1,1025,14.00,0.00,2.00,date('2006-05-01'),'Spende wird eingestellt');






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
  einzug boolean DEFAULT false,
  chaosnr smallint,
  eintrittsdatum date,
  info text);

INSERT INTO dorfmitglied (
            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,
            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)
    VALUES (1025,'false','James T','Kirk','Capt. Kirk','kirk@chaosdorf.de',
            'kirk@chaosdorf.de','kirk@chaosdorf.de','kirk',1,2193,date('2001-04-24'),'');

INSERT INTO dorfmitglied (
            dorfmitglied_pkey, deleted, vorname, name, nickname, chaosdorfadr,
            intern, ccc, shell, einzug, chaosnr, eintrittsdatum, info)
    VALUES (1026,'true','Spock','Spock','Spock','spock@chaosdorf.de',
            'spock@chaosdorf.de','spock@chaosdorf.de','spock',0,1234,date('2002-05-26'),'');





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
  erfasst boolean DEFAULT false);

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
        'ABSCHLUSS  Abrechnung 30.01.2006 siehe Anlage','false');





CREATE TABLE kommunikation (
                  kommunikation_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
                  dorfmitglied_pkey integer,
                  email character varying(50),
                  schluessel text,
                  publickey text);


INSERT INTO kommunikation (
                    kommunikation_pkey, dorfmitglied_pkey, email, schluessel, publickey)
            VALUES (1,1025,'fooo@baaar.xx','Keinen','');





CREATE TABLE konten (
                  kenz smallint,
                  info character(50),
                  CONSTRAINT konten_kenz_key UNIQUE (kenz));





CREATE TABLE kontodaten (
                  kontodaten_pkey INTEGER PRIMARY KEY AUTOINCREMENT, 
                  dorfmitglied_pkey integer,
                  kontonr bigint,
                  bank text,
                  blz integer);

INSERT INTO kontodaten (
        kontodaten_pkey, dorfmitglied_pkey, kontonr, bank, blz)
VALUES (1,1025,12234569,'sparstrumpf',9004010);






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
                     info)
            VALUES (2,1025,-15.00,date('2005-09-18'),'Mitgliedsbeitrag Sep','Automatische Monats Abbuchung');