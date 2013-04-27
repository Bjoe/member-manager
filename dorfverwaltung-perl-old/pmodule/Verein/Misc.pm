#!/usr/bin/perl -w
#
# Funktion: Versiedene Funktionen
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/Misc.pm,v 1.4 2005/09/04 18:20:10 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: Misc.pm,v $
# Revision 1.4  2005/09/04 18:20:10  jboehme
# - FIX: Datums eingabe ausgebessert
#
# Revision 1.3  2005/08/11 19:15:57  jboehme
# - Abaendern des package/Klassen Namens
# - BugFixe in den Eingabe Funktionen
#
# Revision 1.2  2005/08/10 11:12:28  jboehme
# - Source Code nach Emacs Umstellung umformatiert
#
# Revision 1.1  2005/03/23 02:58:17  jboehme
# Initial Revision
#
#-------------------------------------------------------------------------------------------------
#
#

package Verein::Misc;

use strict;
use Term::ReadKey;
use Term::ReadLine;
use Date::Manip;
use Mail::GnuPG;
use MIME::Entity;
use File::Temp qw/tempfile/;
sub whowasi { (caller(1))[3] . "()" }

sub bEingabe
{
    my ($zahlen, @zeichen) = @_;
    my $eingabe;
    my $error = 0;

    do {
		#$eingabe = $term->readline(" ? ");
		#$eingabe = ReadLine(0);
		print " ? ";
		$eingabe = <STDIN>;
		chomp($eingabe);

		if(defined $zahlen or @zeichen) {
			$error = 1;
			if($eingabe =~ /^\d+/ and defined $zahlen) {
				$error = 0 if(defined $eingabe <= defined $zahlen);
				$error = 1 unless(defined $eingabe);
			}
			if(@zeichen) {
				for my $ascii (@zeichen) {
					if(defined $ascii eq defined $eingabe) {
						$error = 0;
						last;
					}
				}
			}
		}
    } while($error);

    return $eingabe;
}

sub zEingabe
{
	return bEingabe(@_);
}
#sub zEingabe
#{
#    my ($zahlen, @zeichen) = @_;
#    my $key;
#    my $error = 0;
#
#    do {
#		print " ? ";
#		ReadMode('cbreak');
#		$key = ReadKey(0);
#		ReadMode('normal');
#		print "$key";
#		chomp($key);
#
#		if(defined $zahlen or @zeichen) {
#			$error = 1;
#			if($key =~ /^\d+/ and defined $zahlen) {
#				$error = 0 if(defined $key <= defined $zahlen);
#				$error = 1 unless(defined $key);
#			}
#			if(@zeichen) {
#				for my $ascii (@zeichen) {
#					if(defined $ascii eq defined $key) {
#						$error = 0;
#						last;
#					}
#				}
#			}
#		}
#    } while($error);
#
#    return $key;
#}

sub stdEingabe # ( AnzeigeTxt, [Parameter] )
{
	my ($txt, $parameter) = @_;
	my $eingabe;
	my $anzeigen = "";

	$anzeigen = "\[$parameter\]" if(defined $parameter);
	print "\n$txt $anzeigen";
	$eingabe = bEingabe();
	$parameter = $eingabe if($eingabe || (defined $eingabe && $eingabe eq "0"));

	return($parameter);
}

sub datumEingabe # ( AnzeigeTxt, [Parameter] )
{
	my ($txt, $parameter) = @_;
	my $eingabe;
	my $anzeigen = "";

	if($parameter) {
		my $date = ParseDate($parameter);
		if($date) {
			my ($jahr, $monat, $tag) = UnixDate($date, "%Y", "%m", "%d");
			$parameter = $tag .".". $monat .".". $jahr;
		}
		$anzeigen = "\[$parameter\]";
	}
	print "\n$txt $anzeigen";

	$parameter = $eingabe if($eingabe = eingabeDatum());

	$parameter = "1000-01-01" unless($parameter);
	return($parameter);
}

sub eingabeDatum
{
    my $error = 0;

    do {
		$error = 0;
		print ": ";
		my $eingabe = bEingabe();
		if($eingabe) {
			my $date = ParseDate($eingabe);
			if($date) {
				my ($jahr, $monat, $tag) = UnixDate($date, "%Y", "%m", "%d");
				$error = 0;
				return "$jahr-$monat-$tag";
			} else {
				print "\nFalsches Datum: $eingabe\n";
				$error = 1;
			}
		}
    } while($error);

	return;
}

sub boolEingabe # ( AnzeigeTxt, $@zeichen, [Parameter] )
{
	my ($txt, $zeichen, $parameter) = @_;
	my $eingabe;
	my $anzeige = "";

	$anzeige = "\[$parameter\]" if($parameter);
	print "\n\n$txt $anzeige";
	$eingabe = zEingabe(0,@$zeichen);
	$parameter = $eingabe if($eingabe || (defined $eingabe && $eingabe eq "0"));

	return($parameter);
}

sub infoEingabe # ( Infotext )
{
	my ($info) = @_;

	$info = "\n" unless($info);
	my @eingabe;

	my($fh, $filename) = tempfile();
	close($fh);

	open(TEMPF, ">$filename")
    or eval {
		print "Kann $filename nicht schreiben";
		return;
    };

	print TEMPF $info;
	close(TEMPF);

	system +($ENV{EDITOR} || 'vi'), $filename;

	if (-r $filename) {
		open(TEMPFF, $filename) or eval {
			unlink($filename);
			print "Kann $filename nicht oeffnen";
			return;
		};

		@eingabe = <TEMPFF>;
		close(TEMPFF);
		unlink($filename);
	}

	return @eingabe;
}

sub arrayTOscalar
{
	my (@arrayy) = @_;
	my $scalarr = "@arrayy";
	$scalarr =~ s/\n\s/\n/g;
	return $scalarr;
}

sub schluesselAuswaehlen # ( gpgObj )
{
	my $gpgObj = shift;

	my @keys = $gpgObj->getallPubKeys();
	print "\n0. Keinen\n";
	my $x = 1;
	my ($user_id, $key);
	foreach $key (@keys) {
		print $x .". ". $key ."\n";
		$x++;
	}
	print "\nWelchen GnuPG Schluessel:";
	my $schluessel;
	my $eingabe = bEingabe();
	$eingabe = $eingabe =~ m/^\d+$/ ? $eingabe : 0;
	if($eingabe != 0 and $eingabe < $#keys) {
		$schluessel = $keys[$eingabe-1];
	} else {
		$schluessel = "Keinen";
	}

	return $schluessel;
}

sub konto # ( DBobj, konto )
{
    my $dbhobj = shift;
    my $konto = shift;

    print "Verfuegbare Konten:\nKontoNr       Konto\n";
    my %konten = $dbhobj->selectKonten();
    my @nr;
    for my $kontonr (keys %konten) {
		print "". $kontonr ." ". $konten{konto} ."\n";
		push(@nr,$kontonr);
    }
    print "\nWelches Konto:";
    print " [$konto]" if($konto);
    my $eingabe = bEingabe(undef,@nr);
    $eingabe = $konto unless($eingabe);

    return $eingabe;
}

sub barkonto # ( DBobj, barkonto )
{
    my $dbhobj = shift;
    my $konto = shift;

    print "Verfuegbare Barkonten:\nNr       Konto\n";
    my %konten = $dbhobj->selectBarkonten();
    my @nr;
    for my $kontonr (keys %konten) {
		print "". $kontonr ." ". $konten{konto} ."\n";
		push(@nr,$kontonr);
    }
    print "\nWelches Barkonto:";
    print " [$konto]" if($konto);
    my $eingabe = bEingabe(undef,@nr);
    $eingabe = $konto unless($eingabe);

    return $eingabe;
}

sub sendEmail # ( From Adr, To Adr, Cc Adr, Subject, Message, GPG Password )
{
	my ($from,$to,$cc,$subject,$msg,$password) = @_;

	my $objMIMEBody = MIME::Entity->build( From => $from,
										   To => $to,
										   Cc => $cc,
										   Subject => $subject,
										   Data => $msg);

	my $objMailGPG = new Mail::GnuPG( passphrase => $password );
	my $ret = $objMailGPG->mime_sign( $objMIMEBody, $from );
	if($ret) {
		print "\nEs ist ein Fehler aufgetreten:\n";
		print "Return Code: ". $ret ."\n";
		print "GnuPG Message:\n";
		foreach(@{$objMailGPG->{last_message}}) { print $_}
		print "\n";
		return;
	}

	open(SENDMAIL, "| sendmail \"$to\" \"$cc\"") or
	eval {
		print "Kann sendmail nicht starten\n$!\n";
		return;
	};
	$objMIMEBody->print(\*SENDMAIL);
	close(SENDMAIL);

	return;
}

1;
