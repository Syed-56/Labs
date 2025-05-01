#include <iostream>
using namespace std;

class Student;
class Teacher;

class Student {
	string name;
	float grades[3];
	friend class Teacher;
	
	public:
	Student(string n, float g1, float g2, float g3) {
		name = n;
		grades[0] = g1;
		grades[1] = g2;
		grades[2] = g3;
	}
	friend float avgGrade(Student &s);
};

class Teacher {
	string name;
	
	public:
	Teacher(string n) : name(n) {}
	friend float avgGrade(Student &s);

	void modifyGrades(Student &s) {
		int i,g;
		cout << "Which Subject Grade to Modify: ";
		cin >> i;
		if(i>3) {
			cout << "Out of Bound\n";
			return;
		}
		cout << "Enter New Grade: ";
		cin >> g;
		s.grades[i-1] = g;
	}
	void accessGrades(Student &s) {
		for(int i=0; i<3; i++) {
			cout << "Subject " << i+1 << ": " << s.grades[i] << endl;
		}
	}
};

float avgGrade(Student &s) {
	int sum=0;
	for(int i=0; i<3; i++) {
		sum += s.grades[i];
	}
	return sum/3;
}

int main() {
	Student s1("Syed Sultan", 90,80,50);
	Teacher t1("Sir Talha");
	cout << "\nGrades:-\n";
	t1.accessGrades(s1);
	cout << "Average Grade: " << avgGrade(s1) << endl;
	t1.modifyGrades(s1);
	cout << "\nUpdated Grades:-\n";
	t1.accessGrades(s1);
	cout << "Average Grade: " << avgGrade(s1);
}

