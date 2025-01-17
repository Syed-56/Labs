#include<iostream>
using namespace std;
class bankAccount {
	string accountNumber;
	double balance;
	
	public:
		bankAccount(string accountNumber, double balance) {
			this->accountNumber = accountNumber;
			this->balance = balance;
		}
		void deposit() {
			int amount;
			cout<<"Enter Amount to Deposit : ";
			cin>>amount;
			balance += amount;
		}
		void withdraw() {
			int amount;
			cout<<"Enter Amount to Withdraw : ";
			cin>>amount;
			if(amount > balance)	cout<<"Insufficient Funds"<<endl;
			else	balance -= amount;
		}
		void checkBalance()	{
			cout<<"Balance = "<<balance<<endl;
		}
};

int main() {
	bankAccount sultan("12345678",0);
	sultan.deposit();
	sultan.withdraw();
	sultan.checkBalance();
return 0;
}