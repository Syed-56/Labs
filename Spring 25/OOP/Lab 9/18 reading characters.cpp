#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream file;
	file.open("18 large_log.txt", ios::binary);
	if(!file.is_open()) {
		cerr << "Error! Cant Open File";
		return 1;	
	}
	
	char ch[10+1];
	while(file.read(ch,10)) {
		cout << "Current Position: " << file.tellg() << endl;
	}
	
	file.close();
	return 0;
}