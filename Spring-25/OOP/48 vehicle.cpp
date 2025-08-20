#include <iostream>
using namespace std;
class Vehicle {
	protected:
	string model;
	string name;
	
	public:
	Vehicle(string m, string n) : model(m) , name(n) {}
	void display() const {
		cout << "\nMaker: " << name << "\nModel: " << model;
	}
};
class Rentable : public Vehicle {
	protected:
	int hours;
	float fees;
	
	public:
	Rentable(string m, string n, int h, float f) : Vehicle(m,n) , hours(h) , fees(f) {}
	void display() const {
		Vehicle::display();
		cout << "\nHours: " << hours << "\nFees: " << fees;
	}
};
class Operational : public Vehicle {
	protected:
	string service;
	
	public:
	Operational(string m, string n, string s) : Vehicle(m,n) , service(s) {}
	void display() const {
		Vehicle::display();
		cout << "\nService: " << service;
	}
};
class Car : public Rentable {
	public:
	string renter;
	Car(string m, string n, int h, float f, string r) :  Rentable(m,n,h,f) , renter(r) {}
	void display() const {
		Rentable::display();
		cout << "\nRenter: " << renter << endl;
	}
};
class GarbageTruck : public Operational {
	public:
	int dutyHours;
	GarbageTruck(string m, string n, string s, int dh) : Operational(m,n,s) , dutyHours(dh) {}
	void display() const {
		Operational::display();
		cout << "\nDuty Hours: " << dutyHours << endl;
	}
};

int main() {
	Car c("Civic","Honda",8,4000,"Sultan");
	GarbageTruck gt("Bionic 400","Hino","Trash Pickup",12);
	cout << "Vehicle 1:-\n";
	c.Car::display();
	cout << "\nVehicle 2:-\n";
	gt.GarbageTruck::display();
return 0;
}