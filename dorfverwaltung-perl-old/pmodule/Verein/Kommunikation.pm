#!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Kommunikation.pm,v 1.4 2005/08/11 19:13:27 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Kommunikation.pm,v $
# Revision 1.4  2005/08/11 19:13:27  jboehme
# - Abaendern des package/Klassen Namens
#
# Revision 1.3  2005/08/10 11:09:40  jboehme
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

package Verein::Kommunikation;

use strict;
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

sub getupemail
{
    my $self = shift;

    if($self->{flemail}) {
		$self->{flemail} = 0;
		return $self->{email};
    }
    return 0;
}

sub setemail
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{email} = $wert;
		}
    }

    return $self->{email};
}

sub email
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		$wert =~ s/\s+//g if($wert);

		if($wert && $wert =~ m/^.*\@.*$/) {
			$self->{flemail} = 1 if((!($self->{email}) && $wert) || ($self->{email} && $self->{email} ne $wert));
			$self->{email} = $wert;
		}
    }

    return $self->{email};
}

sub getuppubkey
{
    my $self = shift;

    if($self->{flpubkey}) {
		$self->{flpubkey} = 0;
		return $self->{pubkey};
	}
    return 0;
}

sub setpubkey
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{pubkey} = $wert;
		}
    }

    return $self->{pubkey};
}

sub pubkey
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{flpubkey} = 1 if($self->{pubkey} && $self->{pubkey} ne $wert);
			$self->{pubkey} = $wert;
		}
    }

    return $self->{pubkey};
}

1;
