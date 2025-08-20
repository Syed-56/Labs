#include <iostream>
#include <string>
using namespace std;

class Course;
class Professor;
class Student;
class University;

class Person {
protected:
    string name;
    int id;

public:
    void setName(string n) { name = n; }
    void setID(int id) { this->id = id; }
    string getName() const { return name; }
    int getID() const { return id; }

    Person() : name(""), id(0) {}
    Person(string n, int id) : name(n), id(id) {}
    Person(const Person& obj) : name(obj.name), id(obj.id) {}

    virtual void display() const {
        cout << "\nName: " << name;
        cout << "\nID: " << id;
        cout << endl;
    }
};

class University {
private:
    string name;
    int fees;
    int departments;
    Professor** faculty;
    Student** students;
    Course** courses;
    int profCapacity, studentCapacity, courseCapacity;
    int profCount, studentCount, courseCount;

public:
    void setName(string n) { name = n; }
    void setFees(int f) { fees = f; }
    void setDepts(int d) { departments = d; }
    void addFaculty(const Professor& p);
    void addStudent(const Student& s);
    void addCourse(const Course& c);

    string getName() const { return name; }
    int getFees() const { return fees; }
    int getDepts() const { return departments; }

    University();
    University(string n, int f, int d);
    University(const University& obj);
    ~University();

    void display() const;
};

class Course {
private:
    string name;
    string code;
    int credits;
    Professor** profs;
    int profCapacity, profCount;

public:
    void setName(string n) { name = n; }
    void setCode(string c) { code = c; }
    void setCredits(int ch) { credits = ch; }
    void addProfessor(const Professor& p);

    string getName() const { return name; }
    string getCode() const { return code; }
    int getCredits() const { return credits; }

    Course();
    Course(string n, string c, int ch);
    Course(const Course& obj);
    ~Course();

    void display() const;
};

class Professor : public Person {
private:
    Course** subjects;
    int salary;
    int subjectCapacity, subjectCount;

public:
    void setSalary(int s) { salary = s; }
    void addCourse(const Course& c);
    int getSalary() const { return salary; }

    Professor();
    Professor(string n, int id, int s);
    Professor(const Professor& obj);
    ~Professor();

    void display() const;
};

class Student : public Person {
private:
    Course** courses;
    float cgpa;
    int courseCapacity, courseCount;

public:
    void addCourse(const Course& c);
    void setCGPA(float gpa) { cgpa = gpa; }
    float getCGPA() const { return cgpa; }

    Student();
    Student(string n, int id, float gpa);
    Student(const Student& obj);
    ~Student();

    void display() const;
};

University::University() : profCapacity(5), studentCapacity(50), courseCapacity(15) {
    profCount = studentCount = courseCount = 0;
    faculty = new Professor*[profCapacity];
    students = new Student*[studentCapacity];
    courses = new Course*[courseCapacity];
    for (int i = 0; i < profCapacity; i++) faculty[i] = nullptr;
    for (int i = 0; i < studentCapacity; i++) students[i] = nullptr;
    for (int i = 0; i < courseCapacity; i++) courses[i] = nullptr;
}

University::University(string n, int f, int d) : name(n), fees(f), departments(d), profCapacity(5), studentCapacity(50), courseCapacity(15) {
    profCount = studentCount = courseCount = 0;
    faculty = new Professor*[profCapacity];
    students = new Student*[studentCapacity];
    courses = new Course*[courseCapacity];
    for (int i = 0; i < profCapacity; i++) faculty[i] = nullptr;
    for (int i = 0; i < studentCapacity; i++) students[i] = nullptr;
    for (int i = 0; i < courseCapacity; i++) courses[i] = nullptr;
}

University::University(const University& obj) : name(obj.name), fees(obj.fees), departments(obj.departments),
                                               profCapacity(obj.profCapacity), studentCapacity(obj.studentCapacity), courseCapacity(obj.courseCapacity),
                                               profCount(obj.profCount), studentCount(obj.studentCount), courseCount(obj.courseCount) {
    faculty = new Professor*[profCapacity];
    students = new Student*[studentCapacity];
    courses = new Course*[courseCapacity];
    for (int i = 0; i < profCount; i++) faculty[i] = new Professor(*obj.faculty[i]);
    for (int i = 0; i < studentCount; i++) students[i] = new Student(*obj.students[i]);
    for (int i = 0; i < courseCount; i++) courses[i] = new Course(*obj.courses[i]);
}

University::~University() {
    for (int i = 0; i < profCount; i++) delete faculty[i];
    for (int i = 0; i < studentCount; i++) delete students[i];
    for (int i = 0; i < courseCount; i++) delete courses[i];
    delete[] faculty;
    delete[] students;
    delete[] courses;
}

void University::addFaculty(const Professor& p) {
    if (profCount >= profCapacity) {
        cout << "Faculty capacity exceeded!\n";
        return;
    }
    faculty[profCount++] = new Professor(p);
}

void University::addStudent(const Student& s) {
    if (studentCount >= studentCapacity) {
        cout << "Student capacity exceeded!\n";
        return;
    }
    students[studentCount++] = new Student(s);
}

void University::addCourse(const Course& c) {
    if (courseCount >= courseCapacity) {
        cout << "Course capacity exceeded!\n";
        return;
    }
    courses[courseCount++] = new Course(c);
}

void University::display() const {
    cout << "\nUniversity Name: " << name;
    cout << "\nFees: " << fees;
    cout << "\nDepartments: " << departments;
    cout << "\nCourses: ";
    for (int i = 0; i < courseCount; i++) cout << courses[i]->getName() << "  ";
    cout << "\nProfessors: ";
    for (int i = 0; i < profCount; i++) cout << faculty[i]->getName() << "  ";
    cout << "\nStudents: ";
    for (int i = 0; i < studentCount; i++) cout << students[i]->getName() << "  ";
    cout << endl;
}

// Course Implementation
Course::Course() : profCapacity(3), profCount(0) {
    profs = new Professor*[profCapacity];
    for (int i = 0; i < profCapacity; i++) profs[i] = nullptr;
}

Course::Course(string n, string c, int ch) : name(n), code(c), credits(ch), profCapacity(3), profCount(0) {
    profs = new Professor*[profCapacity];
    for (int i = 0; i < profCapacity; i++) profs[i] = nullptr;
}

Course::Course(const Course& obj) : name(obj.name), code(obj.code), credits(obj.credits), profCapacity(obj.profCapacity), profCount(obj.profCount) {
    profs = new Professor*[profCapacity];
    for (int i = 0; i < profCount; i++) profs[i] = new Professor(*obj.profs[i]);
}

Course::~Course() {
    for (int i = 0; i < profCount; i++) delete profs[i];
    delete[] profs;
}

void Course::addProfessor(const Professor& p) {
    if (profCount >= profCapacity) {
        cout << "Professor capacity exceeded!\n";
        return;
    }
    profs[profCount++] = new Professor(p);
}

void Course::display() const {
    cout << "\nCourse Name: " << name;
    cout << "\nCourse Code: " << code;
    cout << "\nCredit Hours: " << credits;
    cout << "\nTeachers: ";
    for (int i = 0; i < profCount; i++) cout << profs[i]->getName() << "  ";
    cout << endl;
}

Professor::Professor() : subjectCapacity(3), subjectCount(0) {
    subjects = new Course*[subjectCapacity];
    for (int i = 0; i < subjectCapacity; i++) subjects[i] = nullptr;
}

Professor::Professor(string n, int id, int s) : Person(n, id), salary(s), subjectCapacity(3), subjectCount(0) {
    subjects = new Course*[subjectCapacity];
    for (int i = 0; i < subjectCapacity; i++) subjects[i] = nullptr;
}

Professor::Professor(const Professor& obj) : Person(obj), salary(obj.salary), subjectCapacity(obj.subjectCapacity), subjectCount(obj.subjectCount) {
    subjects = new Course*[subjectCapacity];
    for (int i = 0; i < subjectCount; i++) subjects[i] = new Course(*obj.subjects[i]);
}

Professor::~Professor() {
    for (int i=0; i<subjectCount; i++) delete subjects[i];
    delete[] subjects;
}

void Professor::addCourse(const Course& c) {
    if (subjectCount >= subjectCapacity) {
        cout << "Course capacity exceeded!\n";
        return;
    }
    subjects[subjectCount++] = new Course(c);
}

void Professor::display() const {
    Person::display();
    cout << "Salary: " << salary;
    cout << "\nCourses Teaching: ";
    for (int i=0; i<subjectCount; i++) cout << subjects[i]->getName() << " (" << subjects[i]->getCode() << ")  ";
    cout << endl;
}

Student::Student() : courseCapacity(3), courseCount(0), cgpa(0.0) {
    courses = new Course*[courseCapacity];
    for (int i=0; i<courseCapacity; i++) courses[i] = nullptr;
}

Student::Student(string n, int id, float gpa) : Person(n, id), cgpa(gpa), courseCapacity(3), courseCount(0) {
    courses = new Course*[courseCapacity];
    for (int i=0; i<courseCapacity; i++) courses[i] = nullptr;
}

Student::Student(const Student& obj) : Person(obj), cgpa(obj.cgpa), courseCapacity(obj.courseCapacity), courseCount(obj.courseCount) {
    courses = new Course*[courseCapacity];
    for (int i=0; i<courseCount; i++) courses[i] = new Course(*obj.courses[i]);
}

Student::~Student() {
    for (int i=0; i<courseCount; i++) delete courses[i];
    delete[] courses;
}

void Student::addCourse(const Course& c) {
    if (courseCount >= courseCapacity) {
        cout << "Course capacity exceeded!\n";
        return;
    }
    courses[courseCount++] = new Course(c);
}

void Student::display() const {
    Person::display();
    cout << "Courses Studying: ";
    for (int i=0; i<courseCount; i++) cout << courses[i]->getName() << " (" << courses[i]->getCode() << ")  ";
    cout << "\nCGPA: " << cgpa << endl;
}

int main() {
    University uni("FAST-NUCES",150000,3);
	
	Professor p1("Talha Shahid",10001,80000);
	Professor p2("Uzma Saleh",10002,11000);
	Professor p3("Shahid Ashraf",10003,100000);
	Professor p4("Fahad Hussain",10004,90000);
	Professor p5("Muhammad Rahim",10005,50000);
	
	Course c1("Programming Fundamentals","PF-1002",4);
	Course c2("Object Oriented Programming","OOP-1004",4);
	Course c3("Data Structures","DS-1006",4);
	Course c4("Applied Physics", "AP-2002",3);
	Course c5("Digital Logic Design", "DLD-2004",4);
	Course c6("Computer Architecture and Assembly Language", "COAL-2005",4);
	Course c7("Calculas - I", "CAL-3001",3);
	Course c8("Multivariable Calculas", "CALII-3002",3);
	Course c9("Linear Algebra","LA-3004",3);
	Course c10("Functional English", "FE-1101",3);
	Course c11("Exposity Writing", "EW-1102",3);
	Course c12("Pakistan Studies", "ICP-1103",2);
	Course c13("Islamiat", "IRS-1104",2);
	Course c14("Civics and Community", "CCE-1105",2);
	Course c15("Final Year Project", "FYP-9999",3);
	
	Student s1("Syed Sultan",585,2.9);
	Student s2("Ali Kashif",693,3.6);
	Student s3("Ismail Silat",559,3.8);
	Student s4("Ali Hussain",570,3.4);
	Student s5("Ammar Mufti",586,3.1);
	Student s6("Hammad",581,3.4);
	Student s7("Hamza Atif",220,2.5);
	Student s8("Huzaifa Shahid",820,3.7);
	Student s9("Shayan Siddique Bin Mehar",424,2.8);
	Student s10("Abdul Majid",525,2.3);
	Student s11("Wassaf Rasool",323,2.1);
	Student s12("Abdullah Jabbar",691,2.7);
	Student s13("Asad Khan",244,2.8);
	Student s14("Rayyan Ahmer",690,2.7);
	Student s15("Hatim Mustafa",673,3.7);

    c1.addProfessor(p1);
    c2.addProfessor(p2);

    s1.addCourse(c1);
    s1.addCourse(c2);

    uni.addFaculty(p1);
    uni.addFaculty(p2);
    uni.addCourse(c1);
    uni.addCourse(c2);
    uni.addStudent(s1);

    uni.display();
    s1.display();

return 0;
}