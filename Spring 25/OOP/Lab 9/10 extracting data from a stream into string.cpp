#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
	ostringstream oss;	//creating stream of class ostringstream
	oss << "My score is " << 95 << " out of " << 100;	//streaming data into oss
	
	string result = oss.str();	//extracting data from oss to put in 
	cout << result;	//outputting result variable
	
	return 0;
}