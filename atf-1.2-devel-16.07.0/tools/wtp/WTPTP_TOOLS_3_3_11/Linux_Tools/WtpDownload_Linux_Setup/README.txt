********************************************
USB serial driver Setup for Marvell devices
********************************************
Steps 1 to 4 need to be done only once on a linux system to setup the USB serial driver with Marvell devices.
Step 5 has to be executed whenever a new Marvell device type is plugged in into the system
1.  Ensure you have root or sudo permissions on the linux machine.

2.  Ensure 10-local.rules file has read/write permissions for all users.
		-> $chmod 0666 10-local.rules

3.	Give execute permissions for all users to the MarvellModProbe.pl script file.
		-> $chmod a+x MarvellModProbe.pl

4. 	Copy and paste the 10-local.rules file in /etc/udev/rules.d folder. 		
		-> $sudo cp 10-local.rules /etc/udev/rules.d/
		
5.	Run MarvellModProbe.pl
		-> $./MarvellModProbe.pl
	Check for the message: "Marvell device connected:MARVELL:<DEVICENAME>:<NUM>"
	If the message is not displayed, open the 10-local.rules file and check if the device type exists in the file. See step 1 in 
	"Adding a new MARVELL device to 10-local.rules file" section below.

Once the Marvell device is set up WtpDownload_linux.exe can be executed. Please refer to the WTPTP_Reference_Manual for WtpDownload_linux.exe usage.

*********************************************************
Adding a new MARVELL device to 10-local.rules file
*********************************************************
1. 	Plug in the new Marvell device
	
	For example let the new Marvell device have a productID = 0xABCD. 
	The VendorID for Marvell devices is fixed which is 0x1286.
	The VendorID and ProductID can be obtained by running "lsusb" command on the command prompt.
	The fifth column in the output of "lsusb" command is a combination of two hexadecimal numbers such as 1286:192A which is the VendorID:ProductID
	A Marvell device is recognized by VendorID:ProductID combination: "1286:<hexadecimal number>".
	Make a note of the <hexadecimal number> which is the ProductID of the Marvell device that you have plugged in. 
	In reference to this example you should see a line in the "lsusb" command output with VendorID:ProductID combination equal to 1286:ABCD
	
2. 	Open the 10-local.rules file. Check if the file has a line similar to the below line
	SUBSYSTEM=="tty", ATTRS{idVendor}=="1286", ATTRS{idProduct}=="ABCD", MODE="0666", SYMLINK+="MARVELL:Device_Name:%n"
	
	If the line exists then exit from the file. Go to step 4.
	
3.	If such a line does not exists in 10-local.rules file then add the below line to the end of 10-local.rules file:
	SUBSYSTEM=="tty", ATTRS{idVendor}=="1286", ATTRS{idProduct}=="ABCD", MODE="0666", SYMLINK+="MARVELL:Device_Name:%n"
	
	Replace the <Device_Name> part in the SYMLINK field with a string with no spaces or with a string with underscore as a delimiters that you would like to recognize the Marvell device with.

4.	Follow the steps of "USB serial driver Setup for Marvell devices" section