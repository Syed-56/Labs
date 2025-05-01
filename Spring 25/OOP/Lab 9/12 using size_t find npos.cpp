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
	string type, name, ID, year, extraData;
	
	while(getline(file,line)) {
		if(line.empty() || line[0]=='/')	continue;
		istringstream iss(line);
		getline(iss,type,',');	
		getline(iss,ID,',');	
		getline(iss,name,',');
		getline(iss,year,',');
		cout << "Type: " << type << "\t ID: " << ID << "\tName: " << name << "\tYear: " << year << endl;
		
		getline(iss,extraData,',');
		//checking type and extracting data
		if(type=="AutonomousCar") {
			size_t pos = extraData.find(':');	//size_t is used to store index/position/count. It can be done with int but if the position is not found then the find function returns string::npos thats why we use size_t
			if(pos != string::npos) {	//executing condition when position found
				string valStr = extraData.substr(pos+1);	//extract data from the position after colon
				float softwareVersion = stof(valStr);	//convert the data from string to float
				cout << "Software Version: " << softwareVersion << "\n\n";
			}
		}
		else if(type=="ElectricVehicle") {
			size_t pos = extraData.find(':');	//find position
			if(pos != string::npos) {
				string valStr = extraData.substr(pos+1);	//extract data after colon
				int battery = stoi(valStr);
				cout << "Battery Capacity: " << battery << "\n\n";
			}
		}
	}
	
	return 0;
}