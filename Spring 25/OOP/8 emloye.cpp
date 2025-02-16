#include<iostream>
using namespace std;
typedef struct {
	int employeeID;
	string name;
	string depart;
	int salary;
} employee;
void searchEmp(int n, employee* e) {
	int ID;
	cout << "\n\nEnter ID to search : "; 
	cin >> ID;
	for(int i=0; i<n; i++) {
		if(ID==e[i].employeeID) {
			cout << "Employee " << (i+1) << " ID : " << e[i].employeeID;
			cout << "\nEmployee " << (i+1) << " Name : " << e[i].name;
			cout << "\nEmployee " << (i+1) << " Departmen : " << e[i].depart;
			cout << "\nEmployee " << (i+1) << " Salary : " << e[i].salary;
			return;
		}
	}
	cout << "Employee Not Found";
}
int main() {
	int n;
	cout << "How many employees : ";
	cin >> n;
	employee* e = new employee[n];
	for(int i=0; i<n; i++) {
		cout << "\nInput Employee "<<(i+1)<<" Details:-\n";
		cout << "Enter Employee ID : "; 
		cin >> e[i].employeeID;
		cin.ignore();
		cout << "Enter Name : "; 
		getline(cin,e[i].name);
		cout << "Enter Department : "; 
		getline(cin,e[i].depart);
		cout << "Enter Salary : "; 
		cin >> e[i].salary;
	}
	for(int i=0; i<n; i++) {	
		cout << "\nEmployee " << (i+1) << " ID : " << e[i].employeeID;
		cout << "\nEmployee " << (i+1) << " Name : " << e[i].name;
		cout << "\nEmployee " << (i+1) << " Departmen : " << e[i].depart;
		cout << "\nEmployee " << (i+1) << " Salary : " << e[i].salary;
	}
	searchEmp(n,e);
	delete[] e;
}