#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream file;
	file.open("Vehicle.txt");
	if(file.is_open()) {
		string line;
		while(getline(file,line)) {
			if(line[0]=='/')	continue;
			cout << line << endl;
		}
	}
	else {
		cerr << "Error! Cant Open File";
		return 1;
	}
	file.close();
	return 0;
}