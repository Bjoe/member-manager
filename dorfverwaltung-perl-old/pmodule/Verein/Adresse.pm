#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Adresse.pm,v 1.4 2005/08/11 19:05:27 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Adresse.pm,v $
# Revision 1.4  2005/08/11 19:05:27  jboehme
# - Abaendern des package/Klassen Namens
#
# Revision 1.3  2005/08/10 10:57:09  jboehme
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

package Verein::Adresse;

use strict;
use Verein::DeEncrypt;
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
		$self->{id} = $wert if($wert);
    }

    return $self->{id};
}

sub setStr
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$self->{strasse} = $wert if($wert);
    }

    return $self->{strasse};
}

sub getupStr
{
    my $self = shift;

    if($self->{flstrasse}) {
		$self->{flstrasse} = 0;
		return $self->{strasse};
    }
    return 0;
}

sub strasse
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/^\s*(.+?)\s*$/$1/ if($wert);

		if($wert) {
			$self->{flstrasse} = 1 if((!($self->{strasse}) && $wert) || ($self->{strasse} && $self->{strasse} ne $wert));
			$self->{strasse} = $wert;
		}
    }
    return $self->{strasse};
}

sub setplz
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$self->{plz} = $wert if($wert);
    }

    return $self->{plz};
}

sub plz
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && $wert =~ m/^\d{1,5}$/) {
			$self->{flplz} = 1 if((!($self->{plz}) && $wert) || ($self->{plz} && $self->{plz} ne $wert));
			$self->{plz} = $wert;
		}
    }

    return $self->{plz};
}

sub getupplz
{
    my $self = shift;

    if($self->{flplz}) {
		$self->{flplz} = 0;
		return $self->{plz};
    }
    return 0;
}

sub setort
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$self->{ort} = $wert if($wert);
    }

    return $self->{ort};
}

sub ort
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/^\s*(.+?)\s*$/$1/ if($wert);

		if($wert) {
			$self->{flort} = 1 if((!($self->{ort}) && $wert) || ($self->{ort} && $self->{ort} ne $wert));
			$self->{ort} = $wert;
		}
    }

    return $self->{ort};
}

sub getuport
{
    my $self = shift;

    if($self->{flort}) {
		$self->{flort} = 0;
		return $self->{ort};
    }
    return 0;
}

1;
