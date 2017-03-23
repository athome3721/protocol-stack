#! /bin/bash
set +e
if [ -n "$1" ]
then
/sbin/modprobe usbserial vendor=$1 product=$2
else
/sbin/rmmod usbserial
fi
set -e
exit
