#include <iostream>
using namespace std;
class Device {
	public:
	int deviceID;
	bool status;
	
	void displayDetails() const {
		cout << "\nDevice ID: " << deviceID << "\nStatus: " << (status ? "On\n" : "Off\n");
	}
};
class SmartPhone : virtual public Device {
	public:
	float screenSize;
	void displayDetails() const {
		cout << "Screen Size: " << screenSize << endl;
	}
};
class SmartWatch : virtual public Device {
	public:
	bool heartRateMonitor;
	void displayDetails() const {
		cout << "Heart Rate Monitor: " << (heartRateMonitor ? "Active\n" : "Inactive\n");
	}
};
class SmartWearable : public SmartPhone, public SmartWatch {
	public:
	int stepCounter=0;
	void displayDetails() const {
		Device::displayDetails();
		SmartPhone::displayDetails();
		SmartWatch::displayDetails();
		cout << "Steps: " << stepCounter;
	}
};

int main() {
	SmartWearable s;
	cout << "Enter Device ID: ";
	cin >> s.deviceID;
	cout << "Enter Device Status: ";
	cin >> s.status;
	cout << "Enter Device Screen Size: ";
	cin >> s.screenSize;
	cout << "Enter Heart Rate Monitor Status: ";
	cin >> s.heartRateMonitor;
	cout << "Enter Device Steps: ";
	cin >> s.stepCounter;
	
	s.displayDetails();
return 0;
}