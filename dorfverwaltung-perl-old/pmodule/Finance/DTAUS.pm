#!/usr/bin/perl -w
#
# $Id: DTAUS.pm,v 1.10 2005/09/11 12:36:33 jboehme Exp $
#
#-------------------------------------------------------------------------------------------------
# Funktion: Generieren des DTAUS format fuer Banken
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: DTAUS.pm,v $
# Revision 1.10  2005/09/11 12:36:33  jboehme
# - BUGFIX: Datensatz C muss durch 128 Bytes Teilbar sein. Auffuellen des Datensatz mit "Spaces"
#
# Revision 1.9  2005/09/04 18:45:53  jboehme
# - Aenderung: Package/Klassen Namen geaendert
# - Erweiterung: alle Umlaute werden umgewandelt.
#   Neue Methode: cleanstr
#
# Revision 1.8  2005/08/10 11:25:51  jboehme
# - Source Code nach Emacs Umstellung umformatiert
#
# Revision 1.7  2004/05/04 22:55:28  jboehme
# Die Objekt Funktionen subdtC, subdtE, subdtA, satzabschn, strf, zafk und zaf werden
# als private Methoden deklariert.
# Fehlerausbesserung der Zahlenformatierung in der Funktion zaf.
#
# Revision 1.6  2004/04/25 23:35:41  jboehme
# Fehlerausbesserung bzgl des aktuellen Datum
# in der Klassenmethode new.
#
# Revision 1.5  2004/04/25 20:20:30  jboehme
# Datumsformat ist auf German gesetzt.
#
# Revision 1.4  2004/03/28 17:52:34  jboehme
# Lauffaehige BETA Version.
# NEU: Mit Automatischen Erweiterungsteil im Datensatz C fuer Verwendungszw.,
#      Name des Beguenstigten oder Name des Aufftrg.
#
# Aenderung in der Objekt-Methode auftrgbName:
# Die Leerzeichen am anfang und am Ende des uebergabe Parameters werden geloescht (gestript)
# Fehlerausgabe ausgebessert.
#
# Hinzufuegen einer neuen Objekt-Methode auftrgNameLang:
# zum uebergeben des vollstaendigen Kontonamen an DTAUS
#
# Aenderung in der Objekt-Methode empfName und verwendungszweck:
# Die Leerzeichen am anfang und am Ende des uebergabe Parameters werden geloescht (gestript)
# Fehlerausgabe ausgebessert.
# Uebergabeparameter wird in einem Array a 27 Zeichen abgespeichert
#
# Aenderung in der subroutine dtC:
# Die Objekt Variable fuer die DTAUS Felder Empfaengername Nr 14a, Aufftrgname Nr 15 und
# Verwendungszw Nr 16 sind Arrays.
# Programm Routine fuer "Variabler Satzabschnitt Teil Datensatz C" hinzugefuegt.
#
# Hinzufuegen einer neuen subroutine satzabschn:
# Fuer die Verarbeitung/"Verwaltung"/Kontrolle der Variablen fuer die Programm Routine
# "Variabler Satzabschnitt Teil Datensatz C" in der subroutine dtC
#
# Aenderung in der subroutine strf:
# uebergabe Paramerter wird auf Sonderzeichen ueberprueft und in Grossbuchstaben
# umgewandelt.
#
# Aenderung in der subroutine zafk:
# Fehler Ausbersserung in der Komma Punkt Umwandlung.
#
# Revision 1.3  2004/03/21 21:27:31  jboehme
# Aenderung in der subroutine new:
# Die Objekt Variable kunde umbenannt in bank mit dem wert 0,
# die Objekt Variable gutschrift mit dem neuen wert 0 initialisiert.
#
# Umbenennen der subroutine zwKontnr nach referenzNr und
# aenderung der Variabelnamen in der subroutine genauso wie
# umbenennung der Objekt Variable kontonr2 nach refnr in
# dieser und dtA subroutine.
#
# Hinzufuegen einer neuen Methode (subroutine) erstBtBLZ fuer
# optionale DTAUS Format ausgabe Feld Nr 3.
# Dies bzgl. Aenderungen in der subroutine dtC
#
# Revision 1.2  2004/03/21 20:05:37  jboehme
# Aenderung in der Subroutine dtE:
# Ausbesserung des Fehlers in der DTAUS Formatausgabe im FeldNr 6 + 7.
# Summe bilden aus Kontonummern und BLZs fuer Feld 6 + 7.
#
# Revision 1.1  2004/03/21 19:30:48  jboehme
# Erste Funktionierende Version
#
#-------------------------------------------------------------------------------------------------
#
#

package Finance::DTAUS;

use strict;
use locale;
use Date::Manip;
use Carp;
sub whowasi { (caller(1))[3] . "()" }

Date_Init("Language=German","DateFormat=non-US");

my %txtschl = ( "Last-Abbuchung" => "04",
				"Last-Einzug" => "05",
				"Last-electronic-cash" => "05",
				"Last-Maestro" => "05",
				"Last-POZ" => "05",
				"Gutschrift" => "51",
				"Gehalt" => "53",
				"VL" => "54",
				"Ueberweisung" => "56");

my %txtschlerg = ( "Last-Abbuchung" => "000",
				   "Last-Einzug" => "000",
				   "Last-electronic-cash" => "005",
				   "Last-Maestro" => "006",
				   "Last-POZ" => "015",
				   "Gutschrift" => "000",
				   "Gehalt" => "000",
				   "VL" => "00J",
				   "Ueberweisung" => "000");

my($subdtC,$subdtE,$subdtA,$satzabschn,$cleanstr,$strf,$zafk,$zaf); # Privat Methoden

sub new {
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $datum = "heute";
    $datum = shift if(@_);

    my $filename = "DTAUS0.txt";
    $filename = shift if(@_);

    my $self = {  datum => $datum,
				  file => $filename,
				  anzahlDaten => 0,
				  bank => 0,
				  gutschrift => 0,
			   };

    return bless $self, $class;
}

sub baBLZ {
    my $self = shift;

    if(@_) {
		my $blz = shift;
		$blz =~ s/\s+//g;
		if(my $nblz = &$zaf($blz,8)) {
			$self->{blz} = $nblz;
		} else {
			croak "@{[&whowasi]}: $blz ist keine gueltige BLZ !\n";
		}
    }

    return $self->{blz};
}

sub auftrgbName {
    my $self = shift;

    if(@_) {
		my $name = shift;
		$name = &$cleanstr($name);
		if(my $nname = &$strf($name,27)) {
			$self->{name} = $nname;
        } else {
			croak "@{[&whowasi]}: $name ist zu lang oder enthaelt ein ungueltiges Zeichen!\n";
		}
    }

    return $self->{name};
}

sub auftrgbNameLang {
    my $self = shift;

    if(@_) {
		my $name = shift;
		$name = &$cleanstr($name);
		my $y = 0;
		while($name =~ /(.{1,27})/g) {
			if((my $nname = &$strf($1,27)) && ($y < 2)) {
				$self->{lname}[$y] = $nname;
				$y++;
			} else {
				croak "@{[&whowasi]}: $name ist zu lang oder enthaelt ein ungueltiges Zeichen!\n";
			}
		}
    }
    return $self->{name};
}

sub auftrgbKontnr {
    my $self = shift;

    if(@_) {
		my $kontonr = shift;
		$kontonr =~ s/\s+//g;
		if(my $nkont = &$zaf($kontonr,10)) {
			$self->{kontonr} = $nkont;
		} else {
			croak "@{[&whowasi]}: $kontonr ist keine gueltige Kontonummer !\n";
		}
    }

    return $self->{kontnr};
}

sub referenzNr {
    my $self = shift;

    if(@_) {
		my $refnr = shift;
		$refnr =~ s/\s+//g;
		if(my $nref = &$zaf($refnr,10)) {
			$self->{refnr} = $nref;
		} else {
			croak "@{[&whowasi]}: $refnr ist keine gueltige Referenznummer !\n";
		}
    }

    return $self->{refnr};
}

sub ausfDatum {
    my $self = shift;

    if(@_) {
		my $wert = shift;
		if(my $date = UnixDate(ParseDate($wert), "%d%m%Y")) {
			$self->{ausfdatum} = $date;
		} else {
			croak "@{[&whowasi]}: $wert ist keine gueltiges Datum !\n";
		}
    }
    return $self->{ausfdatum};
}

sub erstBtBLZ {
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $blz = shift;
		$blz =~ s/\s+//g;
		if(my $nblz = &$zaf($blz,8)) {
			$self->{erstKrBLZ}[$x] = $nblz;
		} else {
			croak "@{[&whowasi]}: $blz ist keine gueltige BLZ !\n";
		}
    }

    return $self->{erstKrBLZ}[$x];
}

sub empfKontonr {
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $kontonr = shift;
		$kontonr =~ s/\s+//g;
		if(my $nkont = &$zaf($kontonr,10)) {
			$self->{empfkontonr}[$x] = $nkont;
		} else {
			croak "@{[&whowasi]}: $kontonr ist keine gueltige Kontonummer !\n";
		}
		$self->{anzahlDaten} = $x if($self->{anzahlDaten} < $x);
    }

    return $self->{empfkontonr}[$x];
}

sub empfBLZ {
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $blz = shift;
		$blz =~ s/\s+//g;
		if(my $nblz = &$zaf($blz,8)) {
			$self->{empfblz}[$x] = $nblz;
		} else {
			croak "@{[&whowasi]}: $blz ist keine gueltige BLZ !\n";
		}
		$self->{anzahlDaten} = $x if($self->{anzahlDaten} < $x);
    }

    return $self->{empfblz}[$x];
}

sub betrag {
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g;
		if(my $nwert = &$zafk($wert)) {
			$self->{betrag}[$x] = $nwert;
		} else {
			croak "@{[&whowasi]}: $wert ist kein gueltiger EUR Betrag !\n";
		}
		$self->{anzahlDaten} = $x if($self->{anzahlDaten} < $x);
    }

    return $self->{betrag}[$x];
}

sub textschl {
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;
		my $txtsl = $txtschl{$wert};
		my $txtslerg = $txtschlerg{$wert};
		if($txtsl && $txtslerg) {
			$self->{textschl}[$x] = $txtsl;
			$self->{textschlerg}[$x] = $txtslerg;
		} else {
			croak "@{[&whowasi]}: $wert ist kein Textschluessel !\n";
		}
		$self->{anzahlDaten} = $x if($self->{anzahlDaten} < $x);	
    }

    return $self->{textschl}[$x] ."". $self->{textschlerg}[$x];
}

sub empfName {
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $name = shift;
		$name = &$cleanstr($name);
		my $y = 0;
		while($name =~ /(.{1,27})/g) {
			if((my $nname = &$strf($1,27)) && ($y < 2)) {
				$self->{empfname}[$x][$y] = $nname;
				$y++;
			} else {
				croak "@{[&whowasi]}: $name ist zu lang oder enthaelt ein ungueltiges Zeichen!\n";
			}
		}
		$self->{anzahlDaten} = $x if($self->{anzahlDaten} < $x);
    }

    return $self->{empfname}[$x];
}

sub verwendungszweck {
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;
		$wert = &$cleanstr($wert);
		my $y = 0;
		while($wert =~ /(.{1,27})/g) {
			if((my $nwert = &$strf($1,27)) && ($y < 14) ) {
				$self->{verwdzwck}[$x][$y] = $nwert;
				$y++;
			} else {
				croak "@{[&whowasi]}: $wert ist zu lang oder enthaelt ein ungueltiges Zeichen !\n";
			}
		}

		$self->{anzahlDaten} = $x if($self->{anzahlDaten} < $x);
    }

    return $self->{verwdzwck}[$x];
}

sub getDTAUS {
    my $self = shift;
    my $x = 0;

    open(FILE, "> ". $self->{file}) or croak "@{[&whowasi]}: Konnte ". $self->{file} ." nicht anlegen ! $!\n";
    my $datensatzA = &$subdtA($self);
    if($datensatzA) {
		print FILE $datensatzA;
    } else {
		close(FILE);
		croak "@{[&whowasi]}: Fehler beim zusammenstellen der Daten. Es fehlen die Stammdaten.\n";
    }

	my $sumBytes = 0;
    for(my $w = 0; $w <= $self->{anzahlDaten}; $w++) {
		if(my $datensatzC = &$subdtC($self, $w)) {
			$x++;
			print FILE $datensatzC;
		}
    }
    my $datensatzE = &$subdtE($self,$x);
    print FILE $datensatzE;
    close(FILE);

    return;
}

$subdtC = sub {
    my $self = shift;
    my $zaehler = shift;
    my $dtsC = "";

    if($self->{empfblz}[$zaehler] && $self->{empfkontonr}[$zaehler] && $self->{textschl}[$zaehler] &&
       $self->{textschlerg}[$zaehler] && $self->{blz} && $self->{kontonr} && $self->{betrag}[$zaehler] &&
       $self->{empfname}[$zaehler] && $self->{name} && $self->{verwdzwck}[$zaehler]) {

		my @dtC = ( "0187","C"); # FeldNr 1 + 2

		my $erblz;
		if($self->{erstKrBLZ}[$zaehler]) {
			$erblz = $self->{erstKrBLZ}[$zaehler];
		} else {
			$erblz = $self->{blz};
		}
		push(@dtC, $erblz); # FeldNr 3
		push(@dtC, $self->{empfblz}[$zaehler]); # FeldNr 4
		push(@dtC, $self->{empfkontonr}[$zaehler]); # FeldNr 5
		push(@dtC, pack "A13", "0" x 13); # FeldNr 6
		push(@dtC, $self->{textschl}[$zaehler]); # FeldNr 7a
		push(@dtC, $self->{textschlerg}[$zaehler]); # FeldNr 7b
		push(@dtC, pack "A1", ""); # FeldNr 8
		push(@dtC, pack "A11", "0"x 11); # FeldNr 9
		push(@dtC, $self->{blz}); # FeldNr 10
		push(@dtC, $self->{kontonr}); # FeldNr 11
		push(@dtC, $self->{betrag}[$zaehler]); # FeldNr 12
		push(@dtC, pack "A3", ""); # FeldNr 13
		push(@dtC, $self->{empfname}[$zaehler][0]); # FeldNr 14a
		push(@dtC, pack "A8", ""); # FeldNr 14b

		my $name = "";
		if($self->{lname} && (scalar @{$self->{lname}})) {
			$name = $self->{lname}[0];
		} else {
			$name = $self->{name};
		}
		push(@dtC, $name); # FeldNr 15
		push(@dtC, $self->{verwdzwck}[$zaehler][0]); # FeldNr 16
		push(@dtC, "1"); # FeldNr 17a
		push(@dtC, pack "A2", ""); # FeldNr 17b

		my $anzahl = 0;
		if($self->{verwdzwck}[$zaehler]) {
			$anzahl += ((scalar @{$self->{verwdzwck}[$zaehler]}) - 1);
		}
		if($self->{lname}) {
			$anzahl += ((scalar @{$self->{lname}}) - 1);
		}
		if($self->{empfname}[$zaehler]) {
			$anzahl += ((scalar @{$self->{empfname}[$zaehler]}) - 1);
		}

		my $stanzahl = &$zaf($anzahl,2);
		push(@dtC, $stanzahl); # FeldNr 18.

		my $anzahlby = 187;
		my $realBytes = 187;
		if($anzahl) {
			my $stellen = 0;
			my $satzst = 2;
			my $anzst = 11;

			if($self->{empfname}[$zaehler] && scalar @{$self->{empfname}[$zaehler]} > 1) {
				for(my $y = 1; scalar @{$self->{empfname}[$zaehler]} > $y; $y++) {
					push(@dtC, "01"); # FeldNr 19
					push(@dtC, $self->{empfname}[$zaehler][$y]); # FeldNr 20
					&$satzabschn(\$stellen,\$satzst,\$anzst,\$anzahlby,\$realBytes,\@dtC);
				}
			}

			if($self->{verwdzwck}[$zaehler] && scalar @{$self->{verwdzwck}[$zaehler]} > 1) {
				for(my $y = 1; scalar @{$self->{verwdzwck}[$zaehler]} > $y; $y++) {
					push(@dtC, "02"); # FeldNr 19
					push(@dtC, $self->{verwdzwck}[$zaehler][$y]); # FeldNr 20
					&$satzabschn(\$stellen,\$satzst,\$anzst,\$anzahlby,\$realBytes,\@dtC);
				}
			}

			if($self->{lname} && scalar @{$self->{lname}} > 1) {
				for(my $y = 1; scalar @{$self->{lname}} > $y; $y++) {
					push(@dtC, "03"); # FeldNr 19
					push(@dtC, $self->{lname}[$y]); # FeldNr 20
					&$satzabschn(\$stellen,\$satzst,\$anzst,\$anzahlby,\$realBytes,\@dtC);
				}
			}
		}

		$dtC[0] = &$zaf($anzahlby,4);

		# Datensatz muss durch 128 Bytes teilbar sein
		do {
			$realBytes -= 128;
		} while($realBytes > 0);
		$realBytes *= -1;
		push(@dtC, pack "A$realBytes", "");

		$dtsC = join "", @dtC;
    }
    return ($dtsC);
};

$subdtE = sub {
    my $self = shift;
    my $anzahl = shift;

    my @dtE = ("0128","E"); # FeldNr 1 + 2

    push(@dtE, pack "A5", ""); # FeldNr 3
    $anzahl = &$zaf($anzahl,7);
    push(@dtE, $anzahl); # FeldNr 4
    push(@dtE, pack "A13", "0" x 13); # FeldNr 5

    my $ktosumme = 0;
    foreach(@{$self->{empfkontonr}}) {
		$ktosumme = $ktosumme + $_;
    }
    $ktosumme = &$zaf($ktosumme,17);
    push(@dtE, $ktosumme); # FeldNr 6

    my $blzsumme = 0;
    foreach(@{$self->{empfblz}}) {
		$blzsumme = $blzsumme + $_;
    }
    $blzsumme = &$zaf($blzsumme,17);
    push(@dtE, $blzsumme); # FeldNr 7

    my $summe = 0;
    foreach(@{$self->{betrag}}) {
		$summe = $summe + $_;
    }
    $summe = &$zaf($summe,13);
    push(@dtE, $summe); # FeldNr 8
    push(@dtE, pack "A51", ""); # FeldNr 9

    my $dtsE = join "", @dtE;

    return $dtsE;
};

$subdtA = sub {
    my $self = shift;
    my $dtsA = "";

    if($self->{blz} && $self->{name} && $self->{datum} && $self->{kontonr}) {
		my @dtA = ("0128","A"); # FeldNr 1 + 2

		##### FeldNr 3
		if($self->{gutschrift}) { # In dieser Version noch nicht benutzt
			push(@dtA, "G");
		} else {
			push(@dtA, "L");
		}

		if($self->{bank}) { # In dieser Version noch nicht benutzt
			push(@dtA, "B");
		} else {
			push(@dtA, "K");
		}

		push(@dtA, $self->{blz});  # FeldNr 4
		push(@dtA, pack "A8", "0" x 8); # FeldNr 5
		push(@dtA, $self->{name}); # FeldNr 6
		push(@dtA, UnixDate(ParseDate($self->{datum}),"%d%m%y")); # FeldNr 7
		push(@dtA, pack "A4", ""); # FeldNr 8
		push(@dtA, $self->{kontonr}); # FeldNr 9

		my $refnr = pack "A10", "0" x 10;
		$refnr = $self->{refnr} if($self->{refnr});
		push(@dtA, $refnr); # FeldNr 10
		push(@dtA, pack "A15", ""); # FeldNr 11a

		my $ausdate = pack "A8", "";
		$ausdate = $self->{ausfdatum} if($self->{ausfdatum});
		push(@dtA, $ausdate); # FeldNr 11b
		push(@dtA, pack "A24", ""); # FeldNr 11c
		push(@dtA, "1"); # FeldNr 12

		$dtsA = join "", @dtA;
    }

    return $dtsA;
};

$satzabschn = sub {
    my ($stellen,$satzst,$anzst,$anzahlby,$realBytes,$dtC) = @_;
    $$stellen++;
    $$anzahlby += 29;
	$$realBytes += 29;
    if($$stellen == $$satzst) {
		push(@$dtC, pack "A$$anzst", "");
		$$realBytes += $$anzst;
		$$satzst = 4;
		$$anzst = 12;
    }
    return;
};

$cleanstr = sub {
	my ($wert) = @_;
	$wert =~ s/^\s*(.+?)\s*$/$1/;
	$wert =~ s/ö|Ö/oe/g;
	$wert =~ s/ä|Ä/ae/g;
	$wert =~ s/ü|Ü/ue/g;
	$wert =~ s/ß/ss/g;
	return $wert;
};

$strf = sub {
    my ($wert, $anzahlst) = @_;
    $wert = uc($wert);
    if($wert =~ m/^[0-9A-Z\s\.,&-\/\+\*\$%]*$/) {
		return pack "A$anzahlst", $wert;
    } else {
		return;
    }
};

$zafk = sub {
    my ($wert) = @_;
    $wert =~ s/,/\./;
    $wert =~ s/0*?(([1-9]{1}\d*\.)|(0\.)\d*)/$1/;
    if($wert =~ /^(\d{1,})\.?(\d{0,})/) {
		my $vorkomma = sprintf "%9d", $1;
		my $nachkomma = "0.$2";
		$nachkomma = sprintf "%.2f", $nachkomma;
		$vorkomma =~ s/\s/0/g;
		$nachkomma =~ s/^0.//;
		$wert = "$vorkomma$nachkomma";
    } else {
		$wert = 0;
    }
    return $wert;
};

$zaf = sub {
    my($wert, $anzahlst) = @_;
    if($anzahlst) {
		if($wert =~ m/^(\d{1,$anzahlst})$/) {
			my @ziffern = split("",$wert);
			my $nullst = $anzahlst - scalar @ziffern;
			my $nullen = pack "A$nullst", "0" x $nullst;
			$wert = "$nullen$wert";
		} else {
			$wert = 0;
		}
    } else {
		$wert = 0 unless($wert =~ m/^\d+$/);
    }
    return $wert;
};

1;
