#include <iostream>
#include <fstream>
#include <sstream>	//in this library: stringstream is used for inputting and ostringstream is used for outputting
using namespace std;

int main() {
	string text = "123 4.56 Hello";
	istringstream ss(text);	//means the class stringstream now have data from text variable
	
	int a;
	float b;
	string c;
	
	ss >> a >> b >> c;	//the int part of ss went into a. float part of ss went into b. string part of ss went into c. wrt to their datatypes
	cout << a << " " << b << " " << c << endl;
	
	return 0; 
}