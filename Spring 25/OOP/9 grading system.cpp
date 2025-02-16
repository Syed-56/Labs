#include<iostream>
using namespace std;
typedef struct {
	string name;
	int rollNum;
	float marks[5];
} student;
int main() {
	int n;
	cout << "Enter Number of Students : ";
	cin >> n;
	student s[n];
	for(int i=0; i<n; i++) {
		cin.ignore();
		cout << "Enter Student "<<(i+1)<<" Name : ";
		getline(cin,s[i].name);
		cout << "Enter Student "<<(i+1)<<" Roll# : ";
		cin >> s[i].rollNum;
		cout << "Enter Student "<<(i+1)<<" Marks:-\n";
		for(int j=0; j<5; j++) {
			cout << "Subject "<<(j+1)<<" : ";
			cin >> s[i].marks[j];
		}
	}
	int* avgMarks = new int[n];
	for(int i=0; i<n; i++) {
		int sum=0;
		for(int j=0; j<5; j++) {
			sum += s[i].marks[j];
		}
		avgMarks[i] = sum/5;
	}
	char* grade = new char[n];
	for(int i=0; i<n; i++) {
			 if(avgMarks[i] >= 86)	grade[i] = 'A';
		else if(avgMarks[i] >= 74)	grade[i] = 'B';
		else if(avgMarks[i] >= 62)	grade[i] = 'C';
		else if(avgMarks[i] >= 50)	grade[i] = 'D';
		else if(avgMarks[i] >= 40)	grade[i] = 'E';
		else	grade[i] = 'F';
	}
	for(int i=0; i<n; i++) {
		cout << "\nStudent "<<(i+1)<<endl;
		cout << "Name : "<<s[i].name<<endl;
		cout << "Roll# : "<<s[i].rollNum<<endl;
		cout << "Average Marks : "<<avgMarks[i]<<endl;
		cout << "Grade : "<<grade[i]<<endl;
	}
	delete[] avgMarks, grade;
}