# eject_usb 

Kiaora,

This is a brave attempt to create a terminal command for ejecting usb drives without having to know the device name such as /dev/sda
it read from intenal files such as ftabs to get a list of mounted file in the system.

Ususally the unix `umount` command need to take an device path such as `/dev/sda` or a mount point such as `/media/USERNAME/useb-label`.
This can be rather tedious when you just want to eject a fash drive quicky.

Thus eject_usb is a command that does not take any input to unmount the flashdrive you just inserted. 

Then if an agrument is passed, is searches the label or mountpoint and unmounts it.  

If there is only one device mounted it unmouts it without need of an argument, or the need to prop the user.

If there are multiple mdevices mounted, eject_usb will ask you which one to eject.

### Versions

I wrote two versions of the program, on ins C plus plus and an other in Shell. 


## Use
### CPP
The cpp version can be run with the executable "USBunmount" such as: `./USBunmount`
### Bash 
the Bash version can be run wit `./eject_usb.sh`
 
## Compile
To compile the program, you can run:
`g++ main.cpp -o USBunmount`  with the gcc.

## Install
To install in a linux eviroment simply move the executable to your bin dir.
Such as:

`cp USBunmount ~/bin/`

or 

`cp eject_usb.sh ~/bin/` 


## TODO

- [X] make Bash version

- [ ] make compatible on other linux distros

- [ ] Needs an intaller bash script to intall the autocomplete file for eject_usb 

- [ ] Change the name to eject_usb.

- [ ] Test to see if it works in all devices .

- [ ] Find the way that in which file manajers, such as Nautilus and Caje eject usb drive and impemet it. 
