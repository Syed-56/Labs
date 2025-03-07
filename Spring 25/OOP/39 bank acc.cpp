#include <iostream>
using namespace std;
class Account {
	public:
	int accountNumber;
	float balance;
	
	void displayDetails() const {
		cout << "\nAccount Number: " << accountNumber << "\nBalance: " << balance;
	}		
};
class SavingsAccount : public Account {
	public:
	float interestRate;
	void displayDetails() const {
		Account::displayDetails();
		cout << "\nInterest Rate: " << interestRate;
	}
};
class CheckingAccount : public Account {
	public:
	float overdraftLimit;
	void displayDetails() const {
		Account::displayDetails();
		cout << "\nOverdraft Limit: " << overdraftLimit;
	}
};

int main() {
	SavingsAccount accSave;
	cout << "Input Details for Savings Account:-\n";
	cout << "Enter Account Number: ";
	cin >> accSave.accountNumber;
	cout << "Enter Balance: ";
	cin >> accSave.balance;
	cout << "Enter Interest Rate: ";
	cin >> accSave.interestRate;
	CheckingAccount accCheck;
	cout << "Input Details for Checkings Account:-\n";
	cout << "Enter Account Number: ";
	cin >> accCheck.accountNumber;
	cout << "Enter Balance: ";
	cin >> accCheck.balance;
	cout << "Enter Overdraft Limit: ";
	cin >> accCheck.overdraftLimit;
	
	accSave.displayDetails();
	cout << endl;
	accCheck.displayDetails();
return 0;
}