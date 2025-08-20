#include <iostream>
using namespace std;
class battery {
	public:
	int mAh;
	string company;
	float hours;
};
class smartphone {
	public:
	string name;
	battery b;
	
	smartphone(string name) : name(name) {
		cout << "Enter Battery Name: ";
		getline(cin,b.company);
		cout << "Enter mAh: ";
		cin >> b.mAh;
		cout << "Enter Battery Hours: ";
		cin >> b.hours;
	}
	void display() const {
		cout << "Phone Name: " << name;
		cout << "\nPhone Battery:-\n";
		cout << "Name: " << b.company;
		cout << "\tmAh: " << b.mAh;
		cout << "\tDuration: " << b.hours;
	}
};

int main(void) {
	smartphone p("Nokia");
	p.display();
return 0;
}