#include <iostream>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

std::string regex_match_get(std::string input_str, std::regex rgx){
  std::smatch match;

  const std::string str = (const std::string)input_str;

   std::cout << input_str << '\n';

  if(std::regex_search(str.begin(), str.end(), match, rgx)){
    return match[1];
  }else{
    return "none";
  }
}



int main(int argc, char* argv[]){
	
		regex regex_usb("^(\\-?([^\\-]+)){1}\\-.*$");
		regex regex_des("\\-([^\\-]+)\\-?.*$");
		regex regex_label("^.*\\-(\\w*)\\-.*");
		regex regex_devpath("^(\\s?[^\\s]+\\s){1}([^\\s]+)");
		regex regex_mpoint("^(\\s?[^\\s]+\\s){2}([^\\s]+)");
		regex regex_fs("^(\\s?[^\\s]+\\s){3}([^\\s]+)");
		string strbuff, matchbuff;
		string filename;
		ifstream file;
	
		if(argc > 0){ 
			//if passed argument, open file
			filename = (string)argv[1];	
			file = ifstream(filename);
		}
		
		if(file.is_open()){
			//open read from file
			while(getline(file, strbuff)){
				//cout << strbuff << endl;
				//if(regex_match(strbuff, starts_devpath)) cout<<"It matched!"<<endl;
		 		
				matchbuff = regex_match_get(strbuff, regex_des);
    		std::cout << "match: " << matchbuff << std::endl << std::endl;


			}
			file.close();
		}
	
	 std::string string("last\\x20part");
   string = std::regex_replace(string, std::regex("\\\\x20"), "\x20");
	
	 cout << string << endl;	

}
