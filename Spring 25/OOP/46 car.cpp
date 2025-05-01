#include <iostream>
#include <string>
using namespace std;
static int counter=0;
class Car {
	const int id = 25+counter;
	string model;
	int speed;
	char* manufactor;
	
	public:
		Car() : id(25+(counter++)) , manufactor(nullptr) {}
	Car(string m, int s, const char* man) : id(25+(counter++)) {
		manufactor = new char[strlen(man)+1];
		model = m;
		speed = s;
		strcpy(manufactor,man);
	}
	Car(const Car& obj) : id(obj.id) {
		manufactor = new char[strlen(obj.manufactor)+1];
		model = obj.model;
		speed = obj.speed;
		strcpy(manufactor,obj.manufactor);
	}
	int getCount() {return counter;}
	void display() const {
		cout << "\nModel: " << model;
		cout << "\nID: " << id;
		cout << "\nSpeed: " << speed;
		cout << "\nManufactor: ";
		for(int i=0; i<strlen(manufactor); i++)		cout << manufactor[i];
		cout << endl;
	}
	~Car() {
		delete[] manufactor;
	}
};
int main() {
	Car** c;
	c = new Car*[2];
	
	Car c1("Corolla",150,"Honda");
	Car c2("Civic",170,"Toyota");
	c[0] = new Car(c1);
	c[1] = new Car(c2);
	cout << "Showroom\n";
	c[0]->display();
	c[1]->display();
	Car car(c1);
	cout << "\nShowing Copied Car:-";
	car.display();
	
	for(int i=0; i<2; i++)	delete c[i];
	delete[] c;
	return 0;
}