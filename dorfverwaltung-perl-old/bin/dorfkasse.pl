#!/usr/bin/perl -w
#
# Funktion: Die Dorf Kasse
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/dorfkasse.pl,v 1.3 2006/06/06 20:17:37 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: dorfkasse.pl,v $
# Revision 1.3  2006/06/06 20:17:37  jboehme
# - BUGFIX: Die Option -dbserver Hostname wird als Datenbank Verbindung zum Hostname benutzt
#
# Revision 1.2  2005/09/11 21:51:50  jboehme
# - Erweiterung: Die Monatseinzuege werden mit den "Schulden" erweitert
# - Erweiterung: Es kann entschieden werden ob gebucht wird oder nur eine DTAUS
#   Datei erstellt wird.
# - Ausbesserung: Fehler in der Datenbank werden abgefangen.
# - Nur die "Lastschriften" werden sofort "gebucht"
# - Die Buchungen auf die Konten werden erst bei Eingang des Geldes gebucht.
#
# Revision 1.1  2005/09/04 19:01:57  jboehme
# Initial Revision
# Erste lauffaehige Version
#
#-------------------------------------------------------------------------------------------------
#
#

use lib('../pmodule');
use strict;
use Getopt::Long;
use Date::Manip;
use Term::Cap;
use Term::ReadKey;
use Term::ReadLine;
use File::Temp qw/tempfile/;
use Finance::DTAUS;
use Finance::SWIFT::MT940;
use Verein::BuchDB;
use Verein::Datenbank;
use Verein::Mitglied;
use Verein::DeEncrypt;
use Verein::Misc;
use Verein::Anzeige;

my($dbhobj,$gpgObj); # Globale Objekte
Date_Init("Language=German","DateFormat=nonUS");

my $glob_from = 'Chaosdorf Vorstand <vorstand@chaosdorf.de>';
my $glob_lname = "Chaos Computer Club Duesseldorf / Chaosdorf e.V.";
my $glob_name = "Chaosdorf e.V.";
my $glob_kontonr = "21057476";
my $glob_blz = "300 501 10";
my $glob_bank = "Stadtsparkasse Duesseldorf";

$SIG{INT} = \&hauptmenue;

my ($host, $debug, $help, $env_db_user, $env_db_passwd);
GetOptions('dbserver=s' => \$host,
		   'debug=s' => \$debug,
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
}
else {
    $clear = $terminal->Tputs('cl',1);
}

###########################################################
## Einloggen
###########################################################
print $clear;
my $user = $ENV{'USER'};
eval {
	$dbhobj = Verein::Datenbank->new($user,"", $host);
};
if($@) {
	print $@;
	exit;
}
$dbhobj->debug($debug) if($debug);

hauptmenue();


###########################################################
## Haupt-Menue
###########################################################
sub hauptmenue
{
	while (1) {
		print $clear;
		print "\nMenue:\n\n";
		print "1. Monats Einzug\n";
		print "2. Umsaetze Einlesen\n";
		print "3. Umsaetze Scannen\n";
		print "4. Umsaetze Anzeigen\n";
		print "5. Saldo fuer Mitglied errechnen\n";
#		print "2. Neues Saldo fuer Mitglied eingeben\n";
#		print "3. Saldo fuer Mitglied aendern\n";
		print "e Ende\n\n";
		my $eingabe = Verein::Misc::zEingabe();

		foreach($eingabe) {
		  SWITCH: {
				/^1/ && do {
					monatsEinzuege();
					last SWITCH;
				};
				/^2/ && do {
					umsEinlesen();
					last SWITCH;
				};
				/^3/ && do {
					umsScan(undef);
					last SWITCH;
				};
				/^4/ && do {
					umsAnzeigen();
					last SWITCH;
				};
				/^5/ && do {
					saldoRechnen();
					last SWITCH;
				};
#				/^2/ && do {
#					newSaldo();
#					last SWITCH;
#				};
#				/^3/ && do {
#					changeSaldo();
#					last SWITCH;
#				};
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
sub umsScan
{
	my ($transActionId) = @_;

	my ($refBuchungen, $buchungsDB, $objDB);
	eval {
		$objDB = new Verein::Datenbank($user,"",$host);
		$buchungsDB = new Verein::BuchDB($user,"",$host);
	};
	if($@ || $buchungsDB->isError()) {
		print "$@\n";
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		return;
	}
	$buchungsDB->debug($debug) if($debug);
	$objDB->debug($debug) if($debug);

	if(!$transActionId) {
		my $refTRXIDs = $buchungsDB->getTRXID();
		my $error = 1;
		do {
			print "\n\nTRX IDs: ";
			foreach my $trxID (@{$refTRXIDs}) { print ${$trxID}[0] ." "; }
			print "\nWelche TRX ID soll gescannt werden ? (q = quit)";
			$transActionId = Verein::Misc::bEingabe();
			if($transActionId eq "q") { return; }
		  LOOP: foreach my $trxID (@{$refTRXIDs}) {
				if($transActionId eq ${$trxID}[0]) {
					$error = 0;
					last;
				}
			}
		} while($error);
	}

	eval {
		$refBuchungen = $buchungsDB->getBuchungen($transActionId);
	};
	if($@ || $buchungsDB->isError()) {
		print "$@\n";
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		return;
	}

	my ($gpgpassword);
	foreach my $daten (@{$refBuchungen}) {
		my $kasse_pkey = $$daten[0];
		my $valutadatum = $$daten[1];
		my $shkenn = $$daten[2];
		my $betrag = $$daten[3];
		my $fremdname = $$daten[4];
		my $bezeichnung = $$daten[5];
		my $bankbuschl = $$daten[6];
		my $fremdblz = $$daten[7];
		my $fremdktnr = $$daten[8];

		my $objMitglied = new Verein::Mitglied($objDB);

		my $mail = 0;
		my $bankschlName = "-";
		$_ = $bankbuschl;
	  SWITCH: {
			/^5$/ && do {
				$bankschlName = "Lastschrift Einzugsermaechtigung";
				last SWITCH;
			};

			/^6$/ && do {
				$bankschlName = "Sonstige Einzugspapiere";
				last SWITCH;
			};

			/^8$/ && do {
				$bankschlName = "Dauerauftrag Belastung";
				last SWITCH;
			};

			/^9$/ && do {
				$bankschlName = "Ruecklastschrift DTA";
				$objMitglied->searchKto($fremdktnr,$fremdblz);
				$mail = 1;
				last SWITCH;
			};

			/^11$/ && do {
				$bankschlName = "Euroscheck";
				last SWITCH;
			};

			/^51$/ && do {
				$bankschlName = "Ueberweisungsgutschrift";
				$objMitglied->searchKto($fremdktnr,$fremdblz);
				unless($objMitglied->mitgliedsnr()) {
					$objMitglied->searchName($fremdname);
				}
				unless($objMitglied->mitgliedsnr()) {
					$objMitglied->searchBez($bezeichnung);
				}
				last SWITCH;
			};

			/^52$/ && do {
				$bankschlName = "Dauerauftrag-Gutschrift";
				$objMitglied->searchKto($fremdktnr,$fremdblz);
				unless($objMitglied->mitgliedsnr()) {
					$objMitglied->searchName($fremdname);
				}
				unless($objMitglied->mitgliedsnr()) {
					$objMitglied->searchBez($bezeichnung);
				}
				last SWITCH;
			};

			/^71$/ && do {
				$bankschlName = "Lastschrifteinreichung";
				$objMitglied->searchKto($fremdktnr,$fremdblz);
				unless($objMitglied->mitgliedsnr()) {
					$objMitglied->searchName($fremdname);
				}
				unless($objMitglied->mitgliedsnr()) {
					$objMitglied->searchBez($bezeichnung);
				}
				last SWITCH;
			};

			/^805$/ && do {
				$bankschlName = "Abschluss";
				last SWITCH;
			};

			/^820$/ && do {
				$bankschlName = "Uebertrag";
				$objMitglied->searchBez($bezeichnung);
				last SWITCH;
			};

			print "=============================================================================\n";
			print "Neuer Buchungsschluessel $_ gefunden !\n";
			print "Buchungschluessel kann nicht zugeordnet werden\n";
			print "-------------------- Buchung ------------------------------------------------\n";
			print "Pkey: ". $kasse_pkey ."\n";
			print "Valuta Datum: ". $valutadatum ."\n";
			print "SH-Kennung: ". $shkenn ."\n";
			print "Betrag: ". $betrag ."\n";
			print "Bank Name: ". $fremdname ."\n";
			print "Bez.: ". $bezeichnung ."\n";
			print "Bank Schl.: ". $bankbuschl ."\n";
			print "BLZ: ". $fremdblz ."\n";
			print "KontoNr: ". $fremdktnr ."\n";
			print "=============================================================================\n";

		}
		if($objMitglied->mitgliedsnr()) {
			my $mitgliedObj = Verein::Mitglied->new($dbhobj,$objMitglied->mitgliedsnr());
			print "\nMitglied:\n";
			print "Nr:      ". $mitgliedObj->mitgliedsnr() ."\n";
			print "Name:    ". $mitgliedObj->name() ."\n";
			print "Vorname: ". $mitgliedObj->vorname() ."\n";
			print "\nUmsatzdaten:\n";
			print "Valuta Datum: " . $valutadatum ."\n";
			print "Betrag: ". $shkenn ." ". $betrag ."\n";
			print "Bezeichnung: ". $bezeichnung ."\n";
			print "\nKonto Daten:\nName: ". $fremdname ."\n";
			print "BLZ: ". $fremdblz ."\n";
			print "Konto Nr.: ". $fremdktnr ."\n";
			print "\nBank Schluessel ". $bankbuschl ." => ". $bankschlName ."\n";

			print "\nSoll die Buchung auf das Mitgliedskonto uebertragen werden ? (j/N)\n";
			my $eingabe = Verein::Misc::zEingabe(undef,"j","N",);
			print "\n\n";
			if($eingabe eq "j") {
				$betrag *= -1 if($shkenn eq "debit");

				if($mail) {
					print "\nRuecklastschrift.\nSoll eine Email an das Mitglied verschickt werden ? (j/N)\n";
					my $eingabe = Verein::Misc::zEingabe(undef,"j","N",);
					print "\n\n";
					if($eingabe eq "j") {
						my $subject = "Chaosdorf Mitgliedsbeitrag";
						my $to;
						if($mitgliedObj->getkommObj() && ${$mitgliedObj->getkommObj()}->email()) {
							$to = "". ${$mitgliedObj->getkommObj()}->email() ."";
						} else {
							$to = Verein::Misc::stdEingabe("\nEs gibt kein Email Adresseintrag fuer das Mitglied.Bitte geben Sie eine Email Adresse an:","");
						}				

						my $message = "Hallo ". $mitgliedObj->vorname() ."\n".
						              "leider hat das Lastschrift verfahren nicht bei dir geklappt. Der Beitrag\n".
									  "den wir bei dir abbuchen wollten wurde gebuehrenpflichtig zurueckgebucht.\n".
									  "\n".
									  "Bitte zahle uns den ausstehenden Beitrag zuzueglich der Gebuehren, also\n".
									  "insgesamt ". $betrag ." EUR auf folgendes Konto ein:\n".
									  "\n".
									  "Name: ". $glob_name ."\n".
									  "Konto Nr.: ". $glob_kontonr ."\n".
									  "BLZ: ". $glob_blz ."\n".
									  "Bank: ". $glob_bank ."\n".
									  "\n".
									  "Als Referenz bitte folgendes Eintragen:\n".
									  "Mitgliedsnr ". $mitgliedObj->mitgliedsnr() ."\n".
									  "Mitgliedsbeitrag fuer [Monat eintragen]\n".
									  "\n".
									  "Sollte es Probleme geben, dann wende dich bitte an Chaosdorf Vorstand\n".
									  "". $glob_from ."\n".
									  "\n".
									  "Zu deiner Information hier die Ruecklastschrift der Bank:\n".
									  "Valuta Datum: ". $valutadatum ."\n".
									  "Betrag: ". $betrag ." EUR\n".
									  "". $bezeichnung ."\n".
									  "\n".
									  "\n".
									  "Diese Email wurde automatisch generiert und verschickt\n".
									  "\n";

						print "An:      ". $to ."\n";
						print "Subject: ". $subject ."\n";
						print "Nachricht:\n". $message ."\n";
						print "\nEmail versenden ? (j/N)\n";
						my $eingabe = Verein::Misc::zEingabe(undef,"j","N",);
						print "\n\n";
						if($eingabe eq "j") {

							if(!$gpgpassword) {
								ReadMode('noecho');
								print "\nGnuPG Schluessel Passwort:";
								$gpgpassword = ReadLine(0);
								chomp($gpgpassword);
								ReadMode('normal');
							}
							Verein::Misc::sendEmail($glob_from,$to,$glob_from,$subject,$message,$gpgpassword);
						}
					}
				}

				${$objMitglied->saldo()}->betrag($betrag);
				${$objMitglied->getsaldoObj()}->datum($valutadatum);
				${$objMitglied->getsaldoObj()}->bezeichnung($bezeichnung);
				${$objMitglied->getsaldoObj()}->barkonto($glob_kontonr);
				${$objMitglied->getsaldoObj()}->konto("011");
				${$objMitglied->getsaldoObj()}->info("Automatische Buchung");
				$objMitglied->changeMitglied();
				
				eval {
					$buchungsDB->setErfasst($$daten[0],1);
					$buchungsDB->commit();
				};
				if($@ || $buchungsDB->isError()) {
					print "$@\n";
					print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
					return;
				}
			}
		}
	}
	Verein::Misc::zEingabe(undef,);
	return;
}

###########################################################
sub umsEinlesen
{
	my $datei = Verein::Misc::stdEingabe("Geben Sie den Dateinamen ein:","");
	return if(!$datei || !(-f $datei));

	my $akt_datum = UnixDate("today",'%Y-%m-%d');
	my $mt940Obj = Finance::SWIFT::MT940->new($datei);
	$mt940Obj->einlesen();

	my $x = 0;
	my $bool = 0;
	my ($buchungsDB,$einleseID,@lastbuch,@datums);
	eval {
		$buchungsDB = Verein::BuchDB->new($user,"",$host);
		$buchungsDB->debug($debug) if($debug);
		@lastbuch = $buchungsDB->selectLastBuchung(); # zwshkenn62,zwbudatum62,zwischensaldo62
		@datums = $buchungsDB->selectBuchung(); # valutadatum,buchungsdatum
		$einleseID = $buchungsDB->nextTrxID();
	};
	if($@ || $buchungsDB->isError()) {
		print "$@\n";
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		$buchungsDB->rollback();
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		return;
	}

	my $lastDate = ParseDate($lastbuch[1]);
	print "\nTranksaktionsID: $einleseID\n";

	print "Trans Lines : ". $mt940Obj->transactionLines() ."\n";
	for(; $x <= $mt940Obj->transactionLines(); $x++) {
		my (@balance,$balanceCode,$balanceDate,$flag);
		if($bool == 0) {
			$balanceCode = $mt940Obj->openingBalanceCode($x);
			$balanceDate = ParseDate($mt940Obj->openingBalanceDate($x,"iso8601"));
			@balance = $mt940Obj->openingBalance($x);
			$flag = Date_Cmp($lastDate,$balanceDate);
		}

		if ($bool == 0 && $flag == 0 && (($balance[0] == $lastbuch[2]) || ($balanceCode eq $lastbuch[0]))) {
			my $valDat = ParseDate($mt940Obj->valueDate($x,0,"iso8601"));
			my $buchDat = ParseDate($mt940Obj->entryDate($x,0,"iso8601"));

			my $flag2 = Date_Cmp($datums[0],$valDat);

			$flag2 = Date_Cmp($datums[1],$buchDat) if($flag2 == 0);

			if($flag2 < 0) {
				$bool = 1;
			}
		}

		if ($bool || ($flag < 0) || ($flag == 0 && (($balance[0] != $lastbuch[2]) || ($balanceCode ne $lastbuch[0])))) {
			if($bool == 0) {
				$bool = 1;
			}
			$buchungsDB->insertMT940($akt_datum,$einleseID,$mt940Obj,$x);

			if($buchungsDB->isError()) {
				print "$@\n";
				print "". $buchungsDB->getError() ."\n";
				$buchungsDB->rollback();
				print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
				return;
			}
		}

		if($bool) {
			print ".";
		} else {
			print "-";
		}
	}

	eval {
		$buchungsDB->commit();
	};
	if($@ || $buchungsDB->isError()) {
		print "$@\n";
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		$buchungsDB->rollback();
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		return;
	}

	print "\nMoechten Sie die Buchungen mit der TranksaktionsID: $einleseID Scannen? (j/N)\n";
	my $eingabe = Verein::Misc::zEingabe(undef,"j","N",);
	print "\n\n";

	umsScan($einleseID) if($eingabe eq "j");

	return;
}

###########################################################
sub monatsEinzuege
{
    print $clear;
    print "DTAUS anfertigen ...\n";

    my $datum = "heute";
    my $monat = UnixDate(ParseDate("$datum"), '%b');

    $monat = Verein::Misc::stdEingabe("Fuer den Monat","$monat");

	print "\nMit Buchungen (J/n). Mit n wird nur eine DTAUS Datei erstellt.\n";
	my $mitBuchung = Verein::Misc::zEingabe(undef,"J","n",);
	print "\n\n";

    my @mitgliederObj = $dbhobj->selectMitglieder();

    my $dta = Finance::DTAUS->new();

    $dta->auftrgbName($glob_name);
    $dta->auftrgbNameLang($glob_lname);
    $dta->auftrgbKontnr($glob_kontonr);
    $dta->baBLZ($glob_blz);

    $dta->ausfDatum($datum);

    my $x = 0;
    for my $mgObj (@mitgliederObj) {
		my $mitgliedObj = Verein::Mitglied->new($dbhobj,$mgObj->mitgliedsnr());
		print ".";

		my $bez = "Mitgliedsbeitrag";
		my $mitgliedsNr = $mitgliedObj->mitgliedsnr();
		my ($beitrag,$spende,$schulden);

		eval {
			$beitrag = ${$mitgliedObj->getbeitragObj()}->beitrag();
			$spende = ${$mitgliedObj->getbeitragObj()}->spende();
			$schulden = ${$mitgliedObj->getbeitragObj()}->schulden();
		};

		if($@) {
			print "\nERROR:\nFehler in der Mitgliederdatenbank\n";
			print "Es gibt keinen Beitrags Eintrag fuer Mitglied $mitgliedsNr\n";
		    print "Name: ". ($mitgliedObj->name() ? $mitgliedObj->name() : "-") ."\n";
			print "Vorname: ".($mitgliedObj->vorname() ? $mitgliedObj->vorname() : "-") ."\n";
			next;
		}

		if($mitBuchung eq "J") {
			my $betrag = 0 - $beitrag;
			${$mitgliedObj->saldo()}->betrag($betrag);
			${$mitgliedObj->getsaldoObj()}->datum($datum);
			${$mitgliedObj->getsaldoObj()}->bezeichnung($bez ." ". $monat);
			${$mitgliedObj->getsaldoObj()}->info("Automatische Monats Abbuchung ");

			if($spende && $spende * 1) {
				my $betrag = 0 - $spende;
				${$mitgliedObj->saldo()}->betrag($betrag);
				${$mitgliedObj->getsaldoObj()}->datum($datum);
				${$mitgliedObj->getsaldoObj()}->bezeichnung("Spende ". $monat);
				${$mitgliedObj->getsaldoObj()}->info("Automatische Monats Abbuchung ");
			}
		}

		if($mitgliedObj->einzug()) {
			my $bezeichnung = "";
			my $betrag = $beitrag;

			if($spende && $spende * 1) {
				$bezeichnung .= "u. Spende ";
				$betrag += $spende;
			}

			if($schulden && $schulden * 1) {
				$bezeichnung .= "u. Schulden ";
				$betrag += $schulden;
			}

			$dta->textschl($x,"Last-Einzug");
			$dta->empfName($x,"". $mitgliedObj->name() .",". $mitgliedObj->vorname() ."");
			$dta->empfKontonr($x,"". ${$mitgliedObj->getkontoObj()}->kontonummer() ."");
			$dta->empfBLZ($x,"". ${$mitgliedObj->getkontoObj()}->bankleitzahl() ."");
			$dta->betrag($x,"$betrag");
			$dta->verwendungszweck($x,"$mitgliedsNr $bez $bezeichnung$monat");
			$x++;

			if($mitBuchung eq "J") {
				${$mitgliedObj->saldo()}->betrag($beitrag);
				${$mitgliedObj->getsaldoObj()}->datum($datum);
				${$mitgliedObj->getsaldoObj()}->bezeichnung($bez ." ". $monat);
				${$mitgliedObj->getsaldoObj()}->barkonto($glob_kontonr);
				${$mitgliedObj->getsaldoObj()}->konto("011");
				${$mitgliedObj->getsaldoObj()}->info("Automatische Monats Lastschrift");

				if($spende && $spende * 1) {
					${$mitgliedObj->saldo()}->betrag($spende);
					${$mitgliedObj->getsaldoObj()}->datum($datum);
					${$mitgliedObj->getsaldoObj()}->bezeichnung("Spende ". $monat);
					${$mitgliedObj->getsaldoObj()}->barkonto($glob_kontonr);
					${$mitgliedObj->getsaldoObj()}->konto("012");
					${$mitgliedObj->getsaldoObj()}->info("Automatische Monats Lastschrift");
				}

				if($schulden && $schulden * 1) {
					${$mitgliedObj->saldo()}->betrag($schulden);
					${$mitgliedObj->getsaldoObj()}->datum($datum);
					${$mitgliedObj->getsaldoObj()}->bezeichnung("Schulden ". $bez ." ". $monat);
					${$mitgliedObj->getsaldoObj()}->barkonto($glob_kontonr);
					${$mitgliedObj->getsaldoObj()}->konto("011");
					${$mitgliedObj->getsaldoObj()}->info("Automatische Monats Lastschrift");
				}
			}
		}

		$mitgliedObj->changeMitglied();
    }

    $dta->getDTAUS();

    print " Fertig.\n";
    Verein::Misc::zEingabe();

    return;
}

###########################################################
# Change / Aenderung ######################################

sub change {
    print "\nMitgliedsaenderung\n";
    my $mitgliedNr = mitanz();
    return unless($mitgliedNr);
    my $mitgliedObj = Verein::Mitglied->new($dbhobj,$gpgObj);
    $mitgliedObj->getMitglied($mitgliedNr);
    return($mitgliedObj);
}

###########################################################
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
sub changeSaldo
{
    my $mitgliedObj = change();
	return unless($mitgliedObj);

    print $clear;
    print "\n7. Saldo\n"
	     ." NR:         ". $mitgliedObj->mitgliedsnr()
		 ."\n Vorname:  ". $mitgliedObj->vorname()
		 ."\n Name:     " . $mitgliedObj->name()
		 ."\n Nickname: " . $mitgliedObj->nickname()
		 ."\n\n";

    Verein::Anzeige::saldoAusgabe($mitgliedObj);

    print "\nWelche Zeile soll Veraendert werden";
    my @zeichen = ();
    my $eingabe = Verein::Misc::bEingabe($mitgliedObj->anzahlSaldo(),@zeichen);

    my $saldo = ${$mitgliedObj->getsaldoObj($eingabe)}->betrag();
    my $datum = ${$mitgliedObj->getsaldoObj($eingabe)}->datum();
    my $info = ${$mitgliedObj->getsaldoObj($eingabe)}->bezeichnung();
    my $konto = ${$mitgliedObj->getsaldoObj($eingabe)}->konto();
    my $barkonto = ${$mitgliedObj->getsaldoObj($eingabe)}->barkonto();
    my $info2 = ${$mitgliedObj->getsaldoObj($eingabe)}->info();

    $saldo = Verein::Misc::stdEingabe("Betrag:",$saldo);
    $datum = Verein::Misc::datumEingabe("Datum: (dd.mm.yyyy)",$datum);
    $info = Verein::Misc::stdEingabe("Bezeichnung:",$info);
    $konto = Verein::Misc::konto($konto);
    $barkonto = Verein::Misc::barkonto($barkonto);
    my @newInfo = Verein::Misc::infoEingabe($info2);

    ${$mitgliedObj->getsaldoObj($eingabe)}->betrag($saldo);
    ${$mitgliedObj->getsaldoObj($eingabe)}->datum($datum);
    ${$mitgliedObj->getsaldoObj($eingabe)}->bezeichnung($info);
    ${$mitgliedObj->getsaldoObj($eingabe)}->konto($konto);
    ${$mitgliedObj->getsaldoObj($eingabe)}->barkonto($barkonto);
    ${$mitgliedObj->getsaldoObj($eingabe)}->info("@newInfo");

    return;
}

###########################################################
sub newSaldo
{
    my $mitgliedObj = change();
	return unless($mitgliedObj);

    print $clear;
    print "\n7. Saldo\n"
	     ." NR:         ". $mitgliedObj->mitgliedsnr()
		 ."\n Vorname:  ". $mitgliedObj->vorname()
		 ."\n Name:     " . $mitgliedObj->name()
		 ."\n Nickname: " . $mitgliedObj->nickname()
		 ."\n\n";

    Verein::Anzeige::saldoAusgabe($mitgliedObj);

    print "Neues Saldo eingeben:\n\n";

    ${$mitgliedObj->saldo()}->betrag(Verein::Misc::stdEingabe("Betrag:"));
    ${$mitgliedObj->getsaldoObj()}->datum(Verein::Misc::datumEingabe("Datum: (dd.mm.yyyy"));
    ${$mitgliedObj->getsaldoObj()}->bezeichnung(Verein::Misc::stdEingabe("Bezeichnung:"));
    ${$mitgliedObj->getsaldoObj()}->konto(Verein::Misc::konto());
    ${$mitgliedObj->getsaldoObj()}->barkonto(Verein::Misc::barkonto());
    my @newInfo = Verein::Misc::infoEingabe();
    ${$mitgliedObj->getsaldoObj()}->info("@newInfo");

    return;
}

###########################################################
## Saldo fuer Mitglieder Berechnen
###########################################################
sub saldoRechnen {
   	print "\n5. Saldo\n";
	my ($buchungsDB,$gpgpassword);
	
    my @mitgliederObj = $dbhobj->selectMitglieder();

	eval {
		$buchungsDB = Verein::BuchDB->new($user,"",$host);
	};
	if($@ || $buchungsDB->isError()) {
		print "$@\n";
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		$buchungsDB->rollback();
		print "". $buchungsDB->getError() ."\n" if($buchungsDB->isError());
		return;
	}

	for my $mgObj (@mitgliederObj) {
		my $mitgliedObj = Verein::Mitglied->new($dbhobj,$mgObj->mitgliedsnr());
		print "\n\n\n---------------------------------------------------------------------------------------------------\n";
	    print " NR:       ". $mitgliedObj->mitgliedsnr() ."\n";
		print " Vorname:  ". $mitgliedObj->vorname() ."\n";
		print " Name:     " . $mitgliedObj->name() ."\n";
		print " Nickname: " . ($mitgliedObj->nickname() ? $mitgliedObj->nickname() : "-") ."\n";
		print "\n\n";

		my $mitgliedsNr = $mitgliedObj->mitgliedsnr();
		my $sum = $buchungsDB->beitragSum($mitgliedsNr);
		
		print "Summe: ". $sum ."\n============\n";

		if($sum < 0) {
			my $betrag = $sum * -1;
			print "\nSchulden.\nSoll eine Email an das Mitglied verschickt werden ? (j/N)\n";
			my $eingabe = Verein::Misc::zEingabe(undef,"j","N",);
			print "\n\n";
			if($eingabe eq "j") {
				my $subject = "Chaosdorf Mitgliedsbeitrag Kontostand";
				my $to;
				if($mitgliedObj->getkommObj() && ${$mitgliedObj->getkommObj()}->email()) {
					$to = "". ${$mitgliedObj->getkommObj()}->email() ."";
				} else {
					$to = Verein::Misc::stdEingabe("\nEs gibt kein Email Adresseintrag fuer das Mitglied.Bitte geben Sie eine Email Adresse an:","");
				}				
				my $message = "Hallo ". $mitgliedObj->vorname() ."\n".
							  "leider weist dein Mitlgiedskontostand ein Sollwert von ". $sum ." auf.".
							  "\n".
							  "Bitte zahle uns den ausstehenden Beitrag von ". $betrag ." EUR auf\n".
							  "folgendes Vereins Konto ein:\n".
							  "\n".
							  "Name: ". $glob_name ."\n".
							  "Konto Nr.: ". $glob_kontonr ."\n".
							  "BLZ: ". $glob_blz ."\n".
							  "Bank: ". $glob_bank ."\n".
							  "\n".
							  "Als Referenz bitte folgendes Eintragen:\n".
							  "Mitgliedsnr, dein Vorname und Nachname Mitgliedsschulden\n".
							  "Also deine Referenz:\n".
							  $mitgliedObj->mitgliedsnr() ." ". $mitgliedObj->vorname() ." ". $mitgliedObj->name() ." Mitgliedsschulden\n\n".
							  "Sollte es Probleme oder Fragen geben, dann wende dich bitte\n".
							  "schnellstmoeglich an den Chaosdorf Vorstand\n".
							  "". $glob_from ."\n".
							  "\n".
							  "Diese Email wurde automatisch generiert und verschickt\n".
							  "\n";

				print "An:      ". $to ."\n";
				print "Subject: ". $subject ."\n";
				print "Nachricht:\n". $message ."\n";
				print "\nEmail versenden ? (j/N)\n";
				my $eingabe = Verein::Misc::zEingabe(undef,"j","N",);
				print "\n\n";
				if($eingabe eq "j") {
					if(!$gpgpassword) {
						ReadMode('noecho');
						print "\nGnuPG Schluessel Passwort:";
						$gpgpassword = ReadLine(0);
						chomp($gpgpassword);
						ReadMode('normal');
					}
					Verein::Misc::sendEmail($glob_from,$to,$glob_from,$subject,$message,$gpgpassword);
				}
			}
		}
	}		
}

###########################################################
## Ende
###########################################################
sub ende {
    print "\nBye\n";
    exit(0);
}
