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
		
		if(type=="AutonomousCar") {
			getline(iss,extraData,',');
			size_t pos = extraData.find(':');	
			if(pos != string::npos) {	
				string valStr = extraData.substr(pos+1);
				float softwareVersion = stof(valStr);	
				cout << "Software Version: " << softwareVersion << endl;
			}
		}
		else if(type=="ElectricVehicle") {
			getline(iss,extraData,',');
			size_t pos = extraData.find(':');	
			if(pos != string::npos) {
				string valStr = extraData.substr(pos+1);	
				int battery = stoi(valStr);
				cout << "Battery Capacity: " << battery << "%" << endl;
			}
		}
		else if(type=="HybridTruck") {
			getline(iss,extraData,'|');
			size_t pos = extraData.find(':');
			if(pos != string::npos) {
				string valStr = extraData.substr(pos+1);
				int cargo = stoi(valStr);
				cout << "Cargo Capacity: " << cargo << "Kg"; 
			}
			getline(iss,extraData,',');
			size_t pos2 = extraData.find(':');
			if(pos2 != string::npos) {
				string valStr2 = extraData.substr(pos2+1);
				int battery = stoi(valStr2);
				cout << "\t\tBattery Capacity: " << battery << "%" << endl; 
			}
		}
	}
	file.close();
	return 0;
}