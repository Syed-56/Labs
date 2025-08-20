#include <iostream>
using namespace std;
class Student {
	char* rollNo;
	int sem;
	char* name;
	float gpa;
	
	public:
	void setGPA(int g) {gpa = g;}	
	void setSem(int s) {sem = s;}	
	void setName(int n) {*name = n;}	
	void setRollNum(int r) {*rollNo = r;}	
	
	float getGPA() {return gpa;}
	int getSem()   {return sem;}
	char* getName()  {return name;}
	char* getRollNum()  {return rollNo;}
	
	Student() {
		rollNo = new char[20];
		name = new char[50];
	}
	void input() {
		cout << "\nInput Student Details:-\n";
		cout << "Enter Student Roll Num: ";
		cin.getline(rollNo,20);
		cout << "Enter Student Name: ";
		cin.getline(name,50);
		cout << "Enter Semester Number of Student: ";
		cin >> sem;
		cout << "Enter CGPA of Student: ";
		cin >> gpa;
		cin.ignore();
	}
	void output() const {
		cout << "\nStudent:-\n";
		cout << "\nName: " << name;
		cout << "\nRoll Number: " << rollNo;
		cout << "\nSemester: " << sem;
		cout << "\nCGPA: " << gpa;
		cout << endl;
	}
	~Student() {
		delete[] name;
		delete[] rollNo;
	}
};

void sortByGPA(Student s[]) {
	for(int i=0; i<5; i++) {
		Student temp;
		for(int j=i+1; j<5; j++) {
			if(s[j].getGPA() > s[i].getGPA()) {
				temp.setName(s[j].getName());
				s[j].setName(s[i].getName());
				s[i].setName(temp.getName());
				temp.setRollNum(s[j].getRollNum());
				s[j].setRollNum(s[i].getRollNum());
				s[i].setRollNum(temp.getRollNum());
				temp.setGPA(s[j].getGPA());
				s[j].setGPA(s[i].getGPA());
				s[i].setGPA(temp.getGPA());
				temp.setSem(s[j].getSem());
				s[j].setSem(s[i].getSem());
				s[i].setSem(temp.getSem());
			}
		}
	}
}

int main() {
//	Student S1;
//	S1.input();
//	S1.output();
	
	Student List[5];
	for(int i=0; i<5; i++)	 List[i].input();
	for(int i=0; i<5; i++)	 List[i].output();
	
	sortByGPA(List);
	for(int i=0; i<5; i++)	 List[i].output();
return 0;
}