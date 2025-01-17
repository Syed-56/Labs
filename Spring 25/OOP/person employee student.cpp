#include<iostream>
using namespace std;

class Person {
    string name;
    int age;
    
public:
    void setName(string name) {
        this->name = name;
    }
    void setAge(int age) {
        this->age = age;
    }
    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    
    virtual void displayInfo() {
        cout << "Person : Name = " << getName() << "\tAge = " << getAge();
    }
};

class Employee : public Person {
    int empID;
    
public:
    void setEmpID(int empID) {
        this->empID = empID;
    }
    int getEmpID() {
        return empID;
    }
    
    void inputDetails() {
        string name;
        int age, id;
        cout << "Enter Employee Name: ";
        getline(cin, name);
        cout << "Enter Employee Age: ";
        cin >> age;
        cout << "Enter Employee ID: ";
        cin >> id;
        
        setName(name);
        setAge(age);
        setEmpID(id);
        
        cin.ignore(); // Clear the newline left by cin >>
    }
    
    void displayInfo() {
        cout << "Person : Name = " << getName() << "\tAge = " << getAge() << "\tEmployee ID = " << getEmpID() << endl;
    }
};

class Student : public Person {
    int studID;
    
public:
    void setStudID(int studID) {
        this->studID = studID;
    }
    int getStudID() {
        return studID;
    }
    
    void inputDetails() {
        string name;
        int age, id;
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Student Age: ";
        cin >> age;
        cout << "Enter Student ID: ";
        cin >> id;
        
        setName(name);
        setAge(age);
        setStudID(id);
        
        cin.ignore(); // Clear the newline left by cin >>
    }
    
    void displayInfo() {
        cout << "Person : Name = " << getName() << "\tAge = " << getAge() << "\tStudent ID = " << getStudID() << endl;
    }
};

int main() {
    Employee e;
    Student s;
    
    e.inputDetails();
    s.inputDetails();
    
    cout << "\nDetails:-\n";
    s.displayInfo();
    e.displayInfo();
}
