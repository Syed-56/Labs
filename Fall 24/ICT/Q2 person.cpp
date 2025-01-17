#include <iostream>
#include <string>
using namespace std;
class Person {
	private:
	    string name;
	    int age;
	public:
	    Person(string n = "", int a = 0) : name(n), age(a) {}
	    string getName() const {
	        return name;
	    }
	    void setName(string n) {
	        name = n;
	    }
	    int getAge() const {
	        return age;
	    }
	    void setAge(int a) {
	        if (a >= 0)
	            age = a;
	        else
	            cout << "Invalid age" << endl;
	    }
	    void displayInfo() const {
	        cout << "Person Name : " << name << endl;
	        cout << "Person Age : " << age << endl;
	    }
};
class Employee : public Person {
	private:
	    int employeeID;
	public:
	    Employee(string n = "", int a = 0, int id = 0) : Person(n, a), employeeID(id) {}
	    void setEmployeeID(int id) {
	        employeeID = id;
	    }
	    int getEmployeeID() const {
	        return employeeID;
	    }
	    void displayID() const {
	        cout << "Employee ID : " << employeeID << endl;
	    }
};
class Student : public Person {
	private:
	    int studentID;
	
	public:
	    Student(string n = "", int a = 0, int id = 0) : Person(n, a), studentID(id) {}
	    void setStudentID(int id) {
	        studentID = id;
	    }
	    int getStudentID() const {
	        return studentID;
	    }
	    void displayID() const {
	        cout << "Student ID : " << studentID << endl;
    	}
};

int main() {
    Person p1;
    p1.setName("Syed");
    p1.setAge(17);
    p1.displayInfo();
    cout << "\n";
    Employee e1;
    e1.setName("Sultan");
    e1.setAge(18);
    e1.setEmployeeID(101);
    e1.displayInfo();
    e1.displayID();
    cout << "\n";
    Student s1;
    s1.setName("Ahmed");
    s1.setAge(19);
    s1.setStudentID(202);
    s1.displayInfo();
    s1.displayID();
    return 0;
}
