#include<iostream>
using namespace std;
class Teacher {
	public:
		string name;
		string dept;
		string subj;
		int salary;
		//setters
		/* another way of using setter
			void setCredentials(string newName, string newDept, string newSubj, int newSalary) {
			name = newName;
			dept = newDept;
			subj = newSubj
			salary = newSalary;
		}
		*/
		void setName(string newName) {
			name = newName;
		}
		void setDept(string newDept) {
			dept = newDept;
		}
		void setSubj(string newSubj) {
			subj = newSubj;
		}
		void setSalary(int newSalary) {
			salary = newSalary;
		}
		//getters
		string getName() {
			return name;
		}
		string getDept() {
			return dept;
		}
		string getSubj() {
			return subj;
		}
		int getSalary() {
			return salary;
		}
};
int main() {
		Teacher t1, t2;
		//t1.setCredentials("Syed Sultan", "Mechanical", "Fluid Dynamics", 150000); another way of using getter
		t1.setName("Syed");
		t1.setDept("Computing");
		t1.setSubj("AI");
		t1.setSalary(250000);
		cout << "Name = " << t1.getName() << endl;
		cout << "Department = " << t1.getDept() << endl;
		cout << "Subject = " << t1.getSubj() << endl;
		cout << "Salary = " << t1.getSalary() << endl;
		cout << "----------------------------" << endl;
		t2.setName("Sultan");
		t2.setDept("Engineering");
		t2.setSubj("Calculas");
		t2.setSalary(100000);
		cout << "Name = " << t2.getName() << endl;
		cout << "Department = " << t2.getDept() << endl;
		cout << "Subject = " << t2.getSubj() << endl;
		cout << "Salary = " << t2.getSalary() << endl;
}