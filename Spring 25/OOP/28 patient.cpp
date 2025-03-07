#include <iostream>
using namespace std;
class Patient {
	int id;
	string name;
	string *testResult;
	
	public:
		int testResultNum;
	Patient(int id, string name, string *testResult) {
		this->name = name;
		this->id = id;
		this->testResult = testResult;
	}
	Patient(const Patient &p) {
		id = p.id;
		name = p.name;
		testResult = p.testResult;
		testResultNum = p.testResultNum;
	}
	Patient() {}
	void input() {
		cout << "Enter Patient Name: ";
		getline(cin,name);
		cout << "Enter Patient ID: ";
		cin >> id;
		cout << "Enter Test Numbers: ";
		cin >> testResultNum;
		cin.ignore();
		testResult = new string[testResultNum];
		for(int i=0; i<testResultNum; i++) {
			cout << "Enter Test " << i+1 << " Result: ";
			getline(cin,testResult[i]);
		}
	}
	void display() const {
		cout << "Patient Name: " << name << "\nPatient ID: " << id << "\nTest Results:  ";
		for(int i=0; i<testResultNum; i++)	 cout << testResult[i] << "  ";
		cout << endl;
	}
	~Patient() {
		delete[] testResult;
	}
};

int main(void) {
	Patient p1;
	Patient p2;
	Patient p3;
	p1.input();
	p2.input();
	p3.input();
	p1.display();
	p2.display();
	p3.display();
	int opt;
	cout << "\n\nWhich Patient's Test You want to analyze: ";
	cin >> opt;
	if(opt==1) {
		Patient analyzep1(p1);
		analyzep1.display();
	}
	else if(opt==2) {
		Patient analyzep2(p2);
		analyzep2.display();
	}
	else if(opt==3) {
		Patient analyzep3(p3);
		analyzep3.display();
	}
	else	cout << "Invalid";
return 0;	
}