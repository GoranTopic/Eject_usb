#include <sys/mount.h>
#include <bits/stdc++.h>
#include "Device.h"


Device::Device(){

} 

Device::Device(std::string str){
		
	std::string delimiter = " ";
	std::string token;
	size_t pos = 0;
	std::vector<std::string> tokens;
	

	while ((pos = str.find(delimiter)) != std::string::npos) {
    token = str.substr(0, pos);
    tokens.push_back(token);
    str.erase(0, pos + delimiter.length());
	}

		devpath = tokens[0];
		mpoint = tokens[1];
		fs = tokens[2];
		other = tokens[3];
		mounted = true;
}



bool Device::unmount(){

	//std::cout << "mpoint:" << mpoint << std::endl;
  const char* usb = mpoint.c_str();

		//can't unmount somthing that isnt mounted
		
  std::cout << "atempting to unmount labeled: " << label 
						<< " usb: " << usb << std::endl
						<< " mpoint: " << mpoint << std::endl;
	if(mounted == false){
		std::cout << label << " not mounted... =(" << std::endl;
		return false;
	}
	
  if (!umount(usb)){
		std::cout << devpath; 
    std::cout << label << "unmount successful!!=)" << std::endl;
		return true;

  }else{

    std::cout << "Can't unmount " << strerror(errno) << std::endl;  
		return false;

  }

}


//getter fuctions
std::string Device::get_id()     { return id;       }
std::string Device::get_type()   { return type;     }
std::string Device::get_des()    { return des;      }
std::string Device::get_label()  { return label;    }
std::string Device::get_devpath(){ return devpath;  }
std::string Device::get_mpoint() { return mpoint;   }
std::string Device::get_fs()     { return fs;       }
std::string Device::get_other()  { return other;    }
bool        Device::is_mounted()  { return mounted; }


//setter fuctions
void Device::set_id         (std::string new_id     ){ id      = new_id     ; }
void Device::set_type       (std::string new_type   ){ type    = new_type   ; }
void Device::set_des        (std::string new_des    ){ des     = new_des    ; }
void Device::set_label      (std::string new_label  ){ label   = new_label  ; }
void Device::set_devpath    (std::string new_devpath){ devpath = new_devpath; }
void Device::set_mpoint     (std::string new_mpoint ){ mpoint  = new_mpoint ; }
void Device::set_fs         (std::string new_fs     ){ fs      = new_fs     ; }
void Device::set_other      (std::string new_other  ){ other   = new_other  ; }
void Device::set_as_mounted ()                       { mounted   = true  ; }




void Device::print(){
	
	std::cout << std::endl;	
	std::cout <<  "id     : " << id      << std::endl; 
	std::cout <<  "type   : " << type    << std::endl; 
	std::cout <<  "des    : " << des     << std::endl; 
	std::cout <<  "label  : " << label   << std::endl; 
	std::cout <<  "devpath: " << devpath << std::endl; 
	std::cout <<  "mpoint : " << mpoint  << std::endl; 
	std::cout <<  "fs     : " << fs      << std::endl; 
	std::cout <<  "other  : " << other   << std::endl; 
	std::cout <<  "device mounted: " << mounted  << std::endl; 

}

