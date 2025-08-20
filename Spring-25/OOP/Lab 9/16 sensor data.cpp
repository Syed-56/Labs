#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream file;
	file.open("16 sensor_log.txt", ios::out);
	if(file.is_open()==false) {
		cerr << "Error! Cant Open File";
		return 1;
	}
	streampos pos1, pos2, pos3;
	pos1 = file.tellp();
	cout << "Current Cursor Position: " << pos1 << endl;
	file << "\nRandom Text";
	pos2 = file.tellp();
	cout << "Current Cursor Position: " << pos2 << endl;
	file << "\nRandom Text";
	pos3 = file.tellp();
	cout << "Current Cursor Position: " << pos3 << endl;
	
	file.close();
	return 0;
}