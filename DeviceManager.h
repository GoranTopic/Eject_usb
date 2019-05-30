#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <vector>
#include <string>
#include <regex>
#include "Device.h"


class DeviceManager {
  private:

			//devices array
		std::vector<Device> devices;
		std::vector<std::string> allowed_types;

			//path to system files
		std::string mnts_file_path;
		std::string disk_id_path;
		std::string disk_label_path;

			//format for reading files
		std::regex type_regex;
		std::regex des_regex;
		std::regex devpath_regex;
		std::regex mpoint_regex;
		std::regex fs_regex;
		std::regex other_regex;

  public:
 				//empty contructur 
  		DeviceManager();
				
			DeviceManager(std::string disk_type_regex,
										std::string disk_des_regex,
	              		std::string devpath_regex, 
	              		std::string mpoint_regex, 
	              		std::string fs_regex, 
	              		std::string other_regexa,
										std::vector<std::string> allowed_types);


			bool get_devs_by_disk_dir(std::string disk_id_path); 

			bool update_devs_label(std::string disk_label_path);

			bool update_devs_mnt_file(std::string mnt_file_path);

			bool get_devs_by_mnts_file(std::string mnt_file_path); 
		
			bool unmount(std::string to_umount);	
				
			void print_devs();
		
			void print_mounted_labels();


		};
 
#endif
