#
# Funktion: Swift Format MT940
#-------------------------------------------------------------------------------------------------
# $Id$
# $Name$
#-------------------------------------------------------------------------------------------------
# $Log$
#-------------------------------------------------------------------------------------------------
#
#

package Finance::SWIFT::MT940;

use strict;
use warnings;
use Date::Manip;
sub whowasi { (caller(1))[3] . "()" }

sub new # ( [filename] )
{
    my $ref = shift;
    my $class = ref($ref) || $ref;

    my $filename;
    if(@_) {
		$filename = shift;
		unless(-e $filename && -r $filename && -s $filename) {
			croak("\nError: $filename exstiert nicht oder kann nicht gelesen werden\n");
		}
    }

    my $self = { filename => "$filename",
			     dcCodes => { 'C' => 'credit',
							  'D' => 'debit'},

			   };

    bless $self, $class;

    return $self;
}

sub einlesen # ( [filename] )
{
    my $self = shift;

    if(@_) {
		my $filename = shift;
		unless(-e $filename && -r $filename && -s $filename) {
			croak("\nError: $filename exstiert nicht oder kann nicht gelesen werden\n");
		}
		$self->{filename} = "$filename";
    }

    open(DATA, "< ". $self->{filename} ."") or die "Kann ". $self->{filename} ." nicht oeffnen\n";
    my $x = -1;
    my $y = 0;
    my $z = 0;
    my $tagGruppe = 0;
    my $optionalTag = 0;
    my $lastTag = 0;

    while(<DATA>) {
		$_ =~ s/\r|\n//g;
		next if(!($_));

      SWITCH: {
			/^-$/ && do {
#				$x++;
#				$self->{TransactionLines} = $x;
#
#				$y = 0;
#				$self->{StatementLines}[$x] = $y;
#				$self->{forward_Available_Lines}[$x] = $y;
#
#				$z = 6;
#
#				$tagGruppe = 0;
#				$optionalTag = 0;
#				$lastTag = 0;
				last SWITCH;
			};

			#   M   20   Transaction Reference Number   16x
			/^:20/ && do {
				$x++;
				$self->{TransactionLines} = $x;

				$y = 0;
				$self->{StatementLines}[$x] = $y;
				$self->{forward_Available_Lines}[$x] = $y;

				$z = 6;

				$tagGruppe = 0;
				$optionalTag = 0;
				$lastTag = 0;

				my $buf = $_;
				$buf =~ s/^:20:(.{1,16})/$1/;
				$self->{transaction_Ref}[$x] = $buf;

				$lastTag = 20;
				$tagGruppe = 1;
				last SWITCH;
			};

			#   O   21   Related Reference   16x
			/^:21/ && $tagGruppe == 1 && $optionalTag == 0 && do {
				my $buf = $_;
				$buf =~ s/^:21:(.{1,16})/$1/;
				$self->{reference}[$x] = $buf;

				$lastTag = 21;
				$optionalTag = 1;
				last SWITCH;
			};

			#   M   25   Account Identification   35x (Account)
			/^:25/ && $tagGruppe == 1 && do {
				my $buf = $_;
				$buf =~ s/^:25:(.{1,35})/$1/;
				$self->{ident}[$x] = $buf;

				$tagGruppe = 2;
				$lastTag = 25;
				$optionalTag = 0;
				last SWITCH;
			};

			#   M   28C   Statement Number/Sequence Number   Option C   5n[/5n] (Statement Number) (Sequence Number)
			/^:28/ && $tagGruppe == 2 && do {
				my $buf = $_;
				$buf =~ s/^:28C:(.{1,11})/$1/;
				my @bufAr = split("/",$buf);
				$self->{statement_Nr}[$x] = $bufAr[0];
				$self->{sequence_Nr}[$x] = $bufAr[1] if($bufAr[1]);

				$lastTag = 28;
				$tagGruppe = 3;
				last SWITCH;
			};

			#   M   60a   Opening Balance   F or M   Option F   1!a6!n3!a15d   (D/C Mark) (Date YYMMDD) (Currency ISO4217) (Amount)
			#                                        Option M   1!a6!n3!a15d   (D/C Mark) (Date YYMMDD) (Currency ISO4217) (Amount)
			#                                                                   D/C Mark must contain one of:
			#                                                                   C   The (intermediate) opening balance is a credit balance.
			#                                                                   D   The (intermediate) opening balance is a debit balance.
			/^:60/ && $tagGruppe == 3 && do {
				$_ =~ /^:60(M|F):(D|C)(\d{6})([A-Z]{3})([\d,]{1,15})/;
				my $option = $1;
				my $codes = $2;
				my $date = $3;
				my $currency = $4;
				my $amount = $5;
				$date =~ s/(\d{2})(\d{2})(\d{2})/$1-$2-$3/;
				$date = ParseDate($date);
				$amount =~ s/\.//g;
				$amount =~ s/,/\./;

				if($option eq "F") {
					$self->{first_opening_balance_DC_mark} = $codes unless($self->{first_opening_balance_DC_mark});
					$self->{first_opening_balance_date} = $date unless($self->{first_opening_balance_date});
					$self->{first_opening_balance_whg} = $currency unless($self->{first_opening_balance_whg});
					$self->{first_opening_balance_amount} = $amount unless($self->{first_opening_balance_amount});

					$self->{opening_balance_DC_mark}[$x] = $codes;
					$self->{opening_balance_date}[$x] = $date;
					$self->{opening_balance_whg}[$x] = $currency;
					$self->{opening_balance_amount}[$x] = $amount;
				}
				elsif($option eq "M") {
					$self->{opening_balance_DC_mark}[$x] = $codes;
					$self->{opening_balance_date}[$x] = $date;
					$self->{opening_balance_whg}[$x] = $currency;
					$self->{opening_balance_amount}[$x] = $amount;
				}
				else {
					print "Error in Tag 60\n";
				}

				$lastTag = 60;
				$tagGruppe = 4;
				last SWITCH;
			};

			#   ----->
			#   O   61   Statement Line   6!n[4!n]2a[1!a]15d1!a3!c16x[//16x][34x]
			#                              1   6!n     Value Date (YYMMDD)
			#                              2   [4!n]   Entry Date (MMDD)
			#                              3   2a      Debit/Credit Mark
			#                              4   [1!a]   Funds Code (3rd character of the currency code, if needed)
			#                              5   15d     Amount
			#                              6   1!a3!c  Transaction Type Identification Code
			#                              7   16x     Reference for the Account Owner
			#                              8   [//16x] Account Servicing Institution's Reference
			#                              9   [34x]   Supplementary Details
			/^:61/ && $tagGruppe == 4 && do {

				if($lastTag == 61 or $lastTag == 86) {
					$y++;
					$self->{StatementLines}[$x] = $y;
				}

				$_ =~ /^:61:(\d{6})(\d{4})?(D|C|RC|RD)([A-Z]{1})?([\d,]{1,15})(S|N|F)([0-9A-Z]{3})(.{1,16})(\/\/.{1,16})?(.{1,34})?$/;
				my $valueDate = $1;
				my $entryDate = $2 ? $2 : 0;
				my $dcMark = $3;
				my $fundsCode = $4 ? $4 : 0;
				my $amount = $5;
				my $transactionTyp = $6;
				my $transactionCode = $7;
				my $reference = $8;
				my $institutionRef = $9 ? $9 : 0;
				my $supplyDetails = $10 ? $10 : 0;

				$amount =~ s/\.//g;
				$amount =~ s/,/\./;
				$valueDate =~ s/(\d{2})(\d{2})(\d{2})/$1-$2-$3/;
				$valueDate = ParseDate("$valueDate");
				$self->{value_date}[$x][$y] = $valueDate;
				if($entryDate) {
					my $jahr = UnixDate($valueDate,'%Y');
					$entryDate =~ s/(\d{2})(\d{2})/$1-$2/;
					$entryDate = $jahr ."-". $entryDate;
					$entryDate = ParseDate("$entryDate");
					$self->{entry_date}[$x][$y] = $entryDate;
				}
				$self->{dc_mark}[$x][$y] = $dcMark;
				$self->{funds_code}[$x][$y] = $fundsCode if($fundsCode);
				$self->{amount}[$x][$y] = $amount;
				$self->{transaction_typ}[$x][$y] = $transactionTyp;
				$self->{transaction_code}[$x][$y] = $transactionCode;
				$self->{reference}[$x][$y] = $reference;
				$self->{institution_reference}[$x][$y] = $institutionRef if($institutionRef);
				$self->{supply_details}[$x][$y] = $supplyDetails if($supplyDetails);

				$lastTag = 61;
				last SWITCH;
			};

			#   O   86   Information to Account Owner   6*65x   See specification 7   (Narrative)
			#   -----|
			(/^:86/ || (!(/^:\d{2}/) && $lastTag == 86 && $z)) && $tagGruppe == 4 && do {

				my $buf = $_;
				$buf =~ s/(^:86:)?(.{1,65})/$2/;
				$self->{information_account}[$x][$y] = $self->{information_account}[$x][$y] ? "". $self->{information_account}[$x][$y] ."$buf" : "$buf";

				if($lastTag == 86) {
					$z--;
				} else {
					$z = 6;
				}

				$lastTag = 86;
				last SWITCH;
			};

			#   M   62a   Opening Balance  F or M   Option F   1!a6!n3!a15d   (D/C Mark) (Date YYMMDD) (Currency ISO4217) (Amount)
			#             (Booked Funds)            Option M   1!a6!n3!a15d   (D/C Mark) (Date YYMMDD) (Currency ISO4217) (Amount)
			#                                                                  D/C Mark must contain one of:
			#                                                                  C   The (intermediate) opening balance is a credit balance.
			#                                                                  D   The (intermediate) opening balance is a debit balance.
			/^:62/ && $tagGruppe == 4 && do {
				$_ =~ /^:62(M|F):(D|C)(\d{6})([A-Z]{3})([\d,]{1,15})/;
				my $option = $1;
				my $codes = $2;
				my $date = $3;
				my $currency = $4;
				my $amount = $5;
				$date =~ s/(\d{2})(\d{2})(\d{2})/$1-$2-$3/;
				$date = ParseDate($date);
				$amount =~ s/\.//g;
				$amount =~ s/,/\./;

				if($option eq "F") {
					$self->{final_closing_balance_DC_mark} = $codes;
					$self->{final_closing_balance_date} = $date;
					$self->{final_closing_balance_whg} = $currency;
					$self->{final_closing_balance_amount} = $amount;

					$self->{closing_balance_DC_mark}[$x] = $codes;
					$self->{closing_balance_date}[$x] = $date;
					$self->{closing_balance_whg}[$x] = $currency;
					$self->{closing_balance_amount}[$x] = $amount;
				}
				elsif($option eq "M") {
					$self->{closing_balance_DC_mark}[$x] = $codes;
					$self->{closing_balance_date}[$x] = $date;
					$self->{closing_balance_whg}[$x] = $currency;
					$self->{closing_balance_amount}[$x] = $amount;
				}
				else {
					print "Error in Tag 62\n";
				}

				$lastTag = 62;
				$tagGruppe = 5;
				last SWITCH;
			};

			#   M   64   Closing Available Balance   1!a6!n3!a15d   (D/C Mark) (Date YYMMDD) (Currency ISO4217) (Amount)
			#            (Available Funds)                           D/C Mark must contain one of:
			#                                                        C   The (intermediate) opening balance is a credit balance.
			#                                                        D   The (intermediate) opening balance is a debit balance.
			/^:64/ && $tagGruppe == 5 && do {
				$_ =~ /^:64:(D|C)(\d{6})([A-Z]{3})([\d,]{1,15})/;
				my $codes = $2;
				my $date = $3;
				my $currency = $4;
				my $amount = $5;
				$date =~ s/(\d{2})(\d{2})(\d{2})/$1-$2-$3/;
				$date = ParseDate($date);
				$amount =~ s/\.//g;
				$amount =~ s/,/\./;

				$self->{closing_available_balance_DC_mark}[$x] = $codes;
				$self->{closing_available_balance_date}[$x] = $date;
				$self->{closing_available_balance_whg}[$x] = $currency;
				$self->{closing_available_balance_amount}[$x] = $amount;

				$lastTag = 64;
				$tagGruppe = 6;
				last SWITCH;
			};

			#   ---->
			#   O   65   Forward Available Balance   1!a6!n3!a15d   (D/C Mark) (Date YYMMDD) (Currency ISO4217) (Amount)
			#                                                        D/C Mark must contain one of:
			#                                                        C   The (intermediate) opening balance is a credit balance.
			#                                                        D   The (intermediate) opening balance is a debit balance.
			#   ----|
			/^:65/ && $tagGruppe == 6 && do {
				if($lastTag == 65) {
					$y++;
					$self->{forward_Available_Lines}[$x] = $y;
				} else {
					$y = 0;
					$self->{forward_Available_Lines}[$x] = $y;
				}
				$_ =~ /^:64:(D|C)(\d{6})([A-Z]{3})([\d,]{1,15})/;
				my $codes = $2;
				my $date = $3;
				my $currency = $4;
				my $amount = $5;
				$date =~ s/(\d{2})(\d{2})(\d{2})/$1-$2-$3/;
				$date = ParseDate($date);
				$amount =~ s/\.//g;
				$amount =~ s/,/\./;

				$self->{forward_available_balance_DC_mark}[$x][$y] = $codes;
				$self->{forward_available_balance_date}[$x][$y] = $date;
				$self->{forward_available_balance_whg}[$x][$y] = $currency;
				$self->{forward_available_balance_amount}[$x][$y] = $amount;

				$lastTag = 65;
				last SWITCH;
			};

			#   O   86   Information to Account Owner   6*65x   (Narrative)
			(/^:86/ || (!(/^:\d{2}/) && $lastTag == 86 && $z)) && $tagGruppe == 6 && do {
				my $buf =~ s/^(:86:)?(.{1,65})/$1/;
				chomp($buf);
				$self->{information_account_2}[$x] = "". $self->{information_account_2}[$x] ."$buf";

				if($lastTag == 86) {
					$z--;
				} else {
					$z = 6;
					$lastTag = 86;
				}
				last SWITCH;
			};

			print "\nSWIFT Format Error !\n";

		}
    }
    close(DATA);

    return;
}

sub transactionLines # ( )
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{TransactionLines} = $wert;
		}
    }

    return $self->{TransactionLines};
}

sub transactionRef # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{transaction_Ref}[$x] = $wert;
		}
    }

    return $self->{transaction_Ref}[$x];
}

sub reference # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{reference}[$x] = $wert;
		}
    }

    return $self->{reference}[$x];
}

sub accountIdentification # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{ident}[$x] = $wert;
		}
    }

    return $self->{ident}[$x];
}

sub statementNr # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{statement_Nr}[$x] = $wert;
		}
    }

    return $self->{statement_Nr}[$x];
}

sub sequenceNr # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{sequence_Nr}[$x] = $wert;
		}
    }

    return $self->{sequence_Nr}[$x];
}

sub firstOpeningBalanceCode
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{first_opening_balance_DC_mark} = $wert;
		}
    }

    my $ret = $self->{dcCodes}{$self->{first_opening_balance_DC_mark}};
    return $ret;
}

sub firstOpeningBalanceDate # ( [Format], [Datum] )
{
    my $self = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{first_opening_balance_date} = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{first_opening_balance_date},'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{first_opening_balance_date},'%d.%m.%Y');
	}

    return $datum;
}

sub firstOpeningBalance
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		my $whg = shift;

		if($wert) {
			$wert =~ s/\.//g;
			$wert =~ s/,/\./;
			$self->{first_opening_balance_amount} = $wert;
		}

		if($whg) {
			$self->{first_opening_balance_whg} = $whg;
		}
    }


    return($self->{first_opening_balance_amount},$self->{first_opening_balance_whg});
}

sub openingBalanceCode # ( x )
{
    my $self = shift;
	my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{opening_balance_DC_mark}[$x] = $wert;
		}
    }

    my $ret = $self->{dcCodes}{$self->{opening_balance_DC_mark}[$x]};
    return $ret;
}

sub openingBalanceDate # ( x, [Format], [Datum] )
{
    my $self = shift;
	my $x = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{opening_balance_date}[$x] = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{opening_balance_date}[$x],'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{opening_balance_date}[$x],'%d.%m.%Y');
	}

    return $datum;
}

sub openingBalance # ( x )
{
    my $self = shift;
	my $x = shift;

    if(@_) {
		my $wert = shift;
		my $whg = shift;

		if($wert) {
			$wert =~ s/\.//g;
			$wert =~ s/,/\./;
			$self->{opening_balance_amount}[$x] = $wert;
		}

		if($whg) {
			$self->{opening_balance_whg}[$x] = $whg;
		}
    }


    return($self->{opening_balance_amount}[$x],$self->{opening_balance_whg}[$x]);
}

sub statmentLines # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{StatementLines}[$x] = $wert;
		}
    }

    return $self->{StatementLines}[$x];
}

sub valueDate # ( x, y, [Format], [Datum] )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{value_date}[$x][$y] = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{value_date}[$x][$y],'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{value_date}[$x][$y],'%d.%m.%Y');
	}
    return $datum;
}

sub entryDate # ( x, y, [Format], [Datum] )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{entry_date}[$x][$y] = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{entry_date}[$x][$y],'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{entry_date}[$x][$y],'%d.%m.%Y');
	}
    return $datum;
}

sub statementCode # ( x , y )
{
    my $self = shift;
	my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{dc_mark}[$x][$y] = $wert;
		}
    }

    my $ret = $self->{dcCodes}{$self->{dc_mark}[$x][$y]};
    return $ret;
}

sub fundsCode # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{funds_code}[$x][$y] = $wert;
		}
    }

    return $self->{funds_code}[$x][$y];
}

sub amount # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$wert =~ s/\.//g;
			$wert =~ s/,/\./;
			$self->{amount}[$x][$y] = $wert;
		}
    }

    return $self->{amount}[$x][$y];
}

sub transactionTyp # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{transaction_typ}[$x][$y] = $wert;
		}
    }

    return $self->{transaction_typ}[$x][$y];
}

sub transactionCode # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{transaction_code}[$x][$y] = $wert;
		}
    }

    return $self->{transaction_code}[$x][$y];
}

sub statementRef # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{reference}[$x][$y] = $wert;
		}
    }

    return $self->{reference}[$x][$y];
}

sub institutionRef # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{institution_reference}[$x][$y] = $wert;
		}
    }

    return $self->{institution_reference}[$x][$y];
}

sub supplayDetails # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{supply_details}[$x][$y] = $wert;
		}
    }

    return $self->{supply_details}[$x][$y];
}

sub informationAccount # ( x , y )
{
    my $self = shift;
    my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{information_account}[$x][$y] = $wert;
		}
    }

    return $self->{information_account}[$x][$y];
}

sub finalClosingBalanceCode
{
    my $self = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{final_closing_balance_DC_mark} = $wert;
		}
    }

    my $ret = $self->{dcCodes}{$self->{final_closing_balance_DC_mark}};
    return $ret;
}

sub finalClosingBalanceDate # ( [Format], [Datum] )
{
    my $self = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{final_closing_balance_date} = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{final_closing_balance_date},'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{final_closing_balance_date},'%d.%m.%Y');
	}

    return $datum;
}

sub finalClosingBalance
{
    my $self = shift;

    if(@_) {
		my $wert = shift;
		my $whg = shift;

		if($wert) {
			$wert =~ s/\.//g;
			$wert =~ s/,/\./;
			$self->{final_closing_balance_amount} = $wert;
		}

		if($whg) {
			$self->{final_closing_balance_whg} = $whg;
		}
    }

    return($self->{final_closing_balance_amount},$self->{final_closing_balance_whg});
}

sub closingBalanceCode # ( x )
{
    my $self = shift;
	my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{closing_balance_DC_mark}[$x] = $wert;
		}
    }

    my $ret = $self->{dcCodes}{$self->{closing_balance_DC_mark}[$x]};
    return $ret;
}

sub closingBalanceDate # ( x, [Format], [Datum] )
{
    my $self = shift;
	my $x = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{closing_balance_date}[$x] = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{closing_balance_date}[$x],'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{closing_balance_date}[$x],'%d.%m.%Y');
	}

    return $datum;
}

sub closingBalance # ( x )
{
    my $self = shift;
	my $x = shift;

    if(@_) {
		my $wert = shift;
		my $whg = shift;

		if($wert) {
			$wert =~ s/\.//g;
			$wert =~ s/,/\./;
			$self->{closing_balance_amount}[$x] = $wert;
		}

		if($whg) {
			$self->{closing_balance_whg}[$x] = $whg;
		}
    }


    return($self->{closing_balance_amount}[$x],$self->{closing_balance_whg}[$x]);
}

sub closingAvailableBalanceCode # ( x )
{
    my $self = shift;
	my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{closing_available_balance_DC_mark}[$x] = $wert;
		}
    }

    my $ret = $self->{dcCodes}{$self->{closing_available_balance_DC_mark}[$x]};
    return $ret;
}

sub closingAvailableBalanceDate # ( x, [Format], [Datum] )
{
    my $self = shift;
	my $x = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{closing_available_balance_date}[$x] = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{closing_available_balance_date}[$x],'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{closing_available_balance_date}[$x],'%d.%m.%Y');
	}

    return $datum;
}

sub closingAvailableBalance # ( x )
{
    my $self = shift;
	my $x = shift;

    if(@_) {
		my $wert = shift;
		my $whg = shift;

		if($wert) {
			$wert =~ s/\.//g;
			$wert =~ s/,/\./;
			$self->{closing_available_balance_amount}[$x] = $wert;
		}

		if($whg) {
			$self->{closing_available_balance_whg}[$x] = $whg;
		}
    }


    return($self->{closing_available_balance_amount}[$x],$self->{closing_available_balance_whg}[$x]);
}

sub forewardAvailableLines # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{forward_Available_Lines}[$x] = $wert;
		}
    }

    return $self->{forward_Available_Lines}[$x];
}

sub forewardAvailableBalanceCode # ( x , y )
{
    my $self = shift;
	my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{forward_available_balance_DC_mark}[$x][$y] = $wert;
		}
    }

    my $ret = $self->{dcCodes}{$self->{forward_available_balance_DC_mark}[$x][$y]};
    return $ret;
}

sub forewardAvailableBalanceDate # ( x, y, [Format], [Datum] )
{
    my $self = shift;
	my $x = shift;
	my $y = shift;
	my $format = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{forward_available_balance_date}[$x][$y] = ParseDate($wert);
		}
    }

	my $datum;
	if($format && $format eq "iso8601") {
		$datum = UnixDate($self->{forward_available_balance_date}[$x][$y],'%Y-%m-%d');
	} else {
		$datum = UnixDate($self->{forward_available_balance_date}[$x][$y],'%d.%m.%Y');
	}

    return $datum;
}

sub forewadAvailableBalance # ( x , y )
{
    my $self = shift;
	my $x = shift;
	my $y = shift;

    if(@_) {
		my $wert = shift;
		my $whg = shift;

		if($wert) {
			$wert =~ s/\.//g;
			$wert =~ s/,/\./;
			$self->{forward_available_balance_amount}[$x][$y] = $wert;
		}

		if($whg) {
			$self->{forward_available_balance_whg}[$x][$y] = $whg;
		}
    }


    return($self->{forward_available_balance_amount}[$x][$y],$self->{forward_available_balance_whg}[$x][$y]);
}

sub accountInfomation2 # ( x )
{
    my $self = shift;
    my $x = shift;

    if(@_) {
		my $wert = shift;

		if($wert) {
			$self->{information_account_2}[$x] = $wert;
		}
    }

    return $self->{information_account_2}[$x];
}


1;
