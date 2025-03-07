#include <iostream>
using namespace std;
class Car {
	private:
	string registrationNum;
	string modelName;
	string ownerName;
	
	public:
	Car(string registrationNum, string modelName, string ownerName) {
		this->registrationNum = registrationNum;
		this->modelName = modelName;
		this->ownerName = ownerName;
	}
	Car(){}
	
	Car(const Car &obj, string newName) {
		registrationNum = obj.registrationNum;
		modelName = obj.modelName;
		ownerName = newName;
		cout << "Old Owner: " << obj.ownerName;
	}
	string getregNum() {
		return registrationNum;
	}
	void display() {
		cout << "\nCar Model: " << modelName << "\nCar Owner: " << ownerName << "\nNumber Plate: " << registrationNum << endl;;
	}
	~Car(){}
};

int main(void) {
	int n;
	cout << "How Many Cars in Rental System: ";
	cin >> n;
	cin.ignore();
	string model,owner,plate;
	Car *c = new Car[n];
	for(int i=0; i<n; i++) {
		cout << "Input Car " << i+1 << " Details\n";
		cout << "Enter Car Model Name: ";
		getline(cin,model);
		cout << "Enter Car Owner Name: ";
		getline(cin,owner);
		cout << "Enter Car Number Plate: ";
		getline(cin,plate);
		c[i] = Car(plate,model,owner);
		
	}
	Car rentCar;
	int opt;
	while(true) {
		cout << "1) Rent Cars\n2)Display Cars\n3)Exit\n";
		cout << "Enter Option: ";
		cin >> opt;
		cin.ignore();
		if(opt==1) {
			cout << "Which Car You Want to Rent Sultan: ";
			getline(cin,plate);
			bool found = false;
			for(int i=0; i<n; i++) {
				if(found)	break;
				if(c[i].getregNum()==plate) {
					rentCar = Car(c[i],"Syed Sultan");
					found = true;
					c[i].display();
				}
			}
			if(!found)	cout << "Car Not Found\n";
		}
		else if(opt==2) {
			for(int i=0; i<n; i++) {
				cout << "Car" << i+1 << " Details\n";
				c[i].display();
			}
		}
		else if(opt==3) {
			cout << "Exiting";
			delete[] c;
			break;
		}
		else	cout << "Invalid Option\n";
	}
return 0;
}