#include <iostream>
using namespace std;
class Person {
	protected:
	string name;
	int id;
	long long phone;
	string email;
	string address;
	
	public:
	Person(string n, int ID, long long p, string em, string add) {
		name = n;
		id = ID;
		phone = p;
		email = em;
		address = add;
	}
	
	virtual void displayInfo() const {
		cout << "Name: " << name << "\nID: " << id << "\nPhone Number: +" << phone << "\nEmail ID: " << email << "\nAddress: " << address << endl;
	}
	void updateDetails() {
		cout << "\n1)\t2)ID\t3)Phone\t4)Email\t5)Address\n";
		int opt;
		cout << "Which detail you want to update: ";
		cin >> opt;
		if(opt==1) {
			cin.ignore();
			cout << "Enter New Name: ";
			getline(cin,name);
		}
		else if(opt==2) {
			cout << "Enter New ID: ";
			cin >> id;
		}
		else if(opt==3) {
			cout << "Enter New Phone Number: ";
			cin >> phone;
		}
		else if(opt==4) {
			cin.ignore();
			cout << "Enter New Email ID: ";
			getline(cin,email);
		}
		else if(opt==5) {
			cin.ignore();
			cout << "Enter New Address: ";
			getline(cin,address);
		}
		else	cout << "Invalid Option\n";
	}
};
class Course;
class Student : public Person {
	float GPA;
	int enrollmentYear;
	
	public:
	Course* coursesEnrolled[5];
	int courseCount=0;
	Student(string n, int ID, long long p, string em, string add, float g, int year) : Person(n,ID,p,em,add) {
		GPA = g;
		enrollmentYear = year;
		for(int i=0; i<5; i++)	coursesEnrolled[i] = nullptr;
	}
	
	void displayInfo() const {
		Person::displayInfo();
		cout << "GPA: " << GPA << "\nEnrollment Year: " << enrollmentYear << endl;
	}
};
class Professor : public Person {
	string department;
	Course* coursesTaught[3];
	int salary;
	
	public:
	int courseCount=0;
	Professor(string n, int ID, long long p, string em, string add, string dept, int s) : Person(n,ID,p,em,add) {
		department = dept;
		salary = s;
		for(int i=0; i<3; i++)	coursesTaught[i] = nullptr;
	}
	void setCourses(Course c);
	void displayInfo() const {
		Person::displayInfo();
		cout << "Department: " << department << "\nSalary: " << salary << endl;
	}
};
class Staff : public Person {
	string department;
	string position;
	int salary;
	
	public:
	Staff(string n, int ID, long long p, string em, string add, string dept, string pos, int sal) : Person(n,ID,p,em,add) {
		department = dept;
		position = pos;
		salary = sal;
	}
	
	void displayInfo() const {
		Person::displayInfo();
		cout << "Department: " << department << "\nPosition: " << position << "\nSalary: " << salary << endl;
	}
};

class Course {
	int courseID;
	string courseName;
	int credits;
	Professor* instructor;
	string schedule;
	
	public:
	Course(int id, string name, int cr, string sch ,Professor &p) {
		courseID = id;
		courseName = name;
		credits = cr;
		schedule = sch;
		instructor = &p;
	}
	
	void registerStudent(Student &s) {
		s.coursesEnrolled[s.courseCount] = this;
		s.courseCount++;
	}
};  

void Professor::setCourses(Course c) {
		coursesTaught[courseCount] = &c;
	}

int main() {
	
	Student s1("Syed Sultan", 5850, 923196458754, "k240585@nu.edu.pk", "R-145 Karachi", 2.9, 2024);
	Student s2("Ali Kashif", 9600, 923002483648, "k240690@nu.edu.pk", "Pakistan Warehouse - Lyari", 3.6, 2024);
	Student s3("Ali Hussain", 5780, 923002715007, "k240578@nu.edu.pk", "Capital Society", 3.4, 2024);
	
	Professor p1("Talha Shahid", 10000, 92111222980, "talha.shahid@nu.edu.pk", "CS building", "Computing", 250000);
	Professor p2("Fahad Hussain", 50000, 92090078601, "talha.shahid@nu.edu.pk", "CS building", "Computing", 250000);
	Professor p3("Shahid Ashraf", 20000, 9290909090, "shahid.ashraf@nu.edu.pk", "EE building", "Science", 200000);
	Professor p4("Huma Hafeez", 30000, 9213169055565, "huma.hafeez@nu.edu.pk", "Humanities building", "Humanities", 150000);
	
	Staff st1("Mirza Sahab",9999,92646363636, "mirza.accounts@nu.edu.pk", "One Stop", "Accounts", "Cashier", 100000);
	Staff st2("Arsalan Peon", 4444, 9245534563, "arsalan.peon@nu.edu.pk", "Staff rooms", "Servant", "Tea Boy", 20000);
	
	Course c1(1002, "PF", 4, "Mon-Thurs - 9:00 AM", p1);
	Course c2(1003, "OOP", 4, "Tue-Fri - 10:00 AM", p2);
	Course c3(2002, "CALC-I", 3, "Mon-Wed - 11:00 AM", p3);
	Course c4(3002, "English", 2, "Tue/Thurs - 12:00 PM", p4);
	c1.registerStudent(s1);
	c2.registerStudent(s2);
	c3.registerStudent(s3);
	
	s1.displayInfo();
	s2.displayInfo();
	cout << endl;
	p1.displayInfo();
	p2.displayInfo();
	cout << endl;
	st1.displayInfo();
	st2.displayInfo();
return 0;
}