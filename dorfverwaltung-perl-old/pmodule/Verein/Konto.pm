#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Konto.pm,v 1.4 2005/08/11 19:13:59 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Konto.pm,v $
# Revision 1.4  2005/08/11 19:13:59  jboehme
# - Abaendern des package/Klassen Namens
#
# Revision 1.3  2005/08/10 11:10:54  jboehme
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

package Verein::Konto;

use strict;
use Verein::DeEncrypt;
use Carp;
sub whowasi { (caller(1))[3] . "()" }

sub new # ( [ID] )
{
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $cryptObj = shift;
    my $id = 0;
    if(@_) {
		$id = shift;
    }
    my $self = {   id => $id,
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

sub setKto
{
    my $self = shift;
    if(@_) {
		my $wert = shift;
		$self->{ktonr} = $wert if($wert);
    }

    return $self->{ktonr};
}

sub getupKto
{
    my $self = shift;

    if($self->{flktonr}) {
		$self->{flktonr} = 0;
		return $self->{ktonr};
    }
    return 0;
}

sub kontonummer
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && $wert =~ m/^\d+$/) {
			$self->{flktonr} = 1 if((!($self->{ktonr}) && $wert) || ($self->{ktonr} && $self->{ktonr} ne $wert));
			$self->{ktonr} = $wert;
		}
    }

    return $self->{ktonr};
}

sub setBank
{
    my $self = shift;
    if(@_) {
		my $wert = shift;
		$self->{bank} = $wert if($wert);
    }
    return $self->{bank};
}

sub getupBank
{
    my $self = shift;

    if($self->{flbank}) {
		$self->{flbank} = 0;
		return $self->{bank};
    }
    return 0;
}

sub bank
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/^\s*(.+?)\s*$/$1/ if($wert);

		if($wert) {
			$self->{flbank} = 1 if((!($self->{bank}) && $wert) || ($self->{bank} && $self->{bank} ne $wert));
			$self->{bank} = $wert;
		}
    }

    return $self->{bank};
}

sub setBLZ
{
    my $self = shift;
    if(@_) {
		my $wert = shift;
		$self->{blz} = $wert if($wert);
    }

    return $self->{blz};
}

sub getupBLZ
{
    my $self = shift;

    if($self->{flblz}) {
		$self->{flblz} = 0;
		return $self->{blz};
    }
    return 0;
}

sub bankleitzahl
{
    my $self = shift;

    my ($output,$erg);
    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);
		$erg = 0;

		if($wert && $wert =~ m/^\d{8}$/) {
			$self->{flblz} = 1 if((!($self->{blz}) && $wert) || ($self->{blz} && $self->{blz} ne $wert));
			$self->{blz} = $wert;
		}
    }

    return $self->{blz};
}

1;
