#! /usr/bin/perl
use warnings;
use strict;

our $Marvell_Symlink = `ls /dev/MARVELL:* 2>&1`;
if ($Marvell_Symlink eq "ls: cannot access /dev/MARVELL:*: No such file or directory\n")
{
	#Get Marvell devices from lsusb command
	print ("Checking if any Marvell devices plugged in...\n");
	my $Marvell_Devices = `lsusb | grep '1286'`;
	if($Marvell_Devices ne "")
	{
		my @MarvellDeviceTokens = split(/\s+/, $Marvell_Devices);		
		my @VidPidTokens = split(':',$MarvellDeviceTokens[5]);
		#foreach my $token (@VidPidTokens)
		#{ 
		#	print ($token,"\n");
		#}
		$Marvell_Symlink = `sudo modprobe -r ftdi_sio`;
		$Marvell_Symlink = `sudo modprobe usbserial vendor=0x$VidPidTokens[0] product=0x$VidPidTokens[1]`;
		$Marvell_Symlink = `sudo restart udev`;
		
		print "Marvell device connected!\n";
	}
	else
	{
		print ("No Marvell devices plugged in. Quiting.\n");
	}
}
else
{
	print("Marvell device connected:$Marvell_Symlink\n");
}
