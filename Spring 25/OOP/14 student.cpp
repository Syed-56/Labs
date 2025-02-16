#include<iostream>
using namespace std;
typedef struct {
	string name;
	int rollNum;
	float marks;
} student;

int main() {
	int n;
	cout << "How Many Students You Want To Create: ";
	cin >> n;
	student* s = new student[n];
	for(int i=0; i<n; i++) {
		cin.ignore();
		cout << "Student " << (i+1) << " Details:-\n";
		cout << "Enter Name: ";
		getline(cin,s[i].name);
		cout << "Enter Roll#: ";
		cin >> s[i].rollNum;
		cout << "Enter Marks: ";
		cin >> s[i].marks;
	}
	int id;
	int max=s[0].marks;
	for(int i=0; i<n; i++) {
		if(s[i].marks >= max) {
			max = s[i].marks;
			id=i;
		}
	}
	cout << "Topper Student\nName: " << s[id].name << "\nRoll#: " << s[id].rollNum << "\nMarks: " << s[id].marks;
}