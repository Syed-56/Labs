#include <iostream>
using namespace std;
class Person {
	public:
	string name;
	int age;
	
	void displayDetails() const {
		cout << "\nName: " << name << "\nAge: " << age << " years\n";
	}
};
class Teacher : public Person {
	public:
	string subject;
	void displayDetails() const {
		Person::displayDetails();
		cout << "Subject: " << subject << endl;
	}
};
class Researcher : public Teacher {
	public:
	string researchArea;
	void displayDetails() const {
		Teacher::displayDetails();
		cout << "Research Area: " << researchArea << endl;
	}
};
class Professor : public Researcher {
	public:
	int publications;
	void displayDetails() const {
		Researcher::displayDetails();
		cout << "Publications: " << publications << endl;
	}
};

int main() {
	Professor p;
	cout << "Enter Professor Name: ";
	getline(cin,p.name);
	cout << "Enter Professor Age: ";
	cin >> p.age;
	cin.ignore();
	cout << "Enter Professor Subject: ";
	getline(cin,p.subject);
	cout << "Enter Professor Research Area: ";
	getline(cin,p.researchArea);
	cout << "Enter Professor Publications: ";
	cin >> p.publications;
	
	p.displayDetails();
}