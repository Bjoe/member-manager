##!/usr/bin/perl -w
#
# Projekt: Dorf-Verwaltung
#-------------------------------------------------------------------------------------------------
# $Header: /home/cvs/projekte/chaosdorf/pmodule/Verein/DeEncrypt.pm,v 1.4 2005/08/11 19:12:50 jboehme Exp $
# $Name:  $
#-------------------------------------------------------------------------------------------------
# $Log: DeEncrypt.pm,v $
# Revision 1.4  2005/08/11 19:12:50  jboehme
# - Abaendern des package/Klassen Namens
#
# Revision 1.3  2005/08/10 11:07:46  jboehme
# - Source Code nach Emacs Umstellung umformatiert
#
# Revision 1.2  2005/02/27 11:01:46  jboehme
# Programmcode Aenderung/Umstrukturierung: Prozedual -> OOP und Modulen
# Datenbankfelder hinzugefuegt und Datenbank erweitert
# Zeite BETA Version
#
# Revision 1.1  2004/11/14 21:14:34  jboehme
# Initialrelease
# - Erster Entwurf des Objekts.
#
#

package Verein::DeEncrypt;

use strict;
use GnuPG::Interface;
use IO::Handle;
use Carp;
sub whowasi { (caller(1))[3] . "()" }

sub new # ( private Key, [ \@ public Keys] )
{
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $privkey = shift;
    my @pubkey;
    if(@_) {
		my $schluessel = shift;
		@pubkey = @$schluessel;
    } else {
		push(@pubkey, $privkey);
    }

    my $self = { privkey => $privkey,
				 pubkeys => \@pubkey,
				 errorcode => 0,
			   };

    bless ($self, $class);

    return $self;
}

sub isError # ()
{
    my $self = shift;
    return $self->{errorcode};
}

sub getError # ()
{
    my $self = shift;
    $self->{errorcode} = 0;
    return $self->{error};
}

sub privkey # ( passwort, [schluessel] )
{
    my $self = shift;

    if(@_) {
		$self->{passwd} = shift;

		my $privkey = $self->{privkey};
		$privkey = shift if(@_);
		unless($privkey) {
			$self->{errorcode} = 1;
			$self->{error} = "\nKein Schluessel angegeben\n";
			return;
		}

		my $true = 0;
		foreach(@{$self->{pubkeys}}) {
			if($_ eq $privkey) {
				$true = 1;
				last;
			}
		}
		push(@{$self->{pubkeys}}, $privkey) unless($true);

		my @testver = $self->verschluesseln(1,"123test");

		unless(@testver) {
			$self->{errorcode} = 1;
			$self->{error} = "Test Verschluesselung ist fehlgeschlagen. GnuPG Schluessel nicht bekannt?\n";
			return;
		}

		my @test = $self->entschluesseln(1,@testver);

		if($test[0]) {
			unless($test[0] eq "123test") {
				$self->{errorcode} = 1;
				$self->{error} = "\nFalsches/r Passwort/Schluessel !!\n\n";
				return;
			}
		} else {
			$self->{errorcode} = 1;
			$self->{error} = "\nFalsches/r Passwort/Schluessel !!\n\n";
			return;
		}
    }

    return $self->{privkey};
}

sub getallPubKeys # ()
{
    my $self = shift;

    my $gnupg = new GnuPG::Interface();
    my $handles = new GnuPG::Handles();
    my $schluessel;

    my $pid = $gnupg->list_public_keys(handles => $handles);
    waitpid $pid, 0;

    my @keys = $gnupg->get_public_keys();

    my (@user_id, $key);
    foreach $key (@keys) {
		push(@user_id, $key->user_ids_ref->[0]->as_string);
    }

    return @user_id;
}

sub setPublicKeys # ( @ Schluessel )
{
    my $self = shift;
    foreach(@_) {
		push(@{$self->{pubkeys}},$_);
    }
}

sub getPublicKey # ( Output )
{
    my $self = shift;
    my $goutput = shift;

    my $gpg = GnuPG::Interface->new();
    $gpg->options->hash_init( 	armor => 1);

    my ( $input, $output, $error, $status) = (IO::Handle->new(), IO::Handle->new(), IO::Handle->new, IO::Handle->new);
    my $gpgHandles = GnuPG::Handles->new( 	stdin => $input,
											stdout => $output,
											stderr => $error,
											status => $status);

    my $pid = $gpg->export_keys( handles => $gpgHandles);

    print $input @{$self->{pubkeys}};
    close $input;

    my @publicKey = <$output>;
    my @perror = <$error>;
    my @pstatus = <$status>;

	if($goutput) {
		print "GnuPG: Error:\n@perror\n";
		print "GnuPG Status:\n@pstatus\n";
    }

    close $output;
    close $error;
    close $status;
    waitpid $pid, 0;

    return @publicKey;
}

sub verschluesseln # (  GPG-Output, Text )
{
    my $self = shift;
    my $goutput = shift;
    my @text = @_;

    my $gpg = GnuPG::Interface->new();
    $gpg->options->hash_init( 	armor => 1);

    unless($goutput) {
		$gpg->options->quiet(1);
		$gpg->options->no_verbose(1);
		$gpg->options->batch(1);
    }

    foreach(@{$self->{pubkeys}}) { $gpg->options->push_recipients($_);}

    my ( $input, $output, $error, $status) = (IO::Handle->new(), IO::Handle->new, IO::Handle->new, IO::Handle->new);
    my $gpgHandles = GnuPG::Handles->new( 	stdin => $input,
											stdout => $output,
											stderr => $error,
											status => $status);
    my $pid = $gpg->encrypt( handles => $gpgHandles);

    print $input @text;
    close $input;

    my @verschlText = <$output>;
    my @perror = <$error>;
    my @pstatus = <$status>;

    if($goutput) {
		print "GnuPG: Error:\n@perror\n";
		print "GnuPG Status:\n@pstatus\n";
    }

    close $output;
    close $error;
    close $status;
    waitpid $pid, 0;

    return "@verschlText";
}

sub entschluesseln # ( GPG-Output, Text )
{
    my $self = shift;
    my $goutput = shift;
    my @verschlText = @_;

    return "-" unless($verschlText[0]);

    my $gpg = GnuPG::Interface->new();
    $gpg->options->hash_init( 	armor => 1,
								recipients => [ $self->{privkey} ]);

    unless($goutput) {
		$gpg->options->quiet(1);
		$gpg->options->no_verbose(1);
		$gpg->options->batch(1);
    }

    my ( $input, $output, $error, $passH, $status) = (IO::Handle->new(), IO::Handle->new(), IO::Handle->new, IO::Handle->new, IO::Handle->new);
    my $gpgHandles = GnuPG::Handles->new( 	stdin => $input,
											stdout => $output,
											stderr => $error,
											passphrase => $passH,
											status => $status);
    my $pid = $gpg->decrypt( handles => $gpgHandles);

    print $passH $self->{passwd};
    close $passH;

    print $input @verschlText;
    close $input;

    my @text = <$output>;
    my @perror = <$error>;
    my @pstatus = <$status>;

    if($goutput) {
		print "GnuPG: Error:\n@perror\n";
		print "GnuPG Status:\n@pstatus\n";
    }

    close $output;
    close $error;
    close $status;
    waitpid $pid, 0;

    return "@text";
}

1;
