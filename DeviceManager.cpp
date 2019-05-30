#include <bits/stdc++.h>
#include <unistd.h>
#include <dirent.h>
#include "Device.h"
#include "DeviceManager.h"


DeviceManager::DeviceManager(){

			//device array
		std::vector<Device> devices              ;
		std::vector<std::string> allowed_types   ;
			//file_paths
		std::string mnts_file_path        = "n/a";
		std::string disk_id_path          = "n/a";
		std::string disk_label_path       = "n/a";
			//regex format
		std::regex type_regex                    ;
		std::regex des_regex                     ;
		std::regex devpath_regex                 ;
		std::regex mpoint_regex                  ;
		std::regex fs_regex                      ;
		std::regex other_regex                   ;

} 


DeviceManager::DeviceManager(std::string type_str_regex,
														 std::string des_str_regex,
														 std::string devpath_str_regex,
														 std::string mpoint_str_regex,
														 std::string fs_str_regex,
														 std::string other_str_regex,
														 std::vector<std::string> allowed){
		
		allowed_types = allowed;
		type_regex    = std::regex(type_str_regex);
		des_regex     = std::regex(des_str_regex); 
		devpath_regex = std::regex(devpath_str_regex);
    mpoint_regex  = std::regex(mpoint_str_regex); 
    fs_regex     	= std::regex(fs_str_regex);
    other_regex  = std::regex(other_str_regex); 
} 



std::vector<std::string> filter_file_lines(std::string mount_point,
                                         	 std::string usrname,
                                         	 std::vector<std::string> &devs){

	/*Filters te line of the mounts file using the usr name and mount point
		 to detemin if the are correct*/

 	std::string token = mount_point + usrname;

  for(std::vector<std::string>::iterator dev = devs.begin(); dev != devs.end();){
      if((*dev).find(token) == std::string::npos) dev = devs.erase(dev);
      else dev++;
  }

  return devs;
}



std::string link_dest(std::string link){
	/*return the destination of a symbilc link in linux system*/
	const char* symbolic_link = link.c_str();
	char link_dest[PATH_MAX];
	char resolved_path[PATH_MAX]; 
	ssize_t len;
	std::string strbuff;
	

	if ((len = readlink(symbolic_link, link_dest, sizeof(link_dest)-1)) != -1){
		//if it was able to read link
    link_dest[len] = '\0';
  	realpath(link_dest, resolved_path); 
		
		strbuff = std::string(resolved_path);
			
		return strbuff;
	}else{
		std::cout << "error " << std::strerror(errno) << '\n';
		return NULL;
	}
}

bool is_in_vector(std::string str, std::vector<std::string> vec){
	//simple fuction that retunr true is string is in vector
	for(int i =0; i < vec.size(); i++)
			if( str == vec[i]) return true;
	return false;
}

std::string sanitize_mpoint(std::string match){
	/*some espacial charactes are hard to read by
		 mount it is better to not have them*/
	std::string out = std::regex_replace(match, std::regex("\\\\x20"), "\x20");
	out = std::regex_replace(out, std::regex("\\\\040"), "\x20");
  //std::cout << "out: " << out << std::endl;
	return out;
}

std::string sanitize_label(std::string match){
	/*some espacial charactes are hard to read by
		 mount it is better to not have them*/
	std::string out = std::regex_replace(match, std::regex("\\\\x20"), "\x20");
	out = std::regex_replace(out, std::regex(" "), "\x20");
	out = std::regex_replace(out, std::regex("\\\\040"), "\x20");
	out = std::regex_replace(out, std::regex("\\040"), "\x20");
	out = std::regex_replace(out, std::regex("040"), "\x20");
  //std::cout << "out: " << out << std::endl;
	return out;
}

std::string regex_match_get(std::string input_str, std::regex rgx){
	/*get the matching regex section in an input string*/
 
	std::smatch match;
	const std::string str = (const std::string)input_str;
	try {
 		if(std::regex_search(str.begin(), str.end(), match, rgx)){
			return match[1];	
		}else{	
    	std::cerr << "Urk! unable to macth regex to system files line: " << input_str << std::endl;
			return NULL;
		}		
		
	}catch (const std::regex_error& e) {
    	 std::cerr << "Urk! unable to macth regex to system files line: " << input_str << std::endl;
       std::cout << "regex_error caught: " << e.what() << '\n';
       //if (e.code() == std::regex_constants::error_brack) {
            //std::cout << "The code was error_brack\n";
		return NULL;
		}
}


bool DeviceManager::get_devs_by_disk_dir(std::string id_path){
	disk_id_path = id_path;
	
	std::string link_path, dev_type_buff;
	Device device;

		//change working dir to given dir
	if(chdir(id_path.c_str()) != 0) 
		 std::cout << "error " << std::strerror(errno) << '\n';

	if (auto dir = opendir(id_path.c_str())) {
    while (auto f = readdir(dir)) {
        if (!f->d_name || f->d_name[0] == '.') continue; 
					//Skip everything that starts with a dot

		
				else{
						//look a the type of the device
           dev_type_buff = regex_match_get(f->d_name, type_regex);
						//if dev is part of the allowed device
					 if(is_in_vector(dev_type_buff, allowed_types)){

								//make device
							device =  Device(); 
							
					  		//get id
							std::string dname(f->d_name);
							device.set_id(dname);

								//get type
							device.set_type(regex_match_get(dname, type_regex));

								//get descrition
							device.set_des(regex_match_get(dname, des_regex));

								//get abusolute link destination 
							link_path = disk_id_path + "/" + device.get_id();
							device.set_devpath(link_dest(link_path));

								//save device obj
							devices.push_back(device);
						}		
					}
    	}
    closedir(dir);

	}


	//std::cout << devices.size() << " devices found" << std::endl;
	return (devices.size() > 0) ? true : false;		
}

bool DeviceManager::update_devs_label(std::string label_path){
	disk_label_path = label_path;
	
	int labeled_c = 0;
	std::string label, link_path, cur_devpath;
	Device devbuff;

		//change working dir to given dir
	if(chdir(label_path.c_str()) != 0) 
		 std::cout << "error " << std::strerror(errno) << '\n';

	if (auto dir = opendir(label_path.c_str())) {
    while (auto f = readdir(dir)) {
        if (!f->d_name || f->d_name[0] == '.') continue; 
					//Skip everything that starts with a dot
				
					label = (std::string)f->d_name;

						//get abusolute link destination 
					link_path = disk_label_path + "/" + label;
					cur_devpath = link_dest(link_path);
			
							//update dev which have the same dev_path
						for(int i = 0; i < devices.size(); i++)
							if(devices[i].get_devpath() == cur_devpath){
									//set label
								devices[i].set_label(sanitize_label(label));
									//set as mounted only if label has be found
									//devices[i].set_as_mounted();
								labeled_c++;
							}	
				}
    	closedir(dir);
    }

	//std::cout << labeled_c << " devices found" << std::endl;
	return (labeled_c > 0) ? true : false;		
}

bool DeviceManager::update_devs_mnt_file(std::string file_path){
		//intiate Devices by suing the file path of /proc/self/mounts [ubuntu]
	mnts_file_path  = file_path;

	int devs_updated = 0;
	std::string strbuff, cur_devpath, mpoint_buff;
	std::ifstream file(file_path);

	//Read from mount file in /proc/self/mounts to get the mounted devices	
	while(getline(file, strbuff)){
		
		cur_devpath = regex_match_get(strbuff, devpath_regex);
		for(int i = 0; i < devices.size(); i++){
			//match with device_path
			
			if(devices[i].get_devpath() == cur_devpath){
					
					//update mount point
				mpoint_buff = regex_match_get(strbuff, mpoint_regex);
				devices[i].set_mpoint  (sanitize_mpoint(mpoint_buff));
					//update file system
				devices[i].set_fs      (regex_match_get(strbuff, fs_regex));
					//update other
				devices[i].set_other   (regex_match_get(strbuff, other_regex));
					//set as mounted
				devices[i].set_as_mounted();
			}
		}
	}
		return (devs_updated > 0) ? true : false;		

}

bool DeviceManager::unmount(std::string label){
	//unmount the device which matches the label


	for(auto dev : devices){
		
		if(dev.get_label() == label){

			dev.unmount();
			return true;
		}
	}
	std::cout << "Unable to find that label: " << label << std::endl;
	return false;
}


void DeviceManager::print_devs(){
		for(auto dev : devices)
			dev.print();
}

void DeviceManager::print_mounted_labels(){
		for(auto dev : devices)
			if(dev.is_mounted())
				std::cout << dev.get_label() << std::endl;
			
}	
