#include <iostream>
#include <cstring>


using namespace std;



int main(int argc, char** argv){


	int len = strlen(argv[1]);
	
	for(int i = 0; i < len+4; i++) cout << "*";
	cout << endl;
	printf("* %s *\n", argv[1]);	
	for(int i = 0; i < len+4; i++) cout << "*";
	cout << endl;
	
	

	//cout << "num: " << num <<  endl;

	//for(int i = 0; i < num; i++){
	//	for(int e = 0; e < i; e++) cout << "*";
	//	cout << endl;
	//}

	//for(int i = num; i > 0; i--){
	//	for(int e = 0; e < i; e++) cout << "*";
	//	cout << endl;
	//}





}


