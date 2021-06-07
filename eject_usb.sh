#!/bin/bash

#short program that is use to automate the ejecting from the terminal a flash drive. it calls lsblk to look for the pendrive that you have the it calls eject


LABLE=$1
#get the os ID_LIKE fof the system to know is it is fedora or debian
OS=$(cat /etc/os-release | grep ID_LIKE | cut -d\" -f2)

#get the mounted devices
DEVS=$(lsblk -i | tr -s ' ' | cut -d ' ' -f 1,7  | grep - | grep -v sda | grep -v loop)

#get the mounted dev labels
M_DEV=$(lsblk -i | tr -s ' ' | cut -d ' ' -f 1,7  | grep - | grep -v sda | grep -v loop | rev | cut -d/ -f1 | rev)

# Debuging 
#echo $DEVS
#echo $M_DEV

if [ -z "$DEVS" ]; then 
	echo "Thre are no devices"
	echo "Try mounting somthing, buddy"
	exit 0
fi 


if [ $# -gt 0 ]; then 
	#if a parameter was given 
	
	USB=$( lsblk -i | grep $LABLE | tr -d \- | tr -d \| | tr -d \` | cut -d' ' -f1 )
	
	if [ -z  "$USB" ];then 
		#if the USB with the given parameter was not found 
		
		echo "could not find Lable: $LABLE, Try on of these"
		echo $M_DEV
		exit 0
	else	
		sudo umount "/dev/$USB" && echo " $LABLE ejected successfuly"
	fi

else

	if [ `echo $M_DEV | wc -w` -gt 1 ]; then 
		#else if there are more than one devices
		echo "Which devices would you like to eject?"
		for i in $M_DEV
		do 
			echo "-> $i"
		done
	exit 0

	elif [ `echo $M_DEV | wc -w` -eq 1 ]; then 
		#if there is only one device in /dev
		LABLE=$( echo "$DEVS" | rev | cut -d/ -f1 | rev )
		USB=$( echo "$DEVS" | tr -d \- | tr -d \| | tr -d \` | cut -d' ' -f1 )
		# grep -oh '[a-z]\{3\}[1-9]'
		echo "Ejecting $LABLE..."
		#echo "USB: $USB"
		sudo umount "/dev/$USB" && echo " $LABLE ejected successfuly"

	fi	
fi
 
exit 1
