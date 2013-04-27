#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Beitrag.pm,v 1.5 2005/09/11 21:40:51 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Beitrag.pm,v $
# Revision 1.5  2005/09/11 21:40:51  jboehme
# - Erweiterung: Die Klasse wird mit der "Schulden" methode erweitert
#
# Revision 1.4  2005/08/11 19:07:22  jboehme
# - Abaendern des package/Klassen Namens
#
# Revision 1.3  2005/08/10 10:58:42  jboehme
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

package Verein::Beitrag;

use strict;
use Date::Manip;
use Carp;
sub whowasi { (caller(1))[3] . "()" }

sub new # ( [ID] )
{
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $id = 0;
    if(@_) {
		$id = shift;
    }

    my $self = { id => $id,
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

sub getupbeitrag
{
    my $self = shift;

    if($self->{flbeitrag}) {
		$self->{flbeitrag} = 0;
		return $self->{beitrag};
    }
    return 0;
}

sub setbeitrag
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if(defined $wert) {
			$self->{beitrag} = $wert;
		}
    }

    return $self->{beitrag};
}

sub beitrag
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if(defined $wert);

		if(defined $wert && $wert =~ m/^\d+((\.|,)\d+)?$/) {
			$self->{flbeitrag} = 1 if((!(defined $self->{beitrag}) && defined $wert) || (defined $self->{beitrag} && $self->{beitrag} ne $wert));
			$self->{beitrag} = $wert;
		}
    }

    return $self->{beitrag};

}

sub getupspende {
    my $self = shift;

    if($self->{flspende}) {
		$self->{flspende} = 0;
		return $self->{spende};
    }
    return 0;
}

sub spende {
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if(defined $wert);

		if(defined $wert && $wert =~ m/^\d+((\.|,)\d+)?$/) {
			$self->{flspende} = 1 if((!(defined $self->{spende}) && defined $wert) || (defined $self->{spende} && $self->{spende} ne $wert));
			$self->{spende} = $wert;
		}
    }

    return $self->{spende};
}

sub setspende
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if(defined $wert) {
			$self->{spende} = $wert;
		}
    }

    return $self->{spende};
}

sub getupschulden {
    my $self = shift;

    if($self->{flschulden}) {
		$self->{flschulden} = 0;
		return $self->{schulden};
    }
    return 0;
}

sub schulden {
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if(defined $wert);

		if(defined $wert && $wert =~ m/^\d+((\.|,)\d+)?$/) {
			$self->{flschulden} = 1 if((!(defined $self->{schulden}) && defined $wert) || (defined $self->{schulden} && $self->{schulden} ne $wert));
			$self->{schulden} = $wert;
		}
    }

    return $self->{schulden};
}

sub setschulden
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if(defined $wert) {
			$self->{schulden} = $wert;
		}
    }

    return $self->{schulden};
}

sub getupdatum {
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

sub datum {
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

sub getupinfo
{
    my $self = shift;

    if($self->{flinfo}) {
		$self->{flinfo} = 0;
		return $self->{info};
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

1;
