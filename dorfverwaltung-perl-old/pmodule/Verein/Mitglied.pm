
#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Mitglied.pm,v 1.8 2005/12/04 16:14:45 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Mitglied.pm,v $
# Revision 1.8  2005/12/04 16:14:45  jboehme
# - Neuer Menuepunkt: Mitglieder loeschen.
# - Geloeschte Mitglieder koennen nicht mehr angezeigt oder veraendert werden.
#
# Revision 1.7  2005/09/11 21:38:35  jboehme
# - BUGFIX: Die werte false, no und 0 werden als Gueltige werte erkannt.
#
# Revision 1.6  2005/09/04 18:31:39  jboehme
# - Ausbesserung im Klassen Konstruktor: Das Objekt wird bei der Angabe des
#   uebergabeparameter -MitgliedsNr- mit daten gefuellt.
# - Ausbesserung der Klassen-methode changeMitglied: Neue "unter" Objekte
#   (AdresseObj, KontoObj etc.) werden mit der Datenbank insert Methode eingelesen
#
# Revision 1.5  2005/08/11 19:21:02  jboehme
# - Abaendern des package/Klassen Namens
# - Abaendern der Klassen "Aufrufe", anch abaendern der Klassen/package Namen
# - Neue Methode hinzugefuegt: Letztes Konto Objekt loeschen
#
# Revision 1.4  2005/08/10 11:19:15  jboehme
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
# Revision 1.1  2004/11/11 21:38:06  jboehme
# Initialrelease
# - Erster Entwurf des Objekts bzw. der Objektmethoden
#
#

package Verein::Mitglied;

use strict;
use Date::Manip;
use Verein::Datenbank;
use Verein::Adresse;
use Verein::Beitrag;
use Verein::Kommunikation;
use Verein::Konto;
use Verein::Saldo;
use Carp;
sub whowasi { (caller(1))[3] . "()" }

sub new # ( DatenbankObjekt, {[Mitgliedsnr]} )
{
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $dbobj = shift;

    my $self = { dbobj => \$dbobj, };


    if(@_) {
		my $wert1 = shift;
		if($wert1 && $wert1 =~ m/^\d+$/ && !@_) {
			$self->{mitglnr} = $wert1;
		}
    }


    bless $self, $class;

	if($self->{mitglnr}) {
		${$self->{dbobj}}->selectMitglied($self);
		$self->getMitglied();
	}

    return $self;
}

sub saveMitglied
{
    my $self = shift;

    eval {
		${$self->{dbobj}}->insertMitglied($self);
		die if(${$self->{dbobj}}->isError());

		for(my $x = 0; $x < $self->anzahlAdressen(); $x++) {
			${$self->{dbobj}}->insertAdresse($self,$x);
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlKonto(); $x++) {
			${$self->{dbobj}}->insertKonto($self,$x);
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlKomm(); $x++) {
			${$self->{dbobj}}->insertKommunikation($self,$x);
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlBeitrag(); $x++) {
			${$self->{dbobj}}->insertBeitrag($self,$x);
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlSaldo(); $x++) {
			${$self->{dbobj}}->insertSaldo($self,$x);
			die if(${$self->{dbobj}}->isError());
		}

		${$self->{dbobj}}->commit();
		die if(${$self->{dbobj}}->isError());
    };

    if($@) {
		print "$@\n";
		print "". ${$self->{dbobj}}->getError() ."\n" if(${$self->{dbobj}}->isError());
		${$self->{dbobj}}->rollback();
		print "". ${$self->{dbobj}}->getError() ."\n" if(${$self->{dbobj}}->isError());
		return 1;
    }

    return;
}

sub changeMitglied
{
    my $self = shift;

    eval {
		${$self->{dbobj}}->updateMitglied($self);
		die if(${$self->{dbobj}}->isError());

		for(my $x = 0; $x < $self->anzahlAdressen(); $x++) {
			if(${$self->getadressObj($x)}->id()) {
				${$self->{dbobj}}->updateAdresse($self,$x);
			} else {
				${$self->{dbobj}}->insertAdresse($self,$x);
			}
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlKonto(); $x++) {
			if(${$self->getkontoObj($x)}->id()) {
				${$self->{dbobj}}->updateKonto($self,$x);
			} else {
				${$self->{dbobj}}->insertKonto($self,$x);
			}
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlKomm(); $x++) {
			if(${$self->getkommObj($x)}->id()) {
				${$self->{dbobj}}->updateKommunikation($self,$x);
			} else {
				${$self->{dbobj}}->insertKommunikation($self,$x);
			}
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlBeitrag(); $x++) {
			if(${$self->getbeitragObj($x)}->id()) {
				${$self->{dbobj}}->updateBeitrag($self,$x);
			} else {
				${$self->{dbobj}}->insertBeitrag($self,$x);
			}
			die if(${$self->{dbobj}}->isError());
		}

		for(my $x = 0; $x < $self->anzahlSaldo(); $x++) {
			if(${$self->getsaldoObj($x)}->id()) {
				${$self->{dbobj}}->updateSaldo($self,$x);
			} else {
				${$self->{dbobj}}->insertSaldo($self,$x);
			}
			die if(${$self->{dbobj}}->isError());
		}

		${$self->{dbobj}}->commit();
		die if(${$self->{dbobj}}->isError());
    };

    if($@) {
		print "$@\n";
		print ${$self->{dbobj}}->getError() if(${$self->{dbobj}}->isError());
		${$self->{dbobj}}->rollback();
		print ${$self->{dbobj}}->getError() if(${$self->{dbobj}}->isError());
		return 1;
    }
    return;

}

sub getMitglied # ( [mitgliedsnr] )
{
    my $self = shift;
    if(@_) {
		$self->{mitglnr} = shift;
    }
    ${$self->{dbobj}}->selectMitglied($self);
    ${$self->{dbobj}}->selectAdresse($self);
    ${$self->{dbobj}}->selectKonto($self);
    ${$self->{dbobj}}->selectBeitrag($self);
    ${$self->{dbobj}}->selectSaldo($self);
    ${$self->{dbobj}}->selectKommunikation($self);

    if(${$self->{dbobj}}->isError()) { print "". ${$self->{dbobj}}->getError() ."\n";}

    return;
}

sub mitgliedsnr # ( [Option] | [MitgliedsNr] )
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if(defined $wert);

		if(defined $wert && $wert =~ m/^\d+$/) {
			$self->{mitglnr} = $wert;
		} elsif($wert =~ m/new/) {
	    	$self->{mitglnr} = ${$self->{dbobj}}->lastMitgliedsnr() + 1;
		}
    }

    return $self->{mitglnr};
}

sub deleteMitglied # ()
{
	my $self = shift;
	${$self->{dbobj}}->deleteMitglied($self);
	return;
}

sub setname
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{name} = $wert;
		}
    }
    return $self->{name};
}

sub name
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/^\s*(.+?)\s*$/$1/ if($wert);

		if($wert) {
			$self->{flname} = 1 if((!($self->{name}) && $wert) || ($self->{name} && $self->{name} ne $wert));
			$self->{name} = $wert;
		}
    }

    return $self->{name};
}

sub getupname
{
    my $self = shift;

    if($self->{flname}) {
		$self->{flname} = 0;
		return $self->{name};
    }
    return 0;
}

sub setvorname
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{vorname} = $wert;
		}
    }
    return $self->{vorname};
}

sub vorname
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/^\s*(.+?)\s*$/$1/ if($wert);

		if($wert) {
			$self->{flvorname} = 1 if((!($self->{vorname}) && $wert) || ($self->{vorname} && $self->{vorname} ne $wert));
			$self->{vorname} = $wert;
		}
    }

    return $self->{vorname};
}

sub getupvorname
{
    my $self = shift;

    if($self->{flvorname}) {
		$self->{flvorname} = 0;
		return $self->{vorname};
    }
    return 0;
}

sub setnickname
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{nickname} = $wert;
		}
    }
    return $self->{nickname};
}

sub nickname
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/^\s*(.+?)\s*$/$1/ if($wert);

		if($wert) {
			$self->{flnickname} = 1 if((!($self->{nickname}) && $wert) || ($self->{nickname} && $self->{nickname} ne $wert));
			$self->{nickname} = $wert;
		}
    }

    return $self->{nickname};
}

sub getupnickname
{
    my $self = shift;

    if($self->{flnickname}) {
		$self->{flnickname} = 0;
		return $self->{nickname};
    }
    return 0;
}

sub setmailbox
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{mailbox} = $wert;
		}
    }
    return $self->{mailbox};
}

sub mailbox
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && $wert =~ m/^.*\@.*$/) {
			$self->{flmailbox} = 1 if((!($self->{mailbox}) && $wert) || ($self->{mailbox} && $self->{mailbox} ne $wert));
			$self->{mailbox} = $wert;
		}
    }

    return $self->{mailbox};
}

sub getupmailbox
{
    my $self = shift;

    if($self->{flmailbox}) {
		$self->{flmailbox} = 0;
		return $self->{mailbox};
    }
    return 0;
}

sub seteinzug
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{einzug} = $wert;
		}
    }
    return $self->{einzug};
}

sub einzug
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if(defined $wert && $wert =~ m/t(rue)?|y(es)?|1|f(alse)?|n(o)?|0/) {
			$self->{fleinzug} = 1 if((!($self->{einzug}) && $wert) || ($self->{einzug} && $self->{einzug} ne $wert));
			$self->{einzug} = $wert;
		}
    }

    return $self->{einzug};
}

sub getupeinzug
{
    my $self = shift;

    if($self->{fleinzug}) {
		$self->{fleinzug} = 0;
		return $self->{einzug};
    }
    return 0;
}

sub seteintrittsdatum
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{eintrittsdatum} = $wert;
		}
    }
    return $self->{eintrittsdatum};
}

sub eintrittsdatum
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if(my $date = UnixDate(ParseDate($wert), "%d.%m.%Y")) {
			$self->{fleintrittsdatum} = 1 if((!($self->{eintrittsdatum}) && $wert) || ($self->{eintrittsdatum} && $self->{eintrittsdatum} ne $wert));
			$self->{eintrittsdatum} = $date;
		}
    }
    return $self->{eintrittsdatum};
}

sub getupeintrittsdatum
{
    my $self = shift;

    if($self->{fleintrittsdatum}) {
		$self->{fleintrittsdatum} = 0;
		return $self->{eintrittsdatum};
    }
    return 0;
}

sub setchaosnr
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{chaosnr} = $wert;
		}
    }
    return $self->{chaosnr};
}

sub chaosnr
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && $wert =~ m/^\d+$/) {
			$self->{flchaosnr} = 1 if((!($self->{chaosnr}) && $wert) || ($self->{chaosnr} && $self->{chaosnr} ne $wert));
			$self->{chaosnr} = $wert;
		}
    }

    return $self->{chaosnr};
}

sub getupchaosnr
{
    my $self = shift;

    if($self->{flchaosnr}) {
		$self->{flchaosnr} = 0;
		return $self->{chaosnr};
    }
    return 0;
}

sub setinternATlist
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{internlist} = $wert;
		}
    }
    return $self->{internlist};
}

sub internATlist
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && $wert =~ m/^.*\@.*$/) {
			$self->{flinternlist} = 1 if((!($self->{internlist}) && $wert) || ($self->{internlist} && $self->{internlist} ne $wert));
			$self->{internlist} = $wert;
		}
    }

    return $self->{internlist};
}

sub getupinternATlist
{
    my $self = shift;

    if($self->{flinternlist}) {
		$self->{flinternlist} = 0;
		return $self->{internlist};
    }
    return 0;
}

sub setcccATlist
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{ccclist} = $wert;
		}
    }
    return $self->{ccclist};
}

sub cccATlist
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && $wert =~ m/^.*\@.*$/) {
			$self->{flccclist} = 1 if((!($self->{ccclist}) && $wert) || ($self->{ccclist} && $self->{ccclist} ne $wert));
			$self->{ccclist} = $wert;
		}
    }

    return $self->{ccclist};
}

sub getupcccATlist
{
    my $self = shift;

    if($self->{flccclist}) {
		$self->{flccclist} = 0;
		return $self->{ccclist};
    }
    return 0;
}

sub setshellzugang
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{shell} = $wert;
		}
    }
    return $self->{shell};
}

sub shellzugang
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert) {
			$self->{flshell} = 1 if((!($self->{shell}) && $wert) || ($self->{shell} && $self->{shell} ne $wert));
			$self->{shell} = $wert;
		}
    }

    return $self->{shell};
}

sub getupshellzugang
{
    my $self = shift;

    if($self->{flshell}) {
		$self->{flshell} = 0;
		return $self->{shell};
    }
    return 0;
}

sub setinfo
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{info} = $wert;
		}
    }
    return $self->{info};
}

sub info
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{flinfo} = 1 if((!($self->{info}) && $wert) || ($self->{info} && $self->{info} ne $wert));
			$self->{info} = $wert;
		}
    }

    return $self->{info};
}

sub getupinfo
{
    my $self = shift;

    if($self->{flinfo}) {
		$self->{flinfo} = 0;
		return $self->{info};
    }
    return 0;
}



sub anzahlAdressen
{
    my $self = shift;
    return($#{$self->{adresse}}+1);
}

sub getadressObj # ( [x] )
{
    my $self = shift;

    my $x = $#{$self->{adresse}};
    if(@_) {
		$x = shift;
    }

    return $self->{adresse}[$x];
}

sub adresse # ( [x], [id], [obj] )
{
    my $self = shift;

    my $x = 0;
    if(@_) {
		$x = shift;
    }

    my $id = 0;
    if(@_) {
		$id = shift;
    }

    my $obj;
    if(@_) {
		$obj = shift;
    } else {
		$obj = Verein::Adresse->new($id);
    }

    if($x) {
		$self->{adresse}[$x] = \$obj;
    } else {
		push(@{$self->{adresse}}, \$obj);
    }

    return \$obj;
}



sub anzahlKomm
{
    my $self = shift;
    return($#{$self->{komm}}+1);
}

sub getkommObj # ( [x] )
{
    my $self = shift;

    my $x = $#{$self->{komm}};
    if(@_) {
		$x = shift;
    }

    return $self->{komm}[$x];
}

sub kommunikation # ( [x], [id], [obj] )
{
    my $self = shift;

    my $x = 0;
    if(@_) {
		$x = shift;
    }

    my $id = 0;
    if(@_) {
		$id = shift;
    }

    my $obj;
    if(@_) {
		$obj = shift;
    } else {
		$obj = Verein::Kommunikation->new($id);
    }

    if($x) {
		$self->{komm}[$x] = \$obj;
    } else {
		push(@{$self->{komm}}, \$obj);
    }

    return \$obj;
}



sub anzahlKonto
{
    my $self = shift;
    return($#{$self->{konto}}+1);
}

sub getkontoObj # ( [x] )
{
    my $self = shift;

    my $x = $#{$self->{konto}};
    if(@_) {
		$x = shift;
    }

    return $self->{konto}[$x];
}

sub deletLastkontoObj
{
    my $self = shift;
	pop(@{$self->{konto}});
    return ;
}

sub konto # ( [x], [id], [obj] )
{
    my $self = shift;

    my $x = 0;
    if(@_) {
		$x = shift;
    }

    my $id = 0;
    if(@_) {
		$id = shift;
    }

    my $obj;
    if(@_) {
		$obj = shift;
    } else {
		$obj = Verein::Konto->new($id);
    }

    if($x) {
		$self->{konto}[$x] = \$obj;
    } else {
		push(@{$self->{konto}}, \$obj);
    }

    return \$obj;
}



sub anzahlBeitrag
{
    my $self = shift;
    return($#{$self->{beitrag}}+1);
}

sub getbeitragObj # ( [x] )
{
    my $self = shift;

    my $x = $#{$self->{beitrag}};
    if(@_) {
		$x = shift;
    }

    return $self->{beitrag}[$x];
}

sub beitrag # ( [x], [id], [obj] )
{
    my $self = shift;

    my $x = 0;
    if(@_) {
		$x = shift;
    }

    my $id = 0;
    if(@_) {
		$id = shift;
    }

    my $obj;
    if(@_) {
		$obj = shift;
    } else {
		$obj = Verein::Beitrag->new($id);
    }

    if($x) {
		$self->{beitrag}[$x] = \$obj;
    } else {
		push(@{$self->{beitrag}}, \$obj);
    }

    return \$obj;
}



sub anzahlSaldo
{
    my $self = shift;
    return($#{$self->{saldo}}+1);
}

sub getsaldoObj # ( [x] )
{
    my $self = shift;

    my $x = $#{$self->{saldo}};
    if(@_) {
		$x = shift;
    }

    return $self->{saldo}[$x];
}

sub saldo # ( [x], [id], [obj] )
{
    my $self = shift;

    my $x = 0;
    if(@_) {
		$x = shift;
    }

    my $id = 0;
    if(@_) {
		$id = shift;
    }

    my $obj;
    if(@_) {
		$obj = shift;
    } else {
		$obj = Verein::Saldo->new($id);
	}

    if($x) {
		$self->{saldo}[$x] = \$obj;
    } else {
		push(@{$self->{saldo}}, \$obj);
    }

    return \$obj;
}

sub searchName # ( Name )
{
	my $self = shift;
	my $name = shift;

	$name =~ s/,/ /g;
	my @namen = split(" ",$name);

	$namen[0] = lc $namen[0];
	$namen[0] = ucfirst $namen[0];

	$namen[1] = lc $namen[1];
	$namen[1] = ucfirst $namen[1];

    eval {
		${$self->{dbobj}}->searchName($self,@namen);
	};
	if(${$self->{dbobj}}->isError()) {
		print "DBError: ". ${$self->{dbobj}}->getError() ."\n";
	}

	return;
}

sub searchKto # ( KontoNr, BLZ )
{
	my $self = shift;

	eval {
		${$self->{dbobj}}->searchKto($self,@_);
	};
	if(${$self->{dbobj}}->isError()) {
		print "DBError: ". ${$self->{dbobj}}->getError() ."\n";
	}

	return;
}

sub searchBez # ( Bezeichung )
{
	my $self = shift;
	my $bez = shift;

	$bez =~ s/,/ /g;
	my @bezeichnung = split(" ",$bez);

	my $old = '';
	foreach(@bezeichnung) {
		$_ = lc $_;
		$_ = ucfirst $_;
		eval {
			if($_ =~ m/^\d{4,5}$/) {
				${$self->{dbobj}}->searchMitglNr($self,$_);
			} else {
				${$self->{dbobj}}->searchName($self,($old,$_));
			}
		};
		if(${$self->{dbobj}}->isError()) {
			print "DBError: ". ${$self->{dbobj}}->getError() ."\n";
		}
		$old = $_;
	}

	return;
}

1;
