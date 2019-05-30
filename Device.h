#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
  private:

    std::string id     = "n/a";
    std::string type   = "n/a";
    std::string des    = "n/a";
    std::string label  = "n/a";
    std::string devpath= "n/a";  // the path of the /dev/*
    std::string mpoint = "n/a";  //  mount point where dev is mounted
    std::string fs     = "n/a";  // type of the block device
    std::string other  = "n/a";  // the rest of things
		bool mounted       = false;

  public:
  		Device(); // empty contructur 
			Device(std::string str); //default contructor
			
			void print();
			bool unmount();
			
			//getter methods
			std::string get_id     ();
			std::string get_type   ();
			std::string get_des    ();
			std::string get_label  ();
			std::string get_devpath();
			std::string get_mpoint ();
			std::string get_fs     ();
			std::string get_other  ();
      bool is_mounted        ();

			//setter methods
      void set_id         (std::string new_id     );
      void set_type       (std::string new_type   );
      void set_des        (std::string new_des    );
   		void set_label      (std::string new_label  );
      void set_devpath    (std::string new_devpath);
			void set_mpoint     (std::string new_mpoint );
      void set_fs         (std::string new_fs     );
      void set_other      (std::string new_other  );
      void set_as_mounted ();

}; 
#endif
