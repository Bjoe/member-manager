#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/BuchDB.pm,v 1.1 2005/09/11 22:09:41 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: BuchDB.pm,v $
# Revision 1.1  2005/09/11 22:09:41  jboehme
# Initial Revision
#
#

package Verein::BuchDB;

use strict;
use warnings;
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
    my $dbname = "chaosdorf";
    $dbname = shift if(@_);

	my $dsn = $hostname ? "database=$dbname;host=$hostname;port=$port" : "dbname=$dbname";
    my $dbh = DBI->connect("DBI:Pg:$dsn", $user, $passw,
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

	$self->{debug} = $debuglevel;
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

sub nextTrxID
{
	my $self = shift;

    my $sqlStatement = "SELECT NEXTVAL('nexttrxid_seq')";

	my $id;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		$id = $sth->fetchrow_array();
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

	return $id;
}

sub selectLastBuchung # ( )
{
    my $self = shift;

    my $sqlStatement = "SELECT zwshkenn62,zwbudatum62,zwischensaldo62 FROM kasse WHERE deleted = FALSE ORDER BY zwbudatum62 DESC LIMIT 1";

	my @erg;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		@erg = $sth->fetchrow_array();
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

	return @erg;
}

sub selectBuchung # ( )
{
	my $self = shift;

	my $sqlStatement = "SELECT valutadatum,buchungsdatum FROM kasse WHERE deleted = FALSE ORDER BY valutadatum DESC LIMIT 1";

	my @erg;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		@erg = $sth->fetchrow_array();
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

	return @erg;
}

sub insertMT940 # ( einleseDatum , einleseID , mt940Obj , x )
{
    my $self = shift;
	my $einleseDatum = shift;
	my $einleseID = shift;
    my $mt940Obj = shift;
    my $x = shift;

    my $sqlStatement = "INSERT INTO kasse ( einlesedatum,einleseID,auszug,zwshkenn60,zwbudatum60,zwischensaldo60,zwshkenn62,zwbudatum62,".
	                                         "zwischensaldo62,valutadatum,buchungsdatum,shkenn,betrag,bankbuschl,fremdblz,fremdktnr,fremdname,bezeichnung )";

	for(my $y = 0; $y <= $mt940Obj->statmentLines($x); $y++) {
		my $daten = $mt940Obj->informationAccount($x,$y);

		my $clear = '0-';
		$clear =~ /(.)./;
		$daten =~ /^(\d{3})((\?\d{2})|$)/;
		my $buchschl = $1;

		$clear =~ /(.)./;
		$daten =~ /\?30(\d{8})((\?\d{2})|$)/;
		my $fremdblz = $1;

		$clear =~ /(.)./;
		$daten =~ /\?31(\d*?)((\?\d{2})|$)/;
		my $fremdkonto = $1;

		$clear =~ /.(.)/;
		$daten =~ /\?32(.*?)((\?\d{2})|$)/;
		my $fremdname = $1;

		$clear =~ /.(.)/;
		$daten =~ /\?33(.*?)((\?\d{2})|$)/;
		$fremdname .= ' '. $1 if($1 ne "-");

		$clear =~ /.(.)/;
		$daten =~ /\?00(.*?)((\?\d{2})|$)/;
		my $information = $1;

		$clear =~ /.(.)/;
		$daten =~ /(\?2[0-9](.*?))((\?[0-1,3-9])|$)/;
		$information .= ' '. $1;
		$information =~ s/\?2\d/ /g;

		print "VALUES (".    ($einleseDatum ? $einleseDatum : "-")
		                      .",". ($einleseID ? $einleseID : "-")
							  .",". ($mt940Obj->statementNr($x) ? $mt940Obj->statementNr($x) : "-")
							  ."/". ($mt940Obj->sequenceNr($x) ? $mt940Obj->sequenceNr($x) : "-")
							  .",". ($mt940Obj->openingBalanceCode($x) ? $mt940Obj->openingBalanceCode($x) : "-")
							  .",". ($mt940Obj->openingBalanceDate($x,"iso8601") ? $mt940Obj->openingBalanceDate($x,"iso8601") : "-")
							  .",". (($mt940Obj->openingBalance($x))[0] ? ($mt940Obj->openingBalance($x))[0] : "-")
							  .",". ($mt940Obj->closingBalanceCode($x) ? $mt940Obj->closingBalanceCode($x) : "-")
							  .",". ($mt940Obj->closingBalanceDate($x,"iso8601") ? $mt940Obj->closingBalanceDate($x,"iso8601") : "-")
							  .",". (($mt940Obj->closingBalance($x))[0] ? ($mt940Obj->closingBalance($x))[0] : "-")
							  .",". ($mt940Obj->valueDate($x,$y,"iso8601") ? $mt940Obj->valueDate($x,$y,"iso8601") : "-")
							  .",". ($mt940Obj->entryDate($x,$y,"iso8601") ? $mt940Obj->entryDate($x,$y,"iso8601") : "-")
							  .",". ($mt940Obj->statementCode($x,$y) ? $mt940Obj->statementCode($x,$y) : "-")
							  .",". ($mt940Obj->amount($x,$y) ? $mt940Obj->amount($x,$y) : "-")
							  .",". ($buchschl ? $buchschl : "-")
		                      .",". ($fremdblz ? $fremdblz : "-")
		                      .",". ($fremdkonto ? $fremdkonto : "-")
		                      .",". ($fremdname ? $fremdname : "-")
		                      .",". ($information ? $information : "-")
							  .")\n\n\n" if($self->{debug});
		my $values = "VALUES (".    ${$self->{dbh}}->quote($einleseDatum)
		                      .",". $einleseID
							  .",". ${$self->{dbh}}->quote($mt940Obj->statementNr($x) ."". $mt940Obj->sequenceNr($x))
							  .",". ${$self->{dbh}}->quote($mt940Obj->openingBalanceCode($x))
							  .",". ${$self->{dbh}}->quote($mt940Obj->openingBalanceDate($x,"iso8601"))
							  .",". ${$self->{dbh}}->quote(($mt940Obj->openingBalance($x))[0])
							  .",". ${$self->{dbh}}->quote($mt940Obj->closingBalanceCode($x))
							  .",". ${$self->{dbh}}->quote($mt940Obj->closingBalanceDate($x,"iso8601"))
							  .",". ${$self->{dbh}}->quote(($mt940Obj->closingBalance($x))[0])
							  .",". ${$self->{dbh}}->quote($mt940Obj->valueDate($x,$y,"iso8601"))
							  .",". ${$self->{dbh}}->quote($mt940Obj->entryDate($x,$y,"iso8601"))
							  .",". ${$self->{dbh}}->quote($mt940Obj->statementCode($x,$y))
							  .",". ${$self->{dbh}}->quote($mt940Obj->amount($x,$y))
							  .",". ${$self->{dbh}}->quote($buchschl)
		                      .",". ${$self->{dbh}}->quote($fremdblz)
		                      .",". ${$self->{dbh}}->quote($fremdkonto)
		                      .",". ${$self->{dbh}}->quote($fremdname)
							  .",". ${$self->{dbh}}->quote($information)
							  .")";

		${$self->{dbh}}->do($sqlStatement ."". $values) or
		  eval { $self->{errorcode} = 1;
				 $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
			 };
	}


    return;
}

sub getBuchungen # ( TransActionID , [ALL])
{
	my $self = shift;
	my ($trxid,$all) = @_;

	my $sqlStatement = 'SELECT';
	my $sqlSelect = 'kasse_pkey,valutadatum,shkenn,betrag,fremdname,bezeichnung,bankbuschl,fremdblz,fremdktnr';
	my $sqlTabelle = 'FROM kasse WHERE ';
	my $sqlWhere = 'deleted = FALSE order by valutadatum';

	my $sqlWhere2 = $trxid ? "einleseID = $trxid AND " : '';
	my $sqlWhere3 = $all ? '' : 'erfasst = FALSE and barkonto IS NULL and konten IS NULL and dorfmitglied_pkey IS NULL and ';

	$sqlStatement .= ' '. $sqlSelect .' '. $sqlTabelle .' '. $sqlWhere2 .''. $sqlWhere3 .''. $sqlWhere;

	my $ergref;
    eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		$ergref = $sth->fetchall_arrayref();
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
    }

	return $ergref;
}

sub setErfasst # ( Primary Key, Boolean )
{
	my $self = shift;
	my ($pkid,$true) = @_;

	my $sqlStatement = "UPDATE kasse SET erfasst = ";

	$sqlStatement .= $true ? "TRUE " : "FALSE ";

	$sqlStatement .= "WHERE kasse_pkey = $pkid";

	${$self->{dbh}}->do($sqlStatement) or
	    eval { $self->{errorcode} = 1;
			   $self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
	    };

    return;
}

sub getTRXID # ()
{
	my $self = shift;

	my $sqlStatement = "SELECT DISTINCT(einleseid) FROM kasse;";

	my $ergref;
	eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		$ergref = $sth->fetchall_arrayref();
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
	};

    return $ergref;
}

sub beitragSum # ( Mitglieds ID )
{
	my $self = shift;
	
	my ($mitgliedID) = @_;
	
	my $sqlStatement = "SELECT SUM(betrag) FROM saldo WHERE dorfmitglied_pkey=$mitgliedID";
	
	my $ergref;
	eval {
		my $sth = ${$self->{dbh}}->prepare($sqlStatement);
		$sth->execute();
		$ergref = $sth->fetchall_arrayref();
    };

    if($@) {
		$self->{errorcode} = 1;
		$self->{error} = "\nFehler: $@\n\nDBMeldung: $DBI::errstr\n";
	};

    return ${${$ergref}[0]}[0];	
}

sub DESTROY
{
    my $self = shift;
    ${$self->{dbh}}->disconnect;
    return;
}

1;
