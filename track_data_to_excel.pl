#####################################################################################
# module name  : track_data_to_excel.pl
# call method  : perl track_data_to_excel.pl file_name
# write date   : 2010.06.13
# write author : JMS
# Description  : After Text file read, create Excel file.
#                error return -1, success return Excel filename
####################################################################################
#!/usr/bin/perl -w

use strict;
use Spreadsheet::WriteExcel;

my $file_name = $ARGV[0];
my $save_name = $ARGV[1];

if ($#ARGV == -1) {
   die "-1";
}

eval {
	# Create a new workbook called simple.xls and add a worksheet.
	# my $workbook  = Spreadsheet::WriteExcel->new('track_data_excel.xls');
	my $workbook  = Spreadsheet::WriteExcel->new($save_name);
	my $worksheet = $workbook->add_worksheet();

	# The general syntax is write($row, $column, $token).
	# Note that row and column are zero indexed.

	open (CHECKBOOK, "track_tmp.txt");

	my $idx = 0;
	while (my $record = <CHECKBOOK>) {
   	   #print $record;
   	   my @arr = split /,/, $record;
   
   	   for (my $i = 0; $i <= $#arr; $i++) {
          #print $arr[$i];
       	  $worksheet->write($idx, $i, $arr[$i]);
            }
       $idx++;
	}
	close(CHECKBOOK);
};

if ($@)
{
   print "-1";
   #print $@;
   undef($@);
}else {
   print "track_data_excel.xls";
}
exit;
