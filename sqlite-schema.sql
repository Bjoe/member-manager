
CREATE TABLE adresse (
  adresse_pkey INTEGER PRIMARY KEY AUTOINCREMENT, 
  dorfmitglied_pkey integer, 
  strasse text,  
  plz integer, 
  ort character varying(20)
);

CREATE TABLE barkonto (
  konto integer,
  info character varying(100),
  CONSTRAINT barkonto_konto_key UNIQUE (konto)
);

CREATE TABLE beitragstab (
  beitragstab_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
  dorfmitglied_pkey integer,
  beitrag numeric(10,2),
  spende numeric(10,2),
  schulden numeric(10,2),
  gueltigab date,
  info text
);

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
  info text
);

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
  erfasst character varying(6) DEFAULT 'false'
);

CREATE TABLE kommunikation (
  kommunikation_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
  dorfmitglied_pkey integer,
  email character varying(50),
  schluessel text,
  publickey text
);

CREATE TABLE konten (
  kenz smallint,
  info character(50),
  CONSTRAINT konten_kenz_key UNIQUE (kenz)
);

CREATE TABLE kontodaten (
  kontodaten_pkey INTEGER PRIMARY KEY AUTOINCREMENT, 
  dorfmitglied_pkey integer,
  kontonr bigint,
  bank text,
  blz integer
);

CREATE TABLE saldo (
  saldo_pkey INTEGER PRIMARY KEY AUTOINCREMENT,
  dorfmitglied_pkey integer,
  betrag numeric(10,2),
  datum date,
  bezeichnung text,
  barkonto integer,
  konten smallint,
  kasse_pkey integer,
  info text
);
