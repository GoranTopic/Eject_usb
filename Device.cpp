	}
	}
void Device::set_other      (std::string new_other  ){ other   = new_other  ; }
	std::cout <<  "mpoint : " << mpoint  << std::endl; 
		
		
		mpoint = tokens[1];
	std::cout <<  "label  : " << label   << std::endl; 
//setter fuctions
	std::cout <<  "id     : " << id      << std::endl; 
    tokens.push_back(token);
  if (!umount(usb)){
	
	
	
    str.erase(0, pos + delimiter.length());
	std::cout <<  "type   : " << type    << std::endl; 
//getter fuctions
std::string Device::get_type()   { return type;     }
		other = tokens[3];
#include <bits/stdc++.h>
    std::cout << "Can't unmount " << strerror(errno) << std::endl;  
  const char* usb = mpoint.c_str();
		devpath = tokens[0];
		//can't unmount somthing that isnt mounted
						<< " usb: " << usb << std::endl
}
}
}
		return true;
void Device::set_type       (std::string new_type   ){ type    = new_type   ; }
	while ((pos = str.find(delimiter)) != std::string::npos) {
std::string Device::get_other()  { return other;    }
std::string Device::get_devpath(){ return devpath;  }
	std::cout <<  "devpath: " << devpath << std::endl; 
  }
	std::cout <<  "des    : " << des     << std::endl; 
	std::cout <<  "device mounted: " << mounted  << std::endl; 
  std::cout << "atempting to unmount labeled: " << label 
		fs = tokens[2];
void Device::print(){
		std::cout << devpath; 
std::string Device::get_id()     { return id;       }
void Device::set_des        (std::string new_des    ){ des     = new_des    ; }
  }else{
Device::Device(std::string str){
bool        Device::is_mounted()  { return mounted; }
    token = str.substr(0, pos);
bool Device::unmount(){
void Device::set_fs         (std::string new_fs     ){ fs      = new_fs     ; }
Device::Device(){
	std::cout <<  "other  : " << other   << std::endl; 
	std::cout <<  "fs     : " << fs      << std::endl; 
} 
std::string Device::get_label()  { return label;    }
	std::vector<std::string> tokens;
	//std::cout << "mpoint:" << mpoint << std::endl;
void Device::set_id         (std::string new_id     ){ id      = new_id     ; }
#include "Device.h"
void Device::set_mpoint     (std::string new_mpoint ){ mpoint  = new_mpoint ; }
	std::string token;
    std::cout << label << "unmount successful!!=)" << std::endl;
	if(mounted == false){
	std::cout << std::endl;	
std::string Device::get_fs()     { return fs;       }
	std::string delimiter = " ";
		std::cout << label << " not mounted... =(" << std::endl;
std::string Device::get_des()    { return des;      }
		mounted = true;
std::string Device::get_mpoint() { return mpoint;   }
#include <sys/mount.h>
						<< " mpoint: " << mpoint << std::endl;
void Device::set_label      (std::string new_label  ){ label   = new_label  ; }
void Device::set_as_mounted ()                       { mounted   = true  ; }
		return false;
		return false;

























void Device::set_devpath    (std::string new_devpath){ devpath = new_devpath; }
	size_t pos = 0;
