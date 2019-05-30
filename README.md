# eject_usb-ubuntu
kiaora,

A brave attempt to create a terminal command for ejecting usb drives without having to know the device name such as /dev/sda
it read from intenal files such as ftabs to get a list of mounted file in the system.
Then if an agrument is passed, it unmouts it; 
If there is only one device mounted it unmouts it without need of an argument.

compite main.cpp with the gcc.



TODO

make compatible on other linux distros

Needs an intaller bash script to intall the autocomplete file for eject_usb 

Change the name to eject_usb.

Test to see if it works in all devices .

Find the way that in which file manajers, such as Nautilus and Caje eject usb drive and impemet it. 
