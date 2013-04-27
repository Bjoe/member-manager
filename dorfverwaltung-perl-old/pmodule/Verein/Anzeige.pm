#!/usr/bin/perl -w
#
# Funktion: Anzeige Formate
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Anzeige.pm,v 1.3 2005/09/11 21:41:57 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Anzeige.pm,v $
# Revision 1.3  2005/09/11 21:41:57  jboehme
# - Erweiterung: Die Beitragsanzeige wird mit der Spalte "Schulden" erweitert
#
# Revision 1.2  2005/09/04 18:43:24  jboehme
# - Ausbesserung: Die Anzeige von Geldbetraege wird rechtsbuendig
#   ausgerichtet.
# - Ausbesserung in der Beitragsanzeige: Es koennen wahlweise alle
#   Beitraege von einem Mitglied gesehen werden oder nur der Letzte.
# - Erweiterung in der Saldo Anzeige: Die bezeichnung wird mit
#   Angezeigt.
# - BUGFIX: Es werden alle Saldo Eintraege Angezeigt
#
# Revision 1.1  2005/08/11 19:06:45  jboehme
# - Initial Revision
# - Anzeige Funktionen aus dorfverw
#
#-------------------------------------------------------------------------------------------------
#
#

package Verein::Anzeige;

use strict;
sub whowasi { (caller(1))[3] . "()" }

format LEER =
.

my $glob_anzeigeTool = "less";

sub mitglAusgabe {
    my ($mitglieder, $aktLine) = @_;


	eval {
		open(LESS, "| $glob_anzeigeTool") or die
	};
	if($@) {
		print "Error! Kann AnzeigeTool $glob_anzeigeTool nicht oeffnen\n$!";
		return;
	 }

    my ($mitglNr, $vorname, $name, $nickname, $intern, $ccc, $shellAccount, $einzug, $cccev, $mlbox);

format MITGL_TOP =
Mitgl.Nr. Vorname   Name        Nickname   intern ccc Shell EinZug CCCe.V MLBox
-------------------------------------------------------------------------------
.

format MITGLAUSGABE =
@<<<<<<<< @<<<<<<<< @<<<<<<<<<< @<<<<<<<<<  @|||  @||| @||| @|||   @|||    @|||
$mitglNr, $vorname, $name, $nickname, $intern, $ccc, $shellAccount, $einzug, $cccev, $mlbox
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $mitglTop = select(LESS);
    $^ = "LEER";
    $~ = "MITGL_TOP";
    select($mitglTop);
    write(LESS);

    my $mitglAusg = select(LESS);
    $^ = "MITGL_TOP";
    $~ = "MITGLAUSGABE";
    select($mitglAusg);

    for my $mObj (@$mitglieder) {
		$mitglNr = $mObj->mitgliedsnr() ? $mObj->mitgliedsnr() : "-";
		$vorname = $mObj->vorname() ? $mObj->vorname() : "-";
		$name = $mObj->name() ? $mObj->name() : "-";
		$nickname = $mObj->nickname() ? $mObj->nickname() : "-";
		$intern = $mObj->internATlist() ? $mObj->internATlist() : "-";
		$ccc = $mObj->cccATlist() ? $mObj->cccATlist() : "-";
		$shellAccount = $mObj->shellzugang() ? $mObj->shellzugang() : "-";
		$einzug = $mObj->einzug() ? "x" : "-";
		$cccev = $mObj->chaosnr() ? "x" : "-";
		$mlbox = $mObj->mailbox() ? "x" : "-";
		write(LESS);
    }
	close(LESS);

    select(STDOUT);
    print "\n\n";

    return $-;
}

sub adressAusgabe {
    my ($mitgliedObj, $aktLine) = @_;
    my($x, $strasse, $plz, $ort);

format ADRESS_TOP =
Nr.   Strasse                       PLZ     Ort
------------------------------------------------------------
.

format ADRESSAUSGABE =
@<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<< @<<<<<< @<<<<<<<<<<<<<<<
$x,   $strasse,                     $plz,   $ort
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $adressTop = select(STDOUT);
    $^ = "LEER";
    $~ = "ADRESS_TOP";
    select($adressTop);
    write(STDOUT);

    my $adressAusg = select(STDOUT);
    $^ = "ADRESS_TOP";
    $~ = "ADRESSAUSGABE";
    select($adressAusg);

    for($x = 0; $x < $mitgliedObj->anzahlAdressen(); $x++) {
		if(my $adrObj = $mitgliedObj->getadressObj($x)) {
			$strasse = ${$adrObj}->strasse() ? ${$adrObj}->strasse() : "-";
			$plz = ${$adrObj}->plz() ? ${$adrObj}->plz() : "-";
			$ort = ${$adrObj}->ort() ? ${$adrObj}->ort() : "-";
			write(STDOUT);
		}
    }

    select(STDOUT);
    print "\n\n";

    return($-);
}

sub kommAusgabe {
    my ($mitgliedObj, $aktLine) = @_;
    my($x, $email, $schluessel);

format KOMM_TOP =
Nr.  Email Adr.                        GnuPG-Schluessel
--------------------------------------------------------------------------------------------
.

format KOMMAUSGABE =
@<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$x,  $email,                          $schluessel
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $kommTop = select(STDOUT);
    $^ = "LEER";
    $~ = "KOMM_TOP";
    select($kommTop);
    write(STDOUT);

    my $kommAusg = select(STDOUT);
    $^ = "KOMM_TOP";
    $~ = "KOMMAUSGABE";
    select($kommAusg);

    for($x = 0; $x < $mitgliedObj->anzahlKomm(); $x++) {
		if(my $kommObj = $mitgliedObj->getkommObj($x)) {
			$email = ${$kommObj}->email() ? ${$kommObj}->email() : "-";
			$schluessel = ${$kommObj}->pubkey() ? ${$kommObj}->pubkey() : "-";
			write(STDOUT);
		}
    }

    select(STDOUT);
    print "\n\n";

    return($-);
}

sub miscAusgabe {
    my ($mitgliedObj, $aktLine) = @_;
    my($chaosdorfadr, $chaosnr, $eintrittsdatum);

format MISC_TOP =
ChaosNr.    Eintrittsdatum  Chaosdorf Adr.
-------------------------------------------------------------------------------
.

format MISCAUSGABE =
@<<<<<<<<<< @<<<<<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$chaosnr,   $eintrittsdatum,  $chaosdorfadr
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $miscTop = select(STDOUT);
    $^ = "LEER";
    $~ = "MISC_TOP";
    select($miscTop);
    write(STDOUT);

    my $miscAusg = select(STDOUT);
    $^ = "MISC_TOP";
    $~ = "MISCAUSGABE";
    select($miscAusg);

    $chaosdorfadr = $mitgliedObj->mailbox() ? $mitgliedObj->mailbox() : "-";
    $chaosnr = $mitgliedObj->chaosnr() ? $mitgliedObj->chaosnr() : "-";
    $eintrittsdatum = $mitgliedObj->eintrittsdatum() ? $mitgliedObj->eintrittsdatum() : "-";
    write(STDOUT);

    select(STDOUT);
    print "\n\n";

    return $-;
}

sub beitragAusgabe {
    my ($mitgliedObj, $aktLine, $all) = @_;
    my($x, $beitrag, $spende, $datum, $info, $schulden);

format BEITRAG_TOP =
    Beitrag       Spende    Schulden  ab Datum      Info
-------------------------------------------------------------------------
.

format BEITRAGAUSGABE =
@>>>>>>>>>>   @>>>>>>>>>  @>>>>>>>>>  @<<<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<
$beitrag,    $spende,     $schulden,   $datum,       $info
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $beitragTop = select(STDOUT);
    $^ = "LEER";
    $~ = "BEITRAG_TOP";
    select($beitragTop);
    write(STDOUT);

    my $beitragAusg = select(STDOUT);
    $^ = "BEITRAG_TOP";
    $~ = "BEITRAGAUSGABE";
    select($beitragAusg);

    my $anzahl = $mitgliedObj->anzahlBeitrag();
    $anzahl = 1 unless($all);
    for($x = 0 ; $x < $anzahl; $x++) {
		my $beitragObj;
		if($all) {
			$beitragObj = $mitgliedObj->getbeitragObj($x);
		} else {
			$beitragObj = $mitgliedObj->getbeitragObj();
		}
		if($beitragObj) {
			$beitrag = defined ${$beitragObj}->beitrag() ? ${$beitragObj}->beitrag() : "-";
			$spende = defined ${$beitragObj}->spende() ? ${$beitragObj}->spende() : "-";
			$schulden = defined ${$beitragObj}->schulden() ? ${$beitragObj}->schulden() : "-";
			$datum = ${$beitragObj}->datum() ? ${$beitragObj}->datum() : "-";
			$info = ${$beitragObj}->info() ? ${$beitragObj}->info() : "-";
			write(STDOUT);
		}
    }

    select(STDOUT);
    print "\n\n";

    return $-;
}

sub saldoAusgabe {
    my ($mitgliedObj, $aktLine) = @_;

	eval {
		open(LESS, "| $glob_anzeigeTool") or die
	};
	if($@) {
		print "Error! Kann AnzeigeTool $glob_anzeigeTool nicht oeffnen\n$!";
		return;
	 }

    my($x, $saldo, $datum, $bezeichnung, $info);

format SALDO_TOP =
Saldo        Datum         Bezeichnung            Info
---------------------------------------------------------------------------
.

format SALDOAUSGABE =
@>>>>>>>>>   @<<<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<
$saldo,      $datum,       $bezeichnung,          $info
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $beitragTop = select(LESS);
    $^ = "LEER";
    $~ = "SALDO_TOP";
    select($beitragTop);
    write(LESS);

    my $beitragAusg = select(LESS);
    $^ = "SALDO_TOP";
    $~ = "SALDOAUSGABE";
    select($beitragAusg);


    for($x = 0 ; $x < $mitgliedObj->anzahlSaldo(); $x++) {
		if(my $saldoObj = $mitgliedObj->getsaldoObj($x)) {
			$saldo = defined ${$saldoObj}->betrag() ? ${$saldoObj}->betrag() : "-";
			$datum = ${$saldoObj}->datum() ? ${$saldoObj}->datum() : "-";
			$bezeichnung = ${$saldoObj}->bezeichnung() ? ${$saldoObj}->bezeichnung() : "-";
			$info = ${$saldoObj}->info() ? ${$saldoObj}->info() : "-";
			write(LESS);
		}
    }
	close(LESS);

    select(STDOUT);
    print "\n\n";

    return $-;
}

sub kontoAusgabe {
    my ($mitgliedObj, $aktLine) = @_;
    my($x, $nr, $bank, $blz);

format KONTO_TOP =
Nr.   Konto Nr.         BLZ        Bank
-------------------------------------------------------------------------------------
.

format KONTOAUSGABE =
@<<<< @<<<<<<<<<<<<<<<< @<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$x,   $nr,              $blz,      $bank
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $kontoTop = select(STDOUT);
    $^ = "LEER";
    $~ = "KONTO_TOP";
    select($kontoTop);
    write(STDOUT);

    my $kontoAusg = select(STDOUT);
    $^ = "KONTO_TOP";
    $~ = "KONTOAUSGABE";
    select($kontoAusg);

    for($x = 0; $x < $mitgliedObj->anzahlKonto(); $x++) {
		if(my $kontoObj = $mitgliedObj->getkontoObj($x)) {
			$nr = ${$kontoObj}->kontonummer() ? ${$kontoObj}->kontonummer() : "-";
			$bank = ${$kontoObj}->bank() ? ${$kontoObj}->bank() : "-";
			$blz = ${$kontoObj}->bankleitzahl() ? ${$kontoObj}->bankleitzahl() : "-";
			write(STDOUT);
		}
    }

    select(STDOUT);
    print "\n\n";

    return($-);
}

sub infoAusgabe {
    my($mitgliedObj) = @_;
    my @info;
    @info = $mitgliedObj->info();
    $info[0] = "-" unless($info[0]);

    print "Info\n-------------------------------------------------------------------------------\n";
    print @info;
    print "\n\n";

    return;
}

sub umsAusgabe
{
	my ($refBuchungen , $aktLine) = @_;

	eval {
		open(LESS, "| $glob_anzeigeTool") or die
	};
	if($@) {
		print "Error! Kann AnzeigeTool $glob_anzeigeTool nicht oeffnen\n$!";
		return;
	 }

	my ($valutadatum,$shkenn,$betrag,$fremdname,$bezeichnung);

format BUCHUNG_TOP =
Valutadatum     Betrag Name                               Bezeichnung
--------------------------------------------------------------------------------------------
.

format BUCHUNGAUSGABE =
@<<<<<<<<<< @< @>>>>>> @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$valutadatum,$shkenn,$betrag,$fremdname
                       @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$bezeichnung
.

    if($aktLine) {
		$- = $aktLine;
    } else {
		$- = 0;
    }

    my $buchungTop = select(LESS);
	$^ = "LEER";
	$~ = "BUCHUNG_TOP";
	select($buchungTop);
	write(LESS);

	my $BuchungAusg = select(LESS);
	$^ = "BUCHUNG_TOP";
	$~ = "BUCHUNGAUSGABE";
	select($BuchungAusg);

	foreach(@{$refBuchungen}) {
		$valutadatum = $$_[1] ? $$_[1] : "-";
		if($$_[2] eq "credit") {
			$shkenn = '+';
		} else {
			$shkenn = '-';
		}
		$betrag = $$_[3] ? $$_[3] : "-";
		$fremdname = $$_[4] ? $$_[4] : "-";
		$bezeichnung = $$_[5] ? $$_[5] : "-";
		write(LESS);

	}
	close(LESS);

	select(STDOUT);
    print "\n\n";

	return;
}

sub internList
{
    my ($mitglieder, $aktLine) = @_;

	my ($mitglNr,$vorname,$name,$nickname,$internEmail);

format INTERN_TOP =
Mitgl.Nr. Vornamen          Name              Nickname      Intern Email Adr.
--------------------------------------------------------------------------------------------
.
format INTERNAUSGABE =
@<<<<<<<< @<<<<<<<<<<<<<<<< @<<<<<<<<<<<<<<<< @<<<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$mitglNr,$vorname,$name,$nickname,$internEmail
.

    my $internTop = select(STDOUT);
	$^ = "LEER";
	$~ = "INTERN_TOP";
	select($internTop);
	write(STDOUT);

	my $internAusg = select(STDOUT);
	$^ = "INTERN_TOP";
	$~ = "INTERNAUSGABE";
	select($internAusg);

   for my $mObj (@$mitglieder) {
		$mitglNr = $mObj->mitgliedsnr() ? $mObj->mitgliedsnr() : "-";
		$vorname = $mObj->vorname() ? $mObj->vorname() : "-";
		$name = $mObj->name() ? $mObj->name() : "-";
		$nickname = $mObj->nickname() ? $mObj->nickname() : "-";
		$internEmail = $mObj->internATlist() ? $mObj->internATlist() : "-";
		write(STDOUT);
    }

    select(STDOUT);
    print "\n\n";

    return $-;
}

sub shellAccount
{
    my ($mitglieder, $aktLine) = @_;

	my ($mitglNr,$vorname,$name,$nickname,$shell);

format SHELL_TOP =
Mitgl.Nr. Vornamen          Name              Nickname    Shell Account
--------------------------------------------------------------------------------------------
.
format SHELLAUSGABE =
@<<<<<<<< @<<<<<<<<<<<<<<<< @<<<<<<<<<<<<<<<< @<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$mitglNr,$vorname,$name,$nickname,$shell
.
    my $shellTop = select(STDOUT);
	$^ = "LEER";
	$~ = "SHELL_TOP";
	select($shellTop);
	write(STDOUT);

	my $shellAusg = select(STDOUT);
	$^ = "SHELL_TOP";
	$~ = "SHELLAUSGABE";
	select($shellAusg);

    for my $mObj (@$mitglieder) {
		$mitglNr = $mObj->mitgliedsnr() ? $mObj->mitgliedsnr() : "-";
		$vorname = $mObj->vorname() ? $mObj->vorname() : "-";
		$name = $mObj->name() ? $mObj->name() : "-";
		$nickname = $mObj->nickname() ? $mObj->nickname() : "-";
		$shell = $mObj->shellzugang() ? $mObj->shellzugang() : "-";

		write(STDOUT);
    }

    select(STDOUT);
    print "\n\n";

    return $-;
}

sub interCCClist
{
    my ($mitglieder, $aktLine) = @_;

	my ($mitglNr,$vorname,$name,$nickname,$cccemail);

format CCC_TOP =
Mitgl.Nr. Vornamen          Name              Nickname    CCC Email Adr.
--------------------------------------------------------------------------------------------
.
format CCCAUSGABE =
@<<<<<<<< @<<<<<<<<<<<<<<<< @<<<<<<<<<<<<<<<< @<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$mitglNr,$vorname,$name,$nickname,$cccemail
.
    my $cccTop = select(STDOUT);
	$^ = "LEER";
	$~ = "CCC_TOP";
	select($cccTop);
	write(STDOUT);

	my $cccAusg = select(STDOUT);
	$^ = "CCC_TOP";
	$~ = "CCCAUSGABE";
	select($cccAusg);

    for my $mObj (@$mitglieder) {
		$mitglNr = $mObj->mitgliedsnr() ? $mObj->mitgliedsnr() : "-";
		$vorname = $mObj->vorname() ? $mObj->vorname() : "-";
		$name = $mObj->name() ? $mObj->name() : "-";
		$nickname = $mObj->nickname() ? $mObj->nickname() : "-";
		$cccemail = $mObj->cccATlist() ? $mObj->cccATlist() : "-";

		write(STDOUT);
    }

    select(STDOUT);
    print "\n\n";

    return $-;
}


1;
