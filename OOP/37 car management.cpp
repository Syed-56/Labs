#include <iostream>
using namespace std;
class Vehicle {
	public:
	string brand;
	int speed;
	
	void displayDetails() const {
		cout << "Brand: " << brand << "\nSpeed: " << speed << endl;
	}
};
class Car : public Vehicle {
	public:
	int seats;
	void displayDetails() const {
		Vehicle::displayDetails();
		cout << "Seats: " << seats << endl;
	}
};
class electricCar : public Car {
	public:
	int batteryLife;
	void displayDetails() const {
		Car::displayDetails();
		cout << "Battery Life: " << batteryLife << "%\n";
	}
};

int main() {
	electricCar ec;
	cout << "Enter Car Name: ";
	getline(cin,ec.brand);
	cout << "Enter Speed: ";
	cin >> ec.speed;
	cout << "Enter No. of Seats: ";
	cin >> ec.seats;
	cout << "Enter Battery Life: ";
	cin >> ec.batteryLife;
	
	ec.electricCar::displayDetails();
return 0;
}