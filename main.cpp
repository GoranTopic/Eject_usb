#include <iostream>
#include "DeviceManager.h"
#include <sys/mount.h>



using namespace std;

std::string sanitize_input(std::string input){
  /*some espacial charactes are hard to read by
      mount it is better to not have them*/
   std::string out = std::regex_replace(input, std::regex(" "), "\x20");
   	out = std::regex_replace(out, std::regex("\\\\x20"), "\x20");
		out = std::regex_replace(out, std::regex("\\\\040"), "\x20");
    out = std::regex_replace(out, std::regex("040"), "\x20");
   	//std::cout << "out: " << out << std::endl;
   return out;
 }


int main(int argc, char* argv[]){

	string input;
		/*path were to find the systme files which 
			have the mount information*/
	string mounts_file_path = "/proc/self/mounts";
	string disk_id_path     = "/dev/disk/by-id";
	string disk_label_path  = "/dev/disk/by-label";

		//types of disks to allow
	vector<string> allowed_types= { "usb" };

		/*regex format how to read the system files
			into atributes of the devices */
	string type_str_regex    = "^(\\-?([^\\-]+)){1}\\-?.*$"   	; 
	string des_str_regex     = "\\-([^\\-]+)\\-?.*$"			    	;
	string devpath_str_regex = "^(?:[^\\s]+\\s){0}([^\\s]+)\\s" ;
	string mpoint_str_regex  = "^(?:[^\\s]+\\s){1}([^\\s]+)\\s" ;
	string fs_str_regex      = "^(?:[^\\s]+\\s){2}([^\\s]+)\\s" ;
	string other_str_regex   = "^(?:[^\\s]+\\s){3}([^\\s]+)\\s" ;
                             
	string usrname = getenv("USER");

	DeviceManager devmgr =  DeviceManager(type_str_regex,
																				 des_str_regex,
																				 devpath_str_regex,
                                         mpoint_str_regex,
                                         fs_str_regex,
                                     		 other_str_regex, 
																				 allowed_types);


	devmgr.get_devs_by_disk_dir(disk_id_path);
	devmgr.update_devs_label(disk_label_path);
	devmgr.update_devs_mnt_file(mounts_file_path);
	//devmgr.print_devs();
		if(argc > 1){ //if arguments given
			for(int i = 1; i < argc; i++){				
				input = sanitize_input( (string)argv[i] );
				cout << input << endl;
				devmgr.unmount(input);
			}

		}else devmgr.print_mounted_labels();
}
