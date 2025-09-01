#include <iostream>
using namespace std;

class Account {
		protected:
	long accountNumber;
	int balance;
	string accountHolderName;
	string type;
	
		public:
	int transactions[15];
	int count=0;
	
	Account(long aN, int b, string accHN, string t) {
		accountNumber = aN;
		balance = b;
		type = t;
		while(t != "Fixed Deposit" && t != "Current" && t != "Savings") {
			cout << "Invalid Account Type!! \nEnter Correct: ";
			getline(cin,type);
			type = t;
		}
		accountHolderName = accHN;
	}
	
	void deposit(int amount) {
		if(count==14) {
			cout << "Deleting previous " << count+1 << " Transactions for storage\n";
			for(int i=0; i<count; i++)	transactions[i] = 0;
			count=0;
		}
		balance += amount;
		cout << "Deposited " << amount << " Rs\n";
		cout << "New Balance: " << balance << endl;
		transactions[count] = amount;
		count++;
		
	}
	virtual void withdraw(int amount) {
		if(count==14) {
			cout << "Deleting previous " << count+1 << " Transactions for storage\n";
			for(int i=0; i<count; i++)	transactions[i] = 0;
			count=0;
		}
		if(balance >= amount) {
			balance -= amount;
			cout << "Withdrawn " << amount << " Rs\n";
			cout << "New Balance: " << balance << endl;
			transactions[count] = -amount;
			count++;
		}
		else {
			cout << "Insufficient Funds\n";
		}
	}
	virtual void calculateInterest(int years) {
		float interest = balance/(years*10);
		cout << "Interest on current balance for " << years << " years: Rs " << interest << endl;
	}
	virtual void printStatement() const {
		for(int i=0; i<count; i++) {
			cout << "Transaction " << i+1 << " : ";
			(transactions[i] >= 0) ? cout << "Deposited Rs " << transactions[i] : cout << "Withdrawn Rs " << -transactions[i];
			cout << endl;
		}
	}
	void getAccountInfo() const {
		cout << "Account Number: " << accountNumber;
		cout << "\nBalance: " << balance;
		cout << "\nAccount Holder Number: " << accountHolderName;
		cout << "\nAccount Type: " << type << endl;
	}
};

class SavingsAccount : public Account {
	float interestRate;
	int minimumBalance;
	
		public:
	SavingsAccount(long aN, int b, string accHN, string t, float rate, int minB) : Account(aN,b,accHN,t) {
		interestRate = rate;
		minimumBalance = minB;
	}
	
	void calculateInterest(int years) {
		float interest = balance/(years*10) + balance/interestRate;
		cout << "Savings Account's interest on current balance for " << years << " years: Rs " << interest << endl;
	}
	void printStatement() const {
		cout << "Interest Rate applied on your balance for each transaction  = " << interestRate << endl;
		for(int i=0; i<count; i++) {
			cout << "Transaction " << i+1 << " : ";
			(transactions[i] >= 0) ? cout << "Deposited Rs " << transactions[i] : cout << "Withdrawn Rs " << -transactions[i];
			cout << endl;
		}
	}
};
class CheckingAccount : public Account {
	float transactionFee;
	
		public:
	CheckingAccount(long aN, int b, string accHN, string t, float fee) : Account(aN,b,accHN,t) {
		transactionFee = fee;
	}
	void calculateInterest(int years) {
		cout << "No Interest avalaible for fixed Deposit Account\n";
	}
	void printStatement() const {
		cout << "Rs " << transactionFee << " will be deducted for each transaction record\n";	
		for(int i=0; i<count; i++) {
			cout << "Transaction " << i+1 << " : ";
			(transactions[i] >= 0) ? cout << "Deposited Rs " << transactions[i] : cout << "Withdrawn Rs " << -transactions[i];
			cout << endl;
		}
	}
	void withdraw(int amount) override {
		if(count==14) {
			cout << "Deleting previous " << count+1 << " Transactions for storage\n";
			for(int i=0; i<count; i++)	transactions[i] = 0;
			count=0;
		}
		if(balance >= amount) {
			balance = balance-amount-transactionFee;
			cout << "Withdrawn " << amount << " Rs\n";
			cout << "New Balance: " << balance << endl;
			transactions[count] = -amount;
			count++;
		}
		else {
			cout << "Insufficient Funds\n";
		}
	}
};
class FixedDepositAccount : public Account {
	string maturityDate;
	float fixedInterestRate;
	
		public:
	FixedDepositAccount(long aN, int b, string accHN, string t, float fixRate, string date) : Account(aN,b,accHN,t) {
		maturityDate = date;
		fixedInterestRate = fixRate;
	}
	
	void calculateInterest(int years) {
		float interest = balance/(years*10) * fixedInterestRate;
		cout << "Fixed Deposit Account's interest on current balance for " << years << " years: Rs " << interest << endl;
	}
	void printStatement() const {
	cout << "There will be a total of " << fixedInterestRate << " applied on your balance for each deposit\n";
		for(int i=0; i<count; i++) {
			cout << "Transaction " << i+1 << " : ";
			(transactions[i] >= 0) ? cout << "Deposited Rs " << transactions[i] : cout << "Withdrawn Rs " << -transactions[i];
			cout << endl;
		}
	}
};

int main() {
	SavingsAccount a1(90078601,50000,"Syed Sultan","Savings",2.5,1000);
	CheckingAccount a2(223190,100000,"Syed Khizer","Current",100);
	FixedDepositAccount a3(5618107,250000,"Syed Mubashir","Fixed Deposit",1.5,"17/March/2025");
	a1.deposit(500);
	a1.calculateInterest(5);
	a2.calculateInterest(5);
	a3.calculateInterest(5);
	cout << endl;
	a1.deposit(900);
	cout << endl;
	a2.getAccountInfo();
	cout << endl;
	a1.printStatement();
	a2.printStatement();
	a3.printStatement();
return 0;
}