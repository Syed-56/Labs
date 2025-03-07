#include <iostream>
using namespace std;
class Employee {
	public:
	string name;
	float salary;
	
	Employee(string n, float s) : name(n) , salary(s) {}
	Employee() {}
	void displayDetails() const {
		cout << "Name: " << name << "\nSalary: " << salary << endl;
	}
};
class Manager : public Employee {
	public:
	float bonus;
	Manager (string n, float s, float b) : Employee(n,s) , bonus(b) {}
	void displayDetails() const {
		Employee::displayDetails();
		cout << "Bonus: " << bonus << endl;
	}
};

int main(void) {
	int x;
	Manager m("Syed Sultan",500000,7500);
	cout << "How many Employess to create for Manager " << m.name << ": ";
	cin >> x;
	Employee *e = new Employee[x];
	string n;
	float s;
	for(int i=0; i<x; i++) {
		cin.ignore();
		cout << "Input Employee " << i+1 << " Details:-\n";
		cout << "Enter Name: ";
		getline(cin,n);
		cout << "Enter Salary: ";
		cin >> s;
		e[i] = Employee(n,s);
	}
	
	cout << "Manager:-\n";
	m.displayDetails();
	cout << "Employees:-\n";
	for(int i=0; i<x; i++) {
		e[i].Employee::displayDetails();
	}
	
	delete[] e;
return 0;
}