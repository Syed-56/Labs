#include<iostream>
using namespace std;
class Account{
	private:
		int balance;
	public:
		string name;
		int acc_num;
		void setDetails(int bal) {
			balance = bal;
		}
		int getDetails() {
			return balance;
		}
		void displayDetails() {
			cout << "\nDetails:-\n" << endl;
			cout << "Account Holder = " << name << endl;
			cout << "Account Number = " << acc_num << endl;
			cout << "Account Balance = " << getDetails() << endl;
		}
};
int main() {
	Account acc1;
	int acc_bal;
	acc1.getDetails();
	cout << "Please Enter Details" << endl;
	cout << "Name : ";
	getline(cin, acc1.name);
	cout << "Account Number : ";
	cin >> acc1.acc_num;
	cout << "Account Balance : ";
	cin >> acc_bal;
	
	acc1.setDetails(acc_bal);
	acc1.displayDetails();
}