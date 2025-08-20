#include <iostream>
using namespace std;
class Car {
	public:
	int registrationNum;
	string ownerName;
	string modelName;
	
	Car(){}
	Car(int regNum, string oName, string mName) : registrationNum(regNum),ownerName(oName),modelName(mName) {}
	Car(const Car &obj, string newOwner) {
		cout << "Old Owner: " << obj.ownerName << endl;
		registrationNum = obj.registrationNum;
		ownerName = newOwner;
		modelName = obj.modelName;
	}
	void display() const {
		cout << "\nCar Model: " << modelName << "\nCar Owner: " << ownerName << "\nNumber Plate: " << registrationNum << endl;
	}
	
};

int main(void) {
	Car c1(1234,"Ismail","Alto");
	Car c2(4321,"Ali","Mehran");
	Car c3(1000,"Khizer","Civic");
	if(c1.registrationNum == c2.registrationNum) {
		cout << "Enter Unique Registration Number of Car 1";
		cin >> c1.registrationNum;
	}
	else if(c3.registrationNum == c2.registrationNum) {
		cout << "Enter Unique Registration Number of Car 1";
		cin >> c2.registrationNum;
	}
	else if(c1.registrationNum == c3.registrationNum) {
		cout << "Enter Unique Registration Number of Car 1";
		cin >> c3.registrationNum;
	}
	
	c1.display();
	c2.display();
	c3.display();
	int opt;
	string renter = "Syed Sultan";
	cout << "\nWhich Car You Want to Rent Sultan\n1) Alto\t\t2)Mehran\t3)Civic\nEnter Option Number: ";
	cin >> opt;
	if(opt==1) {
		Car c1Rent(c1,renter);
		c1Rent.display();
	}
	else if(opt==2)	{
		Car c2Rent(c2,renter);
		c2Rent.display();
	}
	else if(opt==3) {
		Car c3Rent(c3,renter);
		c3Rent.display();
	}
	else	cout << "Car Not Found";
return 0;
}