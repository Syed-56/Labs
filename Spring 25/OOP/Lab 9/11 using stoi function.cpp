#include <iostream>
#include <sstream>
#include <fstream>
using namespace std; 

int main() {
	
	ifstream file;
	file.open("8 Vehicle.txt");
	if(file.is_open()==false) {
		cerr << "Error! Cant Open File";
		return 1;
	}
	
	string line;
	string type, name, ID, year;
	
	while(getline(file,line)) {
		if(line.empty() || line[0]=='/')	continue;
		istringstream iss(line);
//		iss >> type >> ID >> name >> year;	this words but in output we are having comma which is bad
//		to resolve this issue, we are gonna use: getline(source, destination, deliminator).
		getline(iss,type,',');		//the ss is stream file which is source, the text is taken from it till it finds the deliminator (,)
		getline(iss,name,',');		//  then the data taken before the comma occurs, is stored in the type/name/etc variable
		getline(iss,ID,',');
		getline(iss,year,',');
		cout << "Type: " << type << "\t Name: " << name << "\tID: " << ID << "\tYear: " << year << endl;
	}
	file.close();
	return 0;
}