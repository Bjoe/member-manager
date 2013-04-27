#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Datenbank.pm,v 1.8 2006/06/06 20:08:07 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Datenbank.pm,v $
# Revision 1.8  2006/06/06 20:08:07  jboehme
# - BUGFIX: Hostname vom Datenbankserver wird als Verbindungserver erkannt
# - Aenderung: Loeschen von Mitgliedern wurde entfernt
#
# Revision 1.6  2005/09/11 21:39:50  jboehme
# - Erweiterung: Die Beitragstabelle wird mit der Spalte "Schulden" erweitert.
#
# Revision 1.5  2005/08/11 19:12:10  jboehme
# - Abaendern des package/Klassen Namens
# - Abaender der Klassen aufrufe nach package/Klassen Namens Aenderung
#
# Revision 1.4  2005/08/10 11:05:54  jboehme
# - Source Code nach Emacs Umstellung umformatiert
#
# Revision 1.3  2005/03/23 22:08:52  jboehme
# - Aenderung im Programm dorfverw: "Eingabe"-Routinen werden in einem extra Modul
#   ausgelagert
# - Neu: Die "Anmeldeparameter" koennen in der Shell enviroment/Umgebung gesetzt werden
# - Aenderungen div. Programmausgaben.
# - BUGFIX: Ueberpruefen ob Uebergabeparamter an den Klassen/Objekten ueber die Methoden
#   NULL bzw. gesetzt sind.
# - BUGFIX: Das Aenderungsflag in den Klassen/Objekten wird auch bei "nicht vorhanden Daten
#   im Objekt" gesetzt.
# - Neue Methoden "set-" in den Klassen hinzugefuegt.
# - Aenderung in den "update" Methoden der Klasse Datenbank: die SET Uebergabeparameter
#   werden in einem Array uebergeben.
#
# Revision 1.2  2005/02/27 11:01:46  jboehme
# Programmcode Aenderung/Umstrukturierung: Prozedual -> OOP und Modulen
# Datenbankfelder hinzugefuegt und Datenbank erweitert
# Zeite BETA Version
#
# Revision 1.1  2004/11/14 21:13:46  jboehme
# Initialrelease
# - Erster Entwurf des Objekts
#
#

package Verein::Datenbank;

use strict;
use DBI;
use Date::Manip;

use Carp;
sub whowasi  { (caller(1))[3] . "()" }

sub new # ( User, Passwort, [hostname], [port], [dbname] )
{
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $user = shift;
    my $passw = shift;
	my $hostname = shift;
	my $port = shift;
	$port = $port ? $port : "5432" if($hostname);
	my $dbname = shift;
    $dbname = "chaosdorf" unless($dbname);

	my $dsn = $hostname ? "database=$dbname;host=$hostname;port=$port" : "dbname=$dbname";
    my $dbh = DBI->connect("dbi:Pg:$dsn", $user, $passw,
						   { RaiseError => 1,
							 PrintError => 0,
							 AutoCommit => 0}
						  );

    croak "@{[&whowasi]}: Kann auf Datenbank nicht connecten: ".$DBI::errstr unless($dbh);

    my $q_user = $dbh->quote($user);

    my $self = { user => $q_user,
				 dbh => \$dbh,
				 errorcode => 0,
			   };

    bless ($self, $class);

    return $self;
}

sub debug
{
    my $self = shift;
    my $debuglevel = shift;

    ${$self->{dbh}}->trace($debuglevel-1); # Debug
    return;
}

sub isError # ()
{
    my $self = shift;
    return $self->{errorcode};
}

sub getError # ()
{
    my $self = shift;
    $self->{errorcode} = 0;
    return $self->{error};
}

sub commit # ()
{
    my $self = shift;

    ${$self->{dbh}}->commit() or
	   eval { $self->{errorcode} = 1;
			  $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		  };

    return;
}

sub rollback # ()
{
    my $self = shift;

    ${$self->{dbh}}->rollback() or
	   eval { $self->{errorcode} = 1;
			  $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		  };

    return;
}

sub lastMitgliedsnr # ()
{
    my $self = shift;

    my $sqlStatement = "select last_value from dorfmitglied_dorfmitglied_pkey_seq";

    my $x = 0;
    my @erg;
    eval {
		@erg = ${$self->{dbh}}->selectrow_array($sqlStatement);
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return $erg[0];
}

sub searchMitglNr # ( mitgliedsObjekt, Bezeichnung)
{
    my $self = shift;
    my $mitgliedsObj = shift;

	my $sqlWhere = "WHERE deleted = false and dorfmitglied_pkey = ". ${$self->{dbh}}->quote($_[0]) ."";
    my $sqlSelect = "SELECT dorfmitglied_pkey";
	my $sqlTable = "FROM dorfmitglied";
	$self->search($mitgliedsObj,$sqlSelect ." ". $sqlTable ." ". $sqlWhere);

	return;
}

sub searchKto # ( mitgliedsObjekt, KontoNr, BLZ )
{
    my $self = shift;
    my $mitgliedsObj = shift;

	my $sqlWhere = "WHERE kontonr = ". ${$self->{dbh}}->quote($_[0]) ." and blz = ". ${$self->{dbh}}->quote($_[1]) ."";
    my $sqlSelect = "SELECT dorfmitglied_pkey";
	my $sqlTable = "FROM kontodaten";
	$self->search($mitgliedsObj,$sqlSelect ." ". $sqlTable ." ". $sqlWhere);

	return;
}

sub searchName # ( mitgliedsObjekt, @Namen-2 )
{
    my $self = shift;
    my $mitgliedsObj = shift;

	my $sqlWhere = "WHERE deleted = false and ( name = ". ${$self->{dbh}}->quote($_[0]) ." and vorname = ". ${$self->{dbh}}->quote($_[1]) .") or ".
	                                         "( vorname = ". ${$self->{dbh}}->quote($_[0]) ." and name = ". ${$self->{dbh}}->quote($_[1]) .")";
    my $sqlSelect = "SELECT dorfmitglied_pkey";
	my $sqlTable = "FROM dorfmitglied";
	$self->search($mitgliedsObj,$sqlSelect ." ". $sqlTable ." ". $sqlWhere);

	return;
}

sub search # ( MitgliedsObj, SQL )
{
	my $self = shift;
    my $mitgliedsObj = shift;
	my $sqlStatement = shift;

	my @erg;
    eval {
		@erg = ${$self->{dbh}}->selectrow_array($sqlStatement);
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

	if(scalar @erg == 1) {
		$mitgliedsObj->mitgliedsnr($erg[0]);
		$self->selectMitglied($mitgliedsObj);
	}

	return;
}

sub selectMitglieder # ( [Mitglieds Objekt], [Ordnen nach], [WhereSQLStat] )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $order = shift;
	my $wheresqlstat = shift;
    my $sqlStatement = "SELECT dorfmitglied_pkey,vorname,name,nickname,chaosdorfadr,".
	                           "intern,ccc,shell,einzug,chaosnr ".
					   "FROM dorfmitglied m WHERE m.deleted = 'false'";

    if($mitgliedsObj) {
		if($mitgliedsObj->mitgliedsnr()) {
			$sqlStatement = $sqlStatement .' AND dorfmitglied_pkey = '. $mitgliedsObj->mitgliedsnr() .'';
		} elsif($mitgliedsObj->name()) {
			$sqlStatement = $sqlStatement .' AND name = '. ${$self->{dbh}}->quote($mitgliedsObj->name()) .'';
			$sqlStatement = $sqlStatement .' AND vorname = '. ${$self->{dbh}}->quote($mitgliedsObj->vorname()) .'' if($mitgliedsObj->vorname());
			$sqlStatement = $sqlStatement .' AND nickname = '. ${$self->{dbh}}->quote($mitgliedsObj->nickname()) .'' if($mitgliedsObj->nickname());
		}
    }
	if($wheresqlstat) {
		$sqlStatement = $sqlStatement .' '. $wheresqlstat .'';
	}
    if($order) {
		$sqlStatement = $sqlStatement .' ORDER BY '. $order;
    }

    my @mitgliedsObjekte;
    my $x = 0;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			$mitgliedsObjekte[$x] = Verein::Mitglied->new();
			$mitgliedsObjekte[$x]->mitgliedsnr($erg[0]);
			$mitgliedsObjekte[$x]->vorname($erg[1]);
			$mitgliedsObjekte[$x]->name($erg[2]);
			$mitgliedsObjekte[$x]->nickname($erg[3]);
			$mitgliedsObjekte[$x]->mailbox($erg[4]);
			$mitgliedsObjekte[$x]->internATlist($erg[5]);
			$mitgliedsObjekte[$x]->cccATlist($erg[6]);
			$mitgliedsObjekte[$x]->shellzugang($erg[7]);
			$mitgliedsObjekte[$x]->einzug($erg[8]);
			$mitgliedsObjekte[$x]->chaosnr($erg[9]);
#    	    $mitgliedsObjekte[$x]->eintrittsdatum($erg[5]);
			$x++;
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return @mitgliedsObjekte;
}

sub selectMitglied # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $sqlStatement = "SELECT vorname,name,nickname,chaosdorfadr,intern,ccc,".
	                          "shell,einzug,chaosnr,eintrittsdatum,info ".
					   "FROM dorfmitglied WHERE dorfmitglied_pkey =". $mitgliedsObj->mitgliedsnr() ."";

    eval {
		my @erg = ${$self->{dbh}}->selectrow_array($sqlStatement);
		$mitgliedsObj->setvorname($erg[0]);
		$mitgliedsObj->setname($erg[1]);
		$mitgliedsObj->setnickname($erg[2]);
		$mitgliedsObj->setmailbox($erg[3]);
		$mitgliedsObj->setinternATlist($erg[4]);
		$mitgliedsObj->setcccATlist($erg[5]);
		$mitgliedsObj->setshellzugang($erg[6]);
		$mitgliedsObj->seteinzug($erg[7]);
		$mitgliedsObj->setchaosnr($erg[8]);
		$mitgliedsObj->seteintrittsdatum($erg[9]);
		$mitgliedsObj->setinfo($erg[10]);
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return;
}

sub insertMitglied # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $sqlStatement = "INSERT INTO dorfmitglied ( vorname,name,nickname,chaosdorfadr,intern,ccc,shell,einzug,chaosnr,eintrittsdatum,info )";

    my $values = "VALUES (".    ${$self->{dbh}}->quote($mitgliedsObj->vorname())
	                      .",". ${$self->{dbh}}->quote($mitgliedsObj->name())
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->nickname())
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->mailbox())
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->internATlist())
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->cccATlist())
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->shellzugang())
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->einzug())
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->chaosnr())
						  .",". ${$self->{dbh}}->quote(UnixDate(ParseDate($mitgliedsObj->eintrittsdatum()), "%Y-%m-%d"))
						  .",". ${$self->{dbh}}->quote($mitgliedsObj->info())
						  .")";

    ${$self->{dbh}}->do($sqlStatement ."". $values) or
	    eval { $self->{errorcode} = 1;
			   $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		   };

    return;
}

sub updateMitglied # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $buffer;
    my $sqlStatement = "UPDATE dorfmitglied SET ";
    my $sqlStatementEnd = "WHERE dorfmitglied_pkey = ". $mitgliedsObj->mitgliedsnr() ."";

    my @upDaten;
    push(@upDaten, "vorname = ". ${$self->{dbh}}->quote($buffer) ." ")      if($buffer = $mitgliedsObj->getupvorname());
    push(@upDaten, "name = ". ${$self->{dbh}}->quote($buffer) ." ")         if($buffer = $mitgliedsObj->getupname());
    push(@upDaten, "nickname = ". ${$self->{dbh}}->quote($buffer) ." ")     if($buffer = $mitgliedsObj->getupnickname());
    push(@upDaten, "chaosdorfadr = ". ${$self->{dbh}}->quote($buffer) ." ") if($buffer = $mitgliedsObj->getupmailbox());
    push(@upDaten, "intern = ". ${$self->{dbh}}->quote($buffer) ." ")       if($buffer = $mitgliedsObj->getupinternATlist());
    push(@upDaten, "ccc = ". ${$self->{dbh}}->quote($buffer) ." ")          if($buffer = $mitgliedsObj->getupcccATlist());
    push(@upDaten, "shell = ". ${$self->{dbh}}->quote($buffer) ." ")        if($buffer = $mitgliedsObj->getupshellzugang());
    push(@upDaten, "chaosnr = ". ${$self->{dbh}}->quote($buffer) ." ")      if($buffer = $mitgliedsObj->getupchaosnr());
    push(@upDaten, "eintrittsdatum = ". ${$self->{dbh}}->quote(UnixDate(ParseDate($buffer), "%Y-%m-%d")) ." ")
                                                                           if($buffer = $mitgliedsObj->getupeintrittsdatum());
    push(@upDaten, "einzug = ". ${$self->{dbh}}->quote($buffer) ." ")       if($buffer = $mitgliedsObj->getupeinzug());
    push(@upDaten, "info = ". ${$self->{dbh}}->quote($buffer) ." ")         if($buffer = $mitgliedsObj->getupinfo());

    return unless(@upDaten);

    $sqlStatement = $sqlStatement ."". join(", ",@upDaten);

    ${$self->{dbh}}->do($sqlStatement ."". $sqlStatementEnd) or

    eval {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    };

    return;
}

sub selectAdresse # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $sqlStatement = "SELECT adresse_pkey,strasse,plz,ort FROM adresse WHERE dorfmitglied_pkey =". $mitgliedsObj->mitgliedsnr() ."";

    my $x = 0;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			${$mitgliedsObj->adresse($x)}->id($erg[0]);
			${$mitgliedsObj->getadressObj($x)}->setStr($erg[1]);
			${$mitgliedsObj->getadressObj($x)}->setplz($erg[2]);
			${$mitgliedsObj->getadressObj($x)}->setort($erg[3]);
			$x++;
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return;
}

sub insertAdresse # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $sqlStatement = "INSERT INTO adresse ( dorfmitglied_pkey,strasse,plz,ort )";

    my $values = "VALUES (".    ${$self->{dbh}}->quote($mitgliedsObj->mitgliedsnr())
	                      .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getadressObj($x)}->strasse())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getadressObj($x)}->plz())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getadressObj($x)}->ort())
						  .")";

    ${$self->{dbh}}->do($sqlStatement ."". $values) or
	   eval { $self->{errorcode} = 1;
			  $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		  };

    return;
}

sub updateAdresse # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $buffer;
    my $sqlStatement = "UPDATE adresse SET ";
    my $sqlStatementEnd = "WHERE adresse_pkey = ". ${$mitgliedsObj->getadressObj($x)}->id() ." AND dorfmitglied_pkey = ". $mitgliedsObj->mitgliedsnr();

    my @upDaten;
    push(@upDaten, "strasse = ". ${$self->{dbh}}->quote($buffer) ." ") if($buffer = ${$mitgliedsObj->getadressObj($x)}->getupStr());
    push(@upDaten, "plz = ". ${$self->{dbh}}->quote($buffer) ." ")     if($buffer = ${$mitgliedsObj->getadressObj($x)}->getupplz());
    push(@upDaten, "ort = ". ${$self->{dbh}}->quote($buffer) ." ")     if($buffer = ${$mitgliedsObj->getadressObj($x)}->getuport());

    return unless(@upDaten);

    $sqlStatement = $sqlStatement ."". join(", ",@upDaten);

    ${$self->{dbh}}->do($sqlStatement ."". $sqlStatementEnd) or

    eval {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    };

    return;
}


sub selectKommunikation # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $sqlStatement = "SELECT kommunikation_pkey,email,schluessel FROM kommunikation WHERE dorfmitglied_pkey =". $mitgliedsObj->mitgliedsnr() ."";

    my $x = 0;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			${$mitgliedsObj->kommunikation($x)}->id($erg[0]);
			${$mitgliedsObj->getkommObj($x)}->setemail($erg[1]);
			${$mitgliedsObj->getkommObj($x)}->setpubkey($erg[2]);
			$x++;
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return;
}

sub insertKommunikation # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $sqlStatement = "INSERT INTO kommunikation ( dorfmitglied_pkey,email,schluessel )";

    my $values = "VALUES (".    ${$self->{dbh}}->quote($mitgliedsObj->mitgliedsnr())
	                      .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getkommObj($x)}->email())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getkommObj($x)}->pubkey())
						  .")";

    ${$self->{dbh}}->do($sqlStatement ."". $values) or
	    eval { $self->{errorcode} = 1;
			   $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		   };

    return;
}

sub updateKommunikation # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $buffer;
    my $sqlStatement = "UPDATE kommunikation SET ";
    my $sqlStatementEnd = "WHERE kommunikation_pkey = ". ${$mitgliedsObj->getkommObj($x)}->id() ." AND dorfmitglied_pkey = ". $mitgliedsObj->mitgliedsnr();

    my @upDaten;
    push(@upDaten, "email = ". ${$self->{dbh}}->quote($buffer) ." ")      if($buffer = ${$mitgliedsObj->getkommObj($x)}->getupemail());
    push(@upDaten, "schluessel = ". ${$self->{dbh}}->quote($buffer) ." ") if($buffer = ${$mitgliedsObj->getkommObj($x)}->getuppubkey());

    return unless(@upDaten);

    $sqlStatement = $sqlStatement ."". join(", ",@upDaten);

    ${$self->{dbh}}->do($sqlStatement ."". $sqlStatementEnd) or

    eval {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    };

    return;
}


sub selectKonto # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $sqlStatement = "SELECT kontodaten_pkey,kontonr,bank,blz FROM kontodaten WHERE dorfmitglied_pkey =". $mitgliedsObj->mitgliedsnr() ."";

    my $x = 0;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			${$mitgliedsObj->konto($x)}->id($erg[0]);
			${$mitgliedsObj->getkontoObj($x)}->setKto($erg[1]);
			${$mitgliedsObj->getkontoObj($x)}->setBank($erg[2]);
			${$mitgliedsObj->getkontoObj($x)}->setBLZ($erg[3]);
			$x++;
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return;
}

sub insertKonto # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $sqlStatement = "INSERT INTO kontodaten ( dorfmitglied_pkey,kontonr,bank,blz )";

    my $values = "VALUES (".    ${$self->{dbh}}->quote($mitgliedsObj->mitgliedsnr())
	                      .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getkontoObj($x)}->setKto())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getkontoObj($x)}->setBank())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getkontoObj($x)}->setBLZ())
						  .")";

    ${$self->{dbh}}->do($sqlStatement ."". $values) or
	    eval { $self->{errorcode} = 1;
			   $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		   };

    return;
}

sub updateKonto # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $buffer;
    my $sqlStatement = "UPDATE kontodaten SET ";
    my $sqlStatementEnd = "WHERE kontodaten_pkey = ". ${$mitgliedsObj->getkontoObj($x)}->id() ." AND dorfmitglied_pkey = ". $mitgliedsObj->mitgliedsnr();

    my @upDaten;
    push(@upDaten, "kontonr = ". ${$self->{dbh}}->quote($buffer) ." ") if($buffer = ${$mitgliedsObj->getkontoObj($x)}->getupKto());
    push(@upDaten, "bank = ". ${$self->{dbh}}->quote($buffer) ." ")    if($buffer = ${$mitgliedsObj->getkontoObj($x)}->getupBank());
    push(@upDaten, "blz = ". ${$self->{dbh}}->quote($buffer) ." ")     if($buffer = ${$mitgliedsObj->getkontoObj($x)}->getupBLZ());

    return unless(@upDaten);

    $sqlStatement = $sqlStatement ."". join(", ",@upDaten);

    ${$self->{dbh}}->do($sqlStatement ."". $sqlStatementEnd) or

    eval {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    };

    return;
}


sub selectBeitrag # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $sqlStatement = "SELECT beitragstab_pkey,beitrag,gueltigab,spende,info,schulden FROM beitragstab WHERE dorfmitglied_pkey =". $mitgliedsObj->mitgliedsnr() ."";

    my $x = 0;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			${$mitgliedsObj->beitrag($x)}->id($erg[0]);
			${$mitgliedsObj->getbeitragObj($x)}->setbeitrag($erg[1]);
			${$mitgliedsObj->getbeitragObj($x)}->setdatum($erg[2]);
			${$mitgliedsObj->getbeitragObj($x)}->setspende($erg[3]);
			${$mitgliedsObj->getbeitragObj($x)}->setinfo($erg[4]);
			${$mitgliedsObj->getbeitragObj($x)}->setschulden($erg[5]);
			$x++;
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return;
}

sub insertBeitrag # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $sqlStatement = "INSERT INTO beitragstab ( dorfmitglied_pkey,beitrag,gueltigab,spende,info,schulden)";

    my $values = "VALUES (".    ${$self->{dbh}}->quote($mitgliedsObj->mitgliedsnr())
	                      .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getbeitragObj($x)}->beitrag())
						  .",". ${$self->{dbh}}->quote(UnixDate(ParseDate(${$mitgliedsObj->getbeitragObj($x)}->datum()), "%Y-%m-%d"))
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getbeitragObj($x)}->spende())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getbeitragObj($x)}->info())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getbeitragObj($x)}->schulden())
						  .")";

    ${$self->{dbh}}->do($sqlStatement ."". $values) or
	    eval { $self->{errorcode} = 1;
			   $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		   };

    return;
}

sub updateBeitrag # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $buffer;
    my $sqlStatement = "UPDATE beitragstab SET ";
    my $sqlStatementEnd = "WHERE beitragstab_pkey = ". ${$mitgliedsObj->getbeitragObj($x)}->id() ." AND dorfmitglied_pkey = ". $mitgliedsObj->mitgliedsnr();

    my @upDaten;
    push(@upDaten, "beitrag = ". ${$self->{dbh}}->quote($buffer) ." ")   if($buffer = ${$mitgliedsObj->getbeitragObj($x)}->getupbeitrag());
    push(@upDaten, "gueltigab = ". ${$self->{dbh}}->quote(UnixDate(ParseDate($buffer), "%Y-%m-%d")) ." ")
                                                                         if($buffer = ${$mitgliedsObj->getbeitragObj($x)}->getupdatum());
    push(@upDaten, "spende = ". ${$self->{dbh}}->quote($buffer) ." ")    if($buffer = ${$mitgliedsObj->getbeitragObj($x)}->getupspende());
    push(@upDaten, "info = ". ${$self->{dbh}}->quote($buffer) ." ")      if($buffer = ${$mitgliedsObj->getbeitragObj($x)}->getupinfo());
    push(@upDaten, "schulden = ". ${$self->{dbh}}->quote($buffer) ." ")  if($buffer = ${$mitgliedsObj->getbeitragObj($x)}->getupschulden());

    return unless(@upDaten);

    $sqlStatement = $sqlStatement ."". join(", ",@upDaten);

    ${$self->{dbh}}->do($sqlStatement ."". $sqlStatementEnd) or

    eval {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    };

    return;
}


sub selectSaldo # ( mitgliedObj )
{
    my $self = shift;
    my $mitgliedsObj = shift;

    my $sqlStatement = "SELECT saldo_pkey,betrag,datum,bezeichnung,barkonto,konten,info FROM saldo WHERE dorfmitglied_pkey =". $mitgliedsObj->mitgliedsnr() ."";

    my $x = 0;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			${$mitgliedsObj->saldo($x)}->id($erg[0]);
			${$mitgliedsObj->getsaldoObj($x)}->setbetrag($erg[1]);
			${$mitgliedsObj->getsaldoObj($x)}->setdatum($erg[2]);
			${$mitgliedsObj->getsaldoObj($x)}->setbezeichnung($erg[3]);
			${$mitgliedsObj->getsaldoObj($x)}->setbarkonto($erg[4]);
			${$mitgliedsObj->getsaldoObj($x)}->setkonto($erg[5]);
			${$mitgliedsObj->getsaldoObj($x)}->setinfo($erg[6]);
			$x++;
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return;
}

sub insertSaldo # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $sqlStatement = "INSERT INTO saldo ( dorfmitglied_pkey,betrag,datum,bezeichnung,barkonto,konten,info )";

    my $values = "VALUES (".    ${$self->{dbh}}->quote($mitgliedsObj->mitgliedsnr())
	                      .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getsaldoObj($x)}->betrag())
						  .",". ${$self->{dbh}}->quote(UnixDate(ParseDate(${$mitgliedsObj->getsaldoObj($x)}->datum()), "%Y-%m-%d"))
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getsaldoObj($x)}->bezeichnung())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getsaldoObj($x)}->barkonto())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getsaldoObj($x)}->konto())
						  .",". ${$self->{dbh}}->quote(${$mitgliedsObj->getsaldoObj($x)}->info())
						  .")";

    ${$self->{dbh}}->do($sqlStatement ."". $values) or
	    eval { $self->{errorcode} = 1;
			   $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
		   };

    return;
}

sub updateSaldo # ( mitgliedObj, x )
{
    my $self = shift;
    my $mitgliedsObj = shift;
    my $x = shift;

    my $buffer;
    my $sqlStatement = "UPDATE saldo SET ";
    my $sqlStatementEnd = "WHERE saldo_pkey = ". ${$mitgliedsObj->getsaldoObj($x)}->id() ." AND dorfmitglied_pkey = ". $mitgliedsObj->mitgliedsnr();

    my @upDaten;
    push(@upDaten, "betrag = ". ${$self->{dbh}}->quote($buffer) ." ")      if($buffer = ${$mitgliedsObj->getsaldoObj($x)}->getupbetrag());
    push(@upDaten, "datum = ". ${$self->{dbh}}->quote(UnixDate(ParseDate($buffer), "%Y-%m-%d")) ." ")
	                                                                       if($buffer = ${$mitgliedsObj->getsaldoObj($x)}->getupdatum());
    push(@upDaten, "bezeichnung = ". ${$self->{dbh}}->quote($buffer) ." ") if($buffer = ${$mitgliedsObj->getsaldoObj($x)}->getupbezeichnung());
    push(@upDaten, "barkonto = ". ${$self->{dbh}}->quote($buffer) ." ")    if($buffer = ${$mitgliedsObj->getsaldoObj($x)}->getupbarkonto());
    push(@upDaten, "konten = ". ${$self->{dbh}}->quote($buffer) ." ")      if($buffer = ${$mitgliedsObj->getsaldoObj($x)}->getupkonto());
    push(@upDaten, "info = ". ${$self->{dbh}}->quote($buffer) ." ")        if($buffer = ${$mitgliedsObj->getsaldoObj($x)}->getupinfo());

    return unless(@upDaten);

    $sqlStatement = $sqlStatement ."". join(", ",@upDaten);

    ${$self->{dbh}}->do($sqlStatement ."". $sqlStatementEnd) or
    eval {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    };

    return;
}


sub selectKonten # ()
{
    my $self = shift;
    my $sqlStatement = "SELECT kenz,info FROM konten";

    my %konto;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			$konto{$erg[0]} = $erg[1];
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return %konto;
}

sub selectBarkonto # ()
{
    my $self = shift;
    my $sqlStatement = "SELECT konto,info FROM barkonto";

    my %konto;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		while(my @erg = $sth->fetchrow_array()) {
			$konto{$erg[0]} = $erg[1];
		}
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

    return %konto;
}

sub DESTROY
{
    my $self = shift;
    #${$self->{dbh}}->disconnect; Hat sich selber schon vorher zerstoert !?
    return;
}

1;
