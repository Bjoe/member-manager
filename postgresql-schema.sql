--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: adresse; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE adresse (
    adresse_pkey integer NOT NULL,
    dorfmitglied_pkey integer,
    strasse text,
    plz integer,
    ort character varying(20)
);


--
-- Name: adresse_adresse_pkey_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE adresse_adresse_pkey_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: adresse_adresse_pkey_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE adresse_adresse_pkey_seq OWNED BY adresse.adresse_pkey;


--
-- Name: barkonto; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE barkonto (
    konto integer,
    info character varying(100)
);


--
-- Name: beitragstab; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE beitragstab (
    beitragstab_pkey integer NOT NULL,
    dorfmitglied_pkey integer,
    beitrag numeric(10,2),
    spende numeric(10,2),
    schulden numeric(10,2),
    gueltigab date,
    info text
);


--
-- Name: beitragstab_beitragstab_pkey_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE beitragstab_beitragstab_pkey_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: beitragstab_beitragstab_pkey_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE beitragstab_beitragstab_pkey_seq OWNED BY beitragstab.beitragstab_pkey;


--
-- Name: dorfmitglied; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE dorfmitglied (
    dorfmitglied_pkey integer NOT NULL,
    deleted boolean DEFAULT false,
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
    info text
);


--
-- Name: dorfmitglied_dorfmitglied_pkey_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE dorfmitglied_dorfmitglied_pkey_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: dorfmitglied_dorfmitglied_pkey_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE dorfmitglied_dorfmitglied_pkey_seq OWNED BY dorfmitglied.dorfmitglied_pkey;


--
-- Name: kasse; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE kasse (
    kasse_pkey integer NOT NULL,
    deleted boolean DEFAULT false,
    einlesedatum date,
    einleseid integer,
    auszug smallint,
    zwshkenn60 character varying(10),
    zwbudatum60 date,
    zwischensaldo60 numeric(10,2),
    zwshkenn62 character varying(10),
    zwbudatum62 date,
    zwischensaldo62 numeric(10,2),
    valutadatum date,
    buchungsdatum date,
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
    erfasst boolean DEFAULT false
);


--
-- Name: kasse_kasse_pkey_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE kasse_kasse_pkey_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: kasse_kasse_pkey_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE kasse_kasse_pkey_seq OWNED BY kasse.kasse_pkey;


--
-- Name: kommunikation; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE kommunikation (
    kommunikation_pkey integer NOT NULL,
    dorfmitglied_pkey integer,
    email character varying(50),
    schluessel text,
    publickey text
);


--
-- Name: kommunikation_kommunikation_pkey_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE kommunikation_kommunikation_pkey_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: kommunikation_kommunikation_pkey_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE kommunikation_kommunikation_pkey_seq OWNED BY kommunikation.kommunikation_pkey;


--
-- Name: konten; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE konten (
    kenz smallint,
    info character(50)
);


--
-- Name: kontodaten; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE kontodaten (
    kontodaten_pkey integer NOT NULL,
    dorfmitglied_pkey integer,
    kontonr bigint,
    bank text,
    blz integer
);


--
-- Name: kontodaten_kontodaten_pkey_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE kontodaten_kontodaten_pkey_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: kontodaten_kontodaten_pkey_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE kontodaten_kontodaten_pkey_seq OWNED BY kontodaten.kontodaten_pkey;


--
-- Name: nexttrxid_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE nexttrxid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: saldo; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE saldo (
    saldo_pkey integer NOT NULL,
    dorfmitglied_pkey integer,
    betrag numeric(10,2),
    datum date,
    bezeichnung text,
    barkonto integer,
    konten smallint,
    kasse_pkey integer,
    info text
);


--
-- Name: saldo_saldo_pkey_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE saldo_saldo_pkey_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: saldo_saldo_pkey_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE saldo_saldo_pkey_seq OWNED BY saldo.saldo_pkey;


--
-- Name: adresse_pkey; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY adresse ALTER COLUMN adresse_pkey SET DEFAULT nextval('adresse_adresse_pkey_seq'::regclass);


--
-- Name: beitragstab_pkey; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY beitragstab ALTER COLUMN beitragstab_pkey SET DEFAULT nextval('beitragstab_beitragstab_pkey_seq'::regclass);


--
-- Name: dorfmitglied_pkey; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY dorfmitglied ALTER COLUMN dorfmitglied_pkey SET DEFAULT nextval('dorfmitglied_dorfmitglied_pkey_seq'::regclass);


--
-- Name: kasse_pkey; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY kasse ALTER COLUMN kasse_pkey SET DEFAULT nextval('kasse_kasse_pkey_seq'::regclass);


--
-- Name: kommunikation_pkey; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY kommunikation ALTER COLUMN kommunikation_pkey SET DEFAULT nextval('kommunikation_kommunikation_pkey_seq'::regclass);


--
-- Name: kontodaten_pkey; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY kontodaten ALTER COLUMN kontodaten_pkey SET DEFAULT nextval('kontodaten_kontodaten_pkey_seq'::regclass);


--
-- Name: saldo_pkey; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY saldo ALTER COLUMN saldo_pkey SET DEFAULT nextval('saldo_saldo_pkey_seq'::regclass);


--
-- Name: adresse_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY adresse
    ADD CONSTRAINT adresse_pkey PRIMARY KEY (adresse_pkey);


--
-- Name: barkonto_konto_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY barkonto
    ADD CONSTRAINT barkonto_konto_key UNIQUE (konto);


--
-- Name: beitragstab_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY beitragstab
    ADD CONSTRAINT beitragstab_pkey PRIMARY KEY (beitragstab_pkey);


--
-- Name: dorfmitglied_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY dorfmitglied
    ADD CONSTRAINT dorfmitglied_pkey PRIMARY KEY (dorfmitglied_pkey);


--
-- Name: kasse_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY kasse
    ADD CONSTRAINT kasse_pkey PRIMARY KEY (kasse_pkey);


--
-- Name: kommunikation_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY kommunikation
    ADD CONSTRAINT kommunikation_pkey PRIMARY KEY (kommunikation_pkey);


--
-- Name: konten_kenz_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY konten
    ADD CONSTRAINT konten_kenz_key UNIQUE (kenz);


--
-- Name: kontodaten_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY kontodaten
    ADD CONSTRAINT kontodaten_pkey PRIMARY KEY (kontodaten_pkey);


--
-- Name: saldo_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY saldo
    ADD CONSTRAINT saldo_pkey PRIMARY KEY (saldo_pkey);


--
-- PostgreSQL database dump complete
--

