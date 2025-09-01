#include<iostream>
using namespace std;
class Employee {
	public:
		
	string name;
	int age;
	float salary;
	
	Employee(string name, int age, float salary) {
		this->name = name;
		this->age = age;
		this->salary = salary;
	}
	
	void print() {
		cout<<"\nEmployee\nName = "<<name<<"\tAge = "<<age<<"\tSalary = "<<salary;
	}
};
class Manager : public Employee {
	public:
	string department;
	
	Manager(string name, int age, float salary, string department) : Employee(name, age, salary) {
		this->department = department;
	}
	
	void print() {
		Employee::print();
		cout<<"\t\tDepartment = "<<department;
	}
};

int main() {
	Employee e("Syed Sultan",32,150.9);
	Manager m("Syed Liaquat",40, 250.4,"Planning");
	e.print();
	m.print();
	
}