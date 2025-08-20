#include<iostream>
using namespace std;
class person{
	private :
		int salary;
	public:
		string name;
		int age;
		float height;
		//setter
		void setSalary(int newSalary) {
			salary = newSalary;
		}
		void setName(string newName) {
			name = newName;
		}
		void setAge(int newAge) {
			age = newAge;
		}
		void setHeight(float newHeight) {
			height = newHeight;
		}
		//getter
		int getSalary() {
			return salary;
		}
		string getName() {
			return name;
		}
		int getAge() {
			return age;
		}
		float getHeight() {
			return height;
		}
};
int main() {
	int n, age, salary;
	string name;
	float height;
	cout << "How many person you want to create? : " ;
	cin >> n;
	person p[n];
	for(int i=0; i<n; i++) {
		cin.ignore();
		cout << "Person " << i+1 << endl;
		cout << "Enter Name : " ;
		getline(cin, name);
		p[i].setName(name);
		cout << "Enter Age : " ;
		cin >> age;
		p[i].setAge(age);
		cout << "Enter Height : " ;
		cin >> height;
		p[i].setHeight(height);
		cout << "Enter Salary : ";
		cin >> salary;
		p[i].setSalary(salary);
	}
	for(int i=0; i<n; i++) {
		cout << "Person " << i+1 <<endl;
		cout << "Name : " << p[i].getName() << endl;
		cout << "Age : " << p[i].getAge() << endl;
		cout << "Height : " << p[i].getHeight() << endl;
		cout << "Salary : " << p[i].getSalary() << endl;
	}
}