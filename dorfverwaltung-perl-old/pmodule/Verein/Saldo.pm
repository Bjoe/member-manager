#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Saldo.pm,v 1.5 2005/09/04 18:34:34 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Saldo.pm,v $
# Revision 1.5  2005/09/04 18:34:34  jboehme
# - FIX: Klassen-Variable offbtr auf betrag geaendert
# - Ausbesserung in der Klassen-Methode betrag: Negativwerte
#   werden uebernommen.
#
# Revision 1.4  2005/08/11 19:21:26  jboehme
# - Abaendern des package/Klassen Namens
#
# Revision 1.3  2005/08/10 11:22:03  jboehme
# - Source Code nach Emacs Umstellung umformatiert
#
# Revision 1.2  2005/03/23 22:08:52  jboehme
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
# Revision 1.1  2005/02/27 11:01:46  jboehme
# Programmcode Aenderung/Umstrukturierung: Prozedual -> OOP und Modulen
# Datenbankfelder hinzugefuegt und Datenbank erweitert
# Zeite BETA Version
#
#

package Verein::Saldo;

use strict;
use Date::Manip;
use Carp;
sub whowasi { (caller(1))[3] . "()" }

sub new # ()
{
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $id = 0;
    if(@_) {
		$id = shift;
    }
    my $self = {  id => $id,
			   };

    bless $self, $class;

    return $self;
}


sub id
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{id} = $wert;
		}
    }

    return $self->{id};
}

sub getupbetrag
{
    my $self = shift;

    if($self->{flbetrag}) {
		$self->{flbetrag} = 0;
		return $self->{betrag};
    }
    return 0;
}

sub setbetrag
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{betrag} = $wert;
		}
    }

    return $self->{betrag};
}

sub betrag
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if(defined $wert);

		if(defined $wert && $wert =~ m/^-?\d+((\.|,)\d+)?$/) {
			$self->{flbetrag} = 1 if((!(defined $self->{betrag}) && $wert) || (defined $self->{betrag} && $self->{betrag} ne $wert));
			$self->{betrag} = $wert;
		}
    }

    return $self->{betrag};
}

sub getupdatum
{
    my $self = shift;

    if($self->{fldatum}) {
		$self->{fldatum} = 0;
		return $self->{datum};
    }
    return 0;
}

sub setdatum
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{datum} = $wert;
		}
    }

    return $self->{datum};
}

sub datum
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && (my $date = UnixDate(ParseDate($wert), "%d.%m.%Y"))) {
			$self->{fldatum} = 1 if((!($self->{datum}) && $wert) || ($self->{datum} && $self->{datum} ne $wert));
			$self->{datum} = $date;
		}
    }
    return $self->{datum};
}

sub getupbezeichnung
{
    my $self = shift;

    if($self->{flbezeichnung}) {
		$self->{flbezeichnung} = 0;
		return $self->{bezeichnung};
    }
    return 0;
}

sub setbezeichnung
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{bezeichnung} = $wert;
		}
    }

    return $self->{bezeichnung};
}

sub bezeichnung
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{flbezeichnung} = 1 if((!($self->{bezeichnung}) && $wert) || ($self->{bezeichnung} && $self->{bezeichnung} ne $wert));
			$self->{bezeichnung} = $wert;
		}
    }

    return $self->{bezeichnung};
}

sub getupbarkonto
{
    my $self = shift;

    if($self->{flbarkonto}) {
		$self->{flbarkonto} = 0;
		return $self->{barkonto};
    }
    return 0;
}

sub setbarkonto
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{barkonto} = $wert;
		}
    }

    return $self->{barkonto};
}

sub barkonto
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{flbarkonto} = 1 if((!($self->{barkonto}) && $wert) || ($self->{barkonto} && $self->{barkonto} ne $wert));
			$self->{barkonto} = $wert;
		}
    }

    return $self->{barkonto};
}

sub getupkonto
{
    my $self = shift;

    if($self->{flkonto}) {
		$self->{flkonto} = 0;
		return $self->{konto};
    }
    return 0;
}

sub konto
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{flkonto} = 1 if((!($self->{konto}) && $wert) || ($self->{konto} && $self->{konto} ne $wert));
			$self->{konto} = $wert;
		}
    }

    return $self->{konto};
}

sub setkonto
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{konto} = $wert;
		}
    }

    return $self->{konto};
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

1;
