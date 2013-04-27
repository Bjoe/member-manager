#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/dorfverw,v 1.8 2006/06/06 20:00:20 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: dorfverw,v $
# Revision 1.8  2006/06/06 20:00:20  jboehme
# - BUGFIX: Option -dbserver Hostname wird als Verbindung zum Datenbankserver angegeben
# - Aenderung: Das Loeschen der Mitglieder wurde rausgenommen, da noch nicht korrekt implementiert
#
# Revision 1.6  2005/09/11 19:59:16  jboehme
# - BUGFIX: Ausbesserung der "Einzug"-aenderung
# - Erweiterung auf "Schulden" eingabe
#
# Revision 1.5  2005/08/11 19:02:59  jboehme
# - "Anzeige" Funktionen in einer extra Verein::Anzeige Klasse ausgelagert
# - STRG-C Abfangen
# - Einige BugFixes bei der Eingabe neuer Mitglieder
# - Abaendern der Klassen/Modul "Aufrufe" nach package Namensaenderung
#
# Revision 1.4  2005/08/10 10:55:02  jboehme
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
# Revision 1.1  2004/10/16 20:52:17  jboehme
# CVS erst Import
# Lauffaehige Version
#
# Name: dorfverw
# Version: 0.7
# Autor: Joerg-C. Boehme
# Datum: 03.05.2002
# Letzte Aenderung: 06.07.2003
#
# History
# 06.07.2003 Die Mitglieder Ausgabe kann nach belieben Sortiert werden.
#            Mitglieder Statistik
#            Alle Mitglieder in Mitgliedsaenderung anzeigen
#            Fehler in der Mitgliedsanzeige ausgebessert
#
# 06.03.2003 Anpassen auf Postgresql Datenbank
#            Verbesserung der UPDATE ... auf WHERE PrimaryKey
#
# 08.09.2002 Die Format ausgabe wurde nochmal angepasst
#
# 24.08.2002 Einige Datenfelder werden verschluesselt in die Datenbank abgelegt
#            Version 0.5
#
# 14.07.2002 Die Ausgabe der Daten zeigt jetzt "Format" :-)
#            Version 0.4
#
# 30.06.2002 Passwort kann jetzt -verdeckt- eingegeben werden
#            Die -Eingaben- koennen jetzt verbessert werden.
#            Bildschirm wird geloescht.
#            Version 0.3 ist damit fertig ....
#
# 30.06.2002 Man kann jetzt allevorname    |    name     |  nickname Daten zum Mitglied abaendern.
#            Programm-Code bereinigt.
#            Version 0.2 ist damit fertig ...
#
# 19.05.2002 Das "flag" wird jetzt mit verarbeitet
#
# 18.05.2002 Datenbank Erweiterung: flag und schluessel (GnuPG)
#            Der Schluessel lasst sich schon ueber GnuPG einpflegen
#
# 05.05.2002 Neues Mitglied Eintragen funktioniert und
#            Mitglieder koennen jetzt auch ("austreten" :-).) geloescht werden
#            Man kann sich jetzt auch alle Infos zu einem User anschauen
#            Version 0.1 ist damit fertig ....
#
# 03.05.2002 Man kann sich schon mal ALLE Mitglieder ausgeben lassen. :-)
#
#-------------------------------------------------------------------------------------------------
#
# Requiremnts:
#	DBI 1.28
#	Date::Manip 5.40
#	GnuPG::Interface 0.31
#	Class::MethodMaker 1.02
#	Term::ReadKey 2.14
#	Term::ReadLine::Gnu 1.12
#	File::Temp 0.12                  File-Temp-0.12.tar.gz
#       File::Spec 0.82                  File-Spec-0.82.tar.gz
#

use lib('../pmodule');
use strict;
use Getopt::Long;
use Date::Manip;
use Term::Cap;
use Term::ReadKey;
use Term::ReadLine;
use File::Temp qw/tempfile/;
use Verein::Datenbank;
use Verein::Mitglied;
use Verein::Misc;
use Verein::Anzeige;
use Verein::BuchDB;

my($dbhobj); # Globale Objekte
Date_Init("Language=German","DateFormat=nonUS");

$SIG{INT} = \&hauptmenue;

my ($host, $debug, $help);
GetOptions('dbserver=s' => \$host,
		   'debug:s' => \$debug,
		   'h' => \$help,
		   'help' => \$help);

usage() if($help);

my $OSPEED = 9600;
eval {
	require POSIX;
	my $termios = POSIX::Termios->new();
	$termios->getattr;
	$OSPEED = $termios->getospeed;
	print $OSPEED if($debug);
};

my $terminal = Term::Cap->Tgetent({OSPEED=>$OSPEED});
my $clear;
if($debug) {
    $clear = "\nLoesche Bildschirm :-)\n\n";
} else {
    $clear = $terminal->Tputs('cl',1);
}

###########################################################
## Einloggen###############################################
print $clear;

my $user = $ENV{'USER'};
eval {
	$dbhobj = Verein::Datenbank->new($user,"", $host);
};
if($@) {
	print $@;
	exit;
}

if($debug) {
    $dbhobj->debug($debug);
}

hauptmenue();

###########################################################
## Haupt-Menue
###########################################################
sub hauptmenue
{
	while (1) {
		print $clear;
		print "\nMenue:\n\n";
		print "1. Neues Mitglied eintragen\n";
		print "2. Mitglieder zeigen\n";
		print "3. Mitgliedsaenderung\n";
		print "4. intern\@chaosdorf.de\n";
		print "5. Shell Accounts\n";
		print "6. intern\@ccc.de\n";
		print "7. Mitglied loeschen\n";
		print "8. Umsatz/Konto Anzeige\n";
		print "e Ende\n";
		my $eingabe = Verein::Misc::zEingabe();

		foreach($eingabe) {
		  SWITCH: {
				/^1/ && do {
					newmit();
					last SWITCH;
				};
				/^2/ && do {
					auslesen();
					last SWITCH;
				};
				/^3/ && do {
					change();
					last SWITCH;
				};
				/^4/ && do {
					anzeigeInternList();
					last SWITCH;
				};
				/^5/ && do {
					anzeigeShellAccount();
					last SWITCH;
				};
				/^6/ && do {
					anzeigeInternCCClist();
					last SWITCH;
				};
				/^7/ && do {
					deletemit();
					last SWITCH;
				};
				/^8/ && do {
					umsAnzeigen();
					last SWITCH;
				};

				/^e/ && do {
					ende();
					last SWITCH;
				};
				print "\nAeh !? $eingabe\n";
			}
		}
	}
}

###########################################################
## Einlesen
###########################################################
sub newmit {
	my @zeichen = ("y","n", "1", "0");

	print $clear;

	my ($name,$vorname,$nick,$einzug,$eintrittsda,$chaosnr,$intern,$ccc,$sh,$email,
		$strasse,$plz,$ort,$email2,$schluessel,$kontonr,$bank,$blz,$beitrag,$spende,
		$datum,$mitglied);

	my $error = 0;
	my $wdh = 1;
	my $mitglnr = 0;
	do {

		if($error) {
			$mitglnr = $mitglied->mitgliedsnr();
		} else {
			$mitglied = Verein::Mitglied->new($dbhobj);
			$mitglnr = $mitglied->mitgliedsnr("new");
		}
		print "\n\nDie Mitgliedsnr ist: ". $mitglnr ."\n";

		$name = Verein::Misc::stdEingabe("Nachname:",$name);
		$vorname = Verein::Misc::stdEingabe("Vorname:",$vorname);
		$nick = Verein::Misc::stdEingabe("Nickname:",$nick);
		$einzug = Verein::Misc::boolEingabe("Einzug: (y/n)", \@zeichen,$einzug);
		$eintrittsda = Verein::Misc::datumEingabe("Eintrittsdatum: (dd.mm.yyyy)",$eintrittsda);
		$chaosnr = Verein::Misc::stdEingabe("ChaosNr.:",$chaosnr);
		$intern = Verein::Misc::stdEingabe("intern\@chaosdorf.de (Email):",$intern);
		$ccc = Verein::Misc::stdEingabe("inter\@list.ccc.de (Email):",$ccc);
		$sh = Verein::Misc::stdEingabe("Shell Zugang (Username):",$sh);
		$email = Verein::Misc::stdEingabe("Email Adr. Chaosdorf (Mailboxname):",$email);

		$strasse = Verein::Misc::stdEingabe("Strasse:",$strasse);
		$plz = Verein::Misc::stdEingabe("PLZ:",$plz);
		$ort = Verein::Misc::stdEingabe("Ort:",$ort);

		$email2 = Verein::Misc::stdEingabe("Email Adr.:",$email2);
#		$schluessel = Verein::Misc::schluesselAuswaehlen();

		if($einzug =~ m/y|1/) {
			$kontonr = Verein::Misc::stdEingabe("KontoNr.:",$kontonr);
			$bank = Verein::Misc::stdEingabe("Bank:",$bank);
			$blz = Verein::Misc::stdEingabe("BLZ:",$blz);
		} else {
			$kontonr = "" if($kontonr);
			$bank = "" if($bank);
			$blz = "" if($blz);
		}

		$beitrag = Verein::Misc::stdEingabe("Beitrag:",$beitrag);
		$spende = Verein::Misc::stdEingabe("Spende:",$spende);
		$datum = Verein::Misc::datumEingabe("Beginn der Beitragszahlung: (dd.mm.yyyy)",$datum);

		$mitglied->name($name);
		$mitglied->vorname($vorname);
		$mitglied->nickname($nick);
		$mitglied->einzug($einzug);
		$mitglied->eintrittsdatum($eintrittsda);
		$mitglied->chaosnr($chaosnr);
		$mitglied->internATlist($intern);
		$mitglied->cccATlist($ccc);
		$mitglied->shellzugang($sh);
		$mitglied->mailbox($email);
		#  $mitglied->info(infoEingabe());

		$mitglied->adresse() unless($error);
		${$mitglied->getadressObj()}->strasse($strasse);
		${$mitglied->getadressObj()}->plz($plz);
		${$mitglied->getadressObj()}->ort($ort);

		$mitglied->kommunikation() unless($error);
		${$mitglied->getkommObj()}->email($email2);
#		${$mitglied->getkommObj()}->pubkey($schluessel);

		if($einzug =~ m/y|1/) {
			$mitglied->konto() unless($mitglied->getkontoObj());
			${$mitglied->getkontoObj()}->kontonummer($kontonr);
			${$mitglied->getkontoObj()}->bank($bank);
			${$mitglied->getkontoObj()}->bankleitzahl($blz);
		} elsif($mitglied->getkontoObj()) {
			$mitglied->deletLastkontoObj();
		}

		$mitglied->beitrag() unless($error);
		${$mitglied->getbeitragObj()}->beitrag($beitrag);
		${$mitglied->getbeitragObj()}->spende($spende);
		${$mitglied->getbeitragObj()}->datum($datum);

		unless($error) {
			${$mitglied->saldo()}->betrag(0);
			${$mitglied->getsaldoObj()}->datum(UnixDate("heute","%d.%m.%Y"));
			${$mitglied->getsaldoObj()}->bezeichnung("Start Saldo");
			${$mitglied->getsaldoObj()}->info("Start Saldo\n");
		}

		print "\n\n";
		my $lines;
		$lines = Verein::Anzeige::mitglAusgabe([$mitglied],0);
		$lines = Verein::Anzeige::adressAusgabe($mitglied, $lines);
		$lines = Verein::Anzeige::kommAusgabe($mitglied, $lines);
		$lines = Verein::Anzeige::miscAusgabe($mitglied, $lines);
		$lines = Verein::Anzeige::kontoAusgabe($mitglied, $lines);
		$lines = Verein::Anzeige::beitragAusgabe($mitglied, $lines);
		$lines = Verein::Anzeige::saldoAusgabe($mitglied, $lines);

		if(Verein::Misc::boolEingabe("Sind diese Angaben Korrekt ? (y/n)",\@zeichen) eq "y") {
			print "\nBitte warten ....\n";
			if($mitglied->saveMitglied()) {
				$wdh = 1;
				$error = 1;
			} else {
				$error = 0;
				print "\nNoch ein Mitglied einpflegen ?";
				if(Verein::Misc::boolEingabe(" (y/n)", \@zeichen) eq "y") {
					$wdh = 1;
				} else {
					$wdh = 0;
				}
			}
		} else {
			$error = 1;
			$wdh = 1;
		}
	} while($wdh);

	return;
}

###########################################################
## internListe
###########################################################
sub anzeigeInternList
{
    my ($sort, $stdin, $eing);
	$eing = 'n';
    do {
		print $clear;
		$sort = "dorfmitglied_pkey" if($eing && $eing =~ m/n/);
		$sort = "vorname, name, nickname" if($eing && $eing =~ m/v/);
		$sort = "name, vorname, nickname" if($eing && $eing =~ m/a/);
		$sort = "nickname, name, vorname" if($eing && $eing =~ m/i/);
		my @mObjs = $dbhobj->selectMitglieder(undef,$sort,"AND NOT intern = ''");

		if($dbhobj->isError()) { print "". $dbhobj->getError() ."\n";}

		Verein::Anzeige::internList(\@mObjs,0);
		print "Sortierung nach: Mitglieds(n)r./(v)orname/n(a)me/n(i)ckname\n";
		print "(0 = Ende)";

		$stdin = Verein::Misc::bEingabe();
		return unless($stdin);
		$eing = $stdin;

    } while($stdin =~ m/\D/);

    return;
}

###########################################################
## shell Account
###########################################################
sub anzeigeShellAccount
{
    my ($sort, $stdin, $eing);
	$eing = 'n';
    do {
		print $clear;
		$sort = "dorfmitglied_pkey" if($eing && $eing =~ m/n/);
		$sort = "vorname, name, nickname" if($eing && $eing =~ m/v/);
		$sort = "name, vorname, nickname" if($eing && $eing =~ m/a/);
		$sort = "nickname, name, vorname" if($eing && $eing =~ m/i/);
		my @mObjs = $dbhobj->selectMitglieder(undef,$sort,"AND NOT shell = ''");

		if($dbhobj->isError()) { print "". $dbhobj->getError() ."\n";}

		Verein::Anzeige::shellAccount(\@mObjs,0);
		print "Sortierung nach: Mitglieds(n)r./(v)orname/n(a)me/n(i)ckname\n";
		print "(0 = Ende)";

		$stdin = Verein::Misc::bEingabe();
		return unless($stdin);
		$eing = $stdin;

    } while($stdin =~ m/\D/);

    return;
}

###########################################################
## CCC Liste
###########################################################
sub anzeigeInternCCClist
{
    my ($sort, $stdin, $eing);
	$eing = 'n';
    do {
		print $clear;
		$sort = "dorfmitglied_pkey" if($eing && $eing =~ m/n/);
		$sort = "vorname, name, nickname" if($eing && $eing =~ m/v/);
		$sort = "name, vorname, nickname" if($eing && $eing =~ m/a/);
		$sort = "nickname, name, vorname" if($eing && $eing =~ m/i/);
		my @mObjs = $dbhobj->selectMitglieder(undef,$sort,"AND NOT ccc = ''");

		if($dbhobj->isError()) { print "". $dbhobj->getError() ."\n";}

		Verein::Anzeige::interCCClist(\@mObjs,0);
		print "Sortierung nach: Mitglieds(n)r./(v)orname/n(a)me/n(i)ckname\n";
		print "(0 = Ende)";

		$stdin = Verein::Misc::bEingabe();
		return unless($stdin);
		$eing = $stdin;

    } while($stdin =~ m/\D/);

    return;
}

###########################################################
## Auslesen
###########################################################
sub auslesen {
    my $eingabe;
    return unless($eingabe = mitanz());
    anzeigen($eingabe);
    Verein::Misc::zEingabe();

    return;
}

sub mitanz{
    my ($sort, $stdin, $eing);
    do {
		print $clear;
		$sort = "dorfmitglied_pkey" if($eing && $eing =~ m/n/);
		$sort = "vorname, name, nickname" if($eing && $eing =~ m/v/);
		$sort = "name, vorname, nickname" if($eing && $eing =~ m/a/);
		$sort = "nickname, name, vorname" if($eing && $eing =~ m/i/);
		my @mObjs = $dbhobj->selectMitglieder(undef,$sort);

		if($dbhobj->isError()) { print "". $dbhobj->getError() ."\n";}

		Verein::Anzeige::mitglAusgabe(\@mObjs,0);
		print "Sortierung nach: Mitglieds(n)r./(v)orname/n(a)me/n(i)ckname\n";
		print "Mitglied Auswaehlen (MitgliedsNR/0 = Ende)";

		$stdin = Verein::Misc::bEingabe();
		return unless($stdin);
		$eing = $stdin;

    } while($stdin =~ m/\D/);

    return $stdin;
}


###########################################################
sub anzeigen {
    my ($mitglnr) = @_;

    my $mitgliedObj = Verein::Mitglied->new($dbhobj);
    $mitgliedObj->getMitglied($mitglnr);

    print $clear;
    my ($buf, $lines);
    $lines = Verein::Anzeige::mitglAusgabe([$mitgliedObj],0);
    $lines = Verein::Anzeige::adressAusgabe($mitgliedObj, $lines);
    $lines = Verein::Anzeige::kommAusgabe($mitgliedObj, $lines);
    $lines = Verein::Anzeige::miscAusgabe($mitgliedObj, $lines);
    $lines = Verein::Anzeige::kontoAusgabe($mitgliedObj, $lines);
    $lines = Verein::Anzeige::beitragAusgabe($mitgliedObj, $lines);
    Verein::Anzeige::infoAusgabe($mitgliedObj);
    Verein::Misc::zEingabe();
    Verein::Anzeige::saldoAusgabe($mitgliedObj,0);

    return;
}

###########################################################
sub umsAnzeigen
{
	my ($refBuchungen, $buchungsDB);
	eval {
		$buchungsDB = Verein::BuchDB->new($user,"",$host);
		$buchungsDB->debug($debug) if($debug);
		$refBuchungen = $buchungsDB->getBuchungen(undef,"ALL");
	};
	if($@ || $buchungsDB->isError()) {
		print "$@\n";
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		return;
	}

	Verein::Anzeige::umsAusgabe($refBuchungen,0);
	return;
}

###########################################################
## Aendern
###########################################################
sub change {
    print "\nMitgliedsaenderung\n";
    my $mitgliedNr = mitanz();
    return unless($mitgliedNr);
    my $mitgliedObj = Verein::Mitglied->new($dbhobj);
    $mitgliedObj->getMitglied($mitgliedNr);
    changeMenu($mitgliedObj);
    return;
}

sub changeMenu {
    my $mitgliedObj = shift;

    my $status = 0;
    while (1) {
		print $clear;
		print "\nWelche Daten sollen zum Mitglied\n"
		      ."NR: ". $mitgliedObj->mitgliedsnr()
			  ."\n Vorname: ". $mitgliedObj->vorname()
			  ."\n Name: " . $mitgliedObj->name()
			  ."\n Nickname: " . $mitgliedObj->nickname()
			  ."\ngeaendert werden ? \n\n";
		print "1. Name, Vorname, Nickname\n";
		print "2. Misc Daten (intern ccc Shell chaosnr Eintrittsdatum)\n";
		print "3. Adressen\n";
		print "4. Email Adr/Schluessel\n";
		print "5. Kontodaten\n";
		print "6. Beitrag, Datum\n";
		print "7. Saldo Daten\n";
		print "8. Bemerkung / INFO\n";
		print "9. Aenderung in die Datenbank uebertragen\n";
		print "e. Ende\n";

		my $eingabe = Verein::Misc::zEingabe();

		foreach($eingabe) {
		  SWITCH: {
				/^1/ && do {
					changeDorfmitglied($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^2/ && do {
					changeDaten($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^3/ && do {
					changeAdresse($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^4/ && do {
					changeKommunikation($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^5/ && do {
					changeKonto($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^6/ && do {
					changeBeitrag($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^7/ && do {
					changeSaldo($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^8/ && do {
					changeInfo($mitgliedObj);
					$status = 1;
					last SWITCH;
				};
				/^9/ && do {
					$mitgliedObj->changeMitglied();
					$status = 0;
					last SWITCH;
				};
				/^e/ && do {
					if($status) {
						print $clear;
						print "\nMitglied wurde veraendert.\n";
						print "\nSollen die Veraenderungen in die Datenbank uebernommen werden ? (y/n)\n";
						my $eingabe = Verein::Misc::bEingabe(undef,("y","n"));
						$mitgliedObj->changeMitglied() if($eingabe eq "y");
					}
					return;
					last SWITCH;
				};
				print "\nAeh !? $eingabe\n";
			}
		}
    }
    return;
}
###########################################################
sub changeDorfmitglied {
    my $mitgliedObj = shift;

    print $clear;
    print "\n1. Name, Vorname, Nickname\n";
    print "\nMitglieds Nr: ". $mitgliedObj->mitgliedsnr() ."\n";
    Verein::Anzeige::mitglAusgabe([$mitgliedObj]);

    my $name = $mitgliedObj->name();
    my $vorname = $mitgliedObj->vorname();
    my $nickname = $mitgliedObj->nickname();

    $name = Verein::Misc::stdEingabe("Nachname:",$name);
    $vorname = Verein::Misc::stdEingabe("Vorname:",$vorname);
    $nickname = Verein::Misc::stdEingabe("Nickname:",$nickname);

    $mitgliedObj->name($name);
    $mitgliedObj->vorname($vorname);
    $mitgliedObj->nickname($nickname);

    return;
}
###########################################################
sub changeDaten {
    my $mitgliedObj = shift;

    print $clear;
    print "\n2. Misc Daten\n";
    print "\nMitglieds Nr.: ". $mitgliedObj->mitgliedsnr() ."\n";
    my $lines = Verein::Anzeige::mitglAusgabe([$mitgliedObj],0);
    Verein::Anzeige::miscAusgabe($mitgliedObj,$lines);

    my $intern = $mitgliedObj->internATlist();
    my $ccc = $mitgliedObj->cccATlist();
    my $shell = $mitgliedObj->shellzugang();
    my $eintrittsdatum = $mitgliedObj->eintrittsdatum();
    my $chaosnr = $mitgliedObj->chaosnr();
    my $mailb = $mitgliedObj->mailbox();

    $intern = Verein::Misc::stdEingabe("intern\@chaosdorf.de (Email):", $intern);
    $ccc = Verein::Misc::stdEingabe("inter\@list.ccc.de (Email):", $ccc);
    $shell = Verein::Misc::stdEingabe("Shell Zugang (Username):", $shell);
    $eintrittsdatum = Verein::Misc::datumEingabe("Eintrittsdatum: (dd.mm.yyyy)", $eintrittsdatum);
    $chaosnr = Verein::Misc::stdEingabe("ChaosNr.:", $chaosnr);
    $mailb = Verein::Misc::stdEingabe("Email Adr. Chaosdorf (Mailboxname):", $mailb);

    $mitgliedObj->internATlist($intern);
    $mitgliedObj->cccATlist($ccc);
    $mitgliedObj->shellzugang($shell);
    $mitgliedObj->eintrittsdatum($eintrittsdatum);
    $mitgliedObj->chaosnr($chaosnr);
    $mitgliedObj->mailbox($mailb);

    return;
}
###########################################################
sub changeInfo {
    my $mitgliedObj = shift;

    print $clear;
    print "\n8. Info\n";
    print "\nMitglieds Nr.: ". $mitgliedObj->mitgliedsnr() ."\n";

    my @newInfo = Verein::Misc::infoEingabe($mitgliedObj->info());
    $mitgliedObj->info("@newInfo");

    return;
}
###########################################################
sub changeAdresse {
    my $mitgliedObj = shift;

    print $clear;
    print "\n3. Adresse\n";
    print "\nMitglieds Nr.: ". $mitgliedObj->mitgliedsnr() ."\n";
    Verein::Anzeige::adressAusgabe($mitgliedObj);
    print "n Neue Adresse hinzufuegen\n";
    print "\nWelche Adresse soll geraendert werden";

    my @zeichen = ("n");
    my $eingabe = Verein::Misc::bEingabe($mitgliedObj->anzahlAdressen(),@zeichen);

    if($eingabe eq "n") {
		print "\nNeue Adresse hinzufuegen ...\n";
		${$mitgliedObj->adresse()}->strasse(Verein::Misc::stdEingabe("Strasse:"));
		${$mitgliedObj->getadressObj()}->plz(Verein::Misc::stdEingabe("PLZ:"));
		${$mitgliedObj->getadressObj()}->ort(Verein::Misc::stdEingabe("Ort:"));
    } else {
		my $strasse = ${$mitgliedObj->getadressObj($eingabe)}->strasse();
		my $plz = ${$mitgliedObj->getadressObj($eingabe)}->plz();
		my $ort = ${$mitgliedObj->getadressObj($eingabe)}->ort();

		$strasse = Verein::Misc::stdEingabe("Strasse:",$strasse);
		$plz = Verein::Misc::stdEingabe("PLZ:",$plz);
		$ort = Verein::Misc::stdEingabe("Ort:",$ort);

		${$mitgliedObj->getadressObj($eingabe)}->strasse($strasse);
		${$mitgliedObj->getadressObj($eingabe)}->plz($plz);
		${$mitgliedObj->getadressObj($eingabe)}->ort($ort);
    }

    return;
}
###########################################################
sub changeKonto {
    my $mitgliedObj = shift;
    my @zeichen = ("y","n", "1", "0");

    print $clear;
    print "\n5. Kontodaten\n";
    print "\nMitglieds Nr.: ". $mitgliedObj->mitgliedsnr() ."\n";
    Verein::Anzeige::kontoAusgabe($mitgliedObj);
    my $einzug = $mitgliedObj->einzug();
	if($einzug) {
		$einzug = "y";
	} else {
		$einzug = "n";
	}
    print "Einzug von diesem Konto: $einzug\n";

	my $kontonr = "0";
	my $bank = "-";
	my $blz = "0";
	if($mitgliedObj->getkontoObj(0)) {
    	$kontonr = ${$mitgliedObj->getkontoObj(0)}->kontonummer();
    	$bank = ${$mitgliedObj->getkontoObj(0)}->bank();
    	$blz = ${$mitgliedObj->getkontoObj(0)}->bankleitzahl();
	}
    $kontonr = Verein::Misc::stdEingabe("KontoNr.:",$kontonr);
    $bank = Verein::Misc::stdEingabe("Bank:",$bank);
    $blz = Verein::Misc::stdEingabe("BLZ:",$blz);
    $einzug = Verein::Misc::boolEingabe("Einzug: (y/n)",\@zeichen, $einzug);

    $mitgliedObj->einzug($einzug);
    if($kontonr) {
		$mitgliedObj->konto() unless($mitgliedObj->getkontoObj());
		${$mitgliedObj->getkontoObj(0)}->kontonummer($kontonr);
	    ${$mitgliedObj->getkontoObj(0)}->bank($bank);
	    ${$mitgliedObj->getkontoObj(0)}->bankleitzahl($blz);
    }
    return;
}
###########################################################
sub changeBeitrag {
    my $mitgliedObj = shift;

    print $clear;
    print "\n6. Beitrag\n";
    print "\nMitglieds Nr.: ". $mitgliedObj->mitgliedsnr() ."\n";
    Verein::Anzeige::beitragAusgabe($mitgliedObj);
    print "n Neuen Beitrag fuer Mitglied fest setzen\n";

    print "\nWelche Zeile soll Veraendert werden";
    my @zeichen = ("n");
    my $eingabe = Verein::Misc::bEingabe($mitgliedObj->anzahlBeitrag(),@zeichen);

    if($eingabe eq "n") {
		${$mitgliedObj->beitrag()}->beitrag(Verein::Misc::stdEingabe("Beitrag:"));
		${$mitgliedObj->getbeitragObj()}->spende(Verein::Misc::stdEingabe("Spende:"));
		${$mitgliedObj->getbeitragObj()}->schulden(Verein::Misc::stdEingabe("Schulden:"));
		${$mitgliedObj->getbeitragObj()}->datum(Verein::Misc::datumEingabe("Datum: (dd.mm.yyyy)"));
		my @newInfo = Verein::Misc::infoEingabe();
		${$mitgliedObj->getbeitragObj()}->info("@newInfo");
    } else {
		my $beitrag = ${$mitgliedObj->getbeitragObj($eingabe)}->beitrag();
		my $spende = ${$mitgliedObj->getbeitragObj($eingabe)}->spende();
		my $schulden = ${$mitgliedObj->getbeitragObj($eingabe)}->schulden();
		my $datum = ${$mitgliedObj->getbeitragObj($eingabe)}->datum();
		my $info = ${$mitgliedObj->getbeitragObj($eingabe)}->info();

		$beitrag = Verein::Misc::stdEingabe("Beitrag:",$beitrag);
		$spende = Verein::Misc::stdEingabe("Spende:",$spende);
		$schulden = Verein::Misc::stdEingabe("Schulden:",$schulden);
		$datum = Verein::Misc::datumEingabe("Datum: (dd.mm.yyyy)",$datum);
		my @newInfo = Verein::Misc::infoEingabe($info);

		${$mitgliedObj->getbeitragObj($eingabe)}->beitrag($beitrag);
		${$mitgliedObj->getbeitragObj($eingabe)}->spende($spende);
		${$mitgliedObj->getbeitragObj($eingabe)}->schulden($schulden);
		${$mitgliedObj->getbeitragObj($eingabe)}->datum($datum);
		${$mitgliedObj->getbeitragObj($eingabe)}->info("@newInfo");
    }
    return;
}
###########################################################
sub changeSaldo {
    my $mitgliedObj = shift;

    print $clear;
    print "\n7. Saldo\n";
    print "\nMitglieds Nr.: ". $mitgliedObj->mitgliedsnr() ."\n";
    Verein::Anzeige::saldoAusgabe($mitgliedObj);
    print "n Neuen Saldo fuer Mitglied fest setzen\n";

    print "\nWelche Zeile soll Veraendert werden";
    my @zeichen = ("n");
    my $eingabe = Verein::Misc::bEingabe($mitgliedObj->anzahlSaldo(),@zeichen);

    if($eingabe eq "n") {
		${$mitgliedObj->saldo()}->betrag(Verein::Misc::stdEingabe("Betrag:"));
		${$mitgliedObj->getsaldoObj()}->datum(Verein::Misc::datumEingabe("Datum: (dd.mm.yyyy"));
		${$mitgliedObj->getsaldoObj()}->bezeichnung(Verein::Misc::stdEingabe("Bezeichnung:"));
		${$mitgliedObj->getsaldoObj()}->konto(Verein::Misc::konto($dbhobj));
		${$mitgliedObj->getsaldoObj()}->barkonto(Verein::Misc::barkonto($dbhobj));
		my @newInfo = Verein::Misc::infoEingabe();
		${$mitgliedObj->getsaldoObj()}->info("@newInfo");
    } else {
		my $saldo = ${$mitgliedObj->getsaldoObj($eingabe)}->betrag();
		my $datum = ${$mitgliedObj->getsaldoObj($eingabe)}->datum();
		my $info = ${$mitgliedObj->getsaldoObj($eingabe)}->bezeichnung();
		my $konto = ${$mitgliedObj->getsaldoObj($eingabe)}->konto();
		my $barkonto = ${$mitgliedObj->getsaldoObj($eingabe)}->barkonto();
		my $info2 = ${$mitgliedObj->getsaldoObj($eingabe)}->info();

		$saldo = Verein::Misc::stdEingabe("Betrag:",$saldo);
		$datum = Verein::Misc::datumEingabe("Datum: (dd.mm.yyyy",$datum);
		$info = Verein::Misc::stdEingabe("Bezeichnung:",$info);
		$konto = Verein::Misc::konto($dbhobj, $konto);
		$barkonto = Verein::Misc::barkonto($dbhobj, $barkonto);
		my @newInfo = Verein::Misc::infoEingabe($info2);

		${$mitgliedObj->getsaldoObj($eingabe)}->betrag($saldo);
		${$mitgliedObj->getsaldoObj($eingabe)}->datum($datum);
		${$mitgliedObj->getsaldoObj($eingabe)}->bezeichnung($info);
		${$mitgliedObj->getsaldoObj($eingabe)}->konto($konto);
		${$mitgliedObj->getsaldoObj($eingabe)}->barkonto($barkonto);
		${$mitgliedObj->getsaldoObj($eingabe)}->info("@newInfo");
    }
    return;
}
###########################################################
sub changeKommunikation {
    my $mitgliedObj = shift;

    print $clear;
    print "\n4. Email Adr.\n";
    print "\nMitglieds Nr.: ". $mitgliedObj->mitgliedsnr() ."\n";
    Verein::Anzeige::kommAusgabe($mitgliedObj);
    print "n Neue Emailadr\n";

    print "\nWelche Zeile soll Veraendert werden";
    my @zeichen = ("n");
    my $eingabe = Verein::Misc::bEingabe($mitgliedObj->anzahlKomm(),@zeichen);

    if($eingabe eq "n") {
		print "\nNeue Kommunikationsdaten hinzufuegen ... \n";
		${$mitgliedObj->kommunikation()}->email(Verein::Misc::stdEingabe("Email Adr.:"));
#		${$mitgliedObj->getkommObj()}->pubkey(Verein::Misc::schluesselAuswaehlen());
    } else {
		my $email = ${$mitgliedObj->getkommObj($eingabe)}->email();
		$email = Verein::Misc::stdEingabe("Email Adr.:",$email);
		${$mitgliedObj->getkommObj($eingabe)}->email($email);
#		${$mitgliedObj->getkommObj($eingabe)}->pubkey(Verein::Misc::schluesselAuswaehlen());
    }
    return;
}

###########################################################
## Loeschen
###########################################################
sub deletemit {
}

###########################################################
## Ende
###########################################################
sub ende {
    print "\nBye\n";
    exit(0);
}

sub usage {
    print "Optionen:\n";
    print " -h | help                Diese Hilfe\n";
    print " -dbserver [server]       Datenbankserver (Default:localhost)\n";
    exit;
}
