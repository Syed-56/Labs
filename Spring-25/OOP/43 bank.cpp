#include <iostream>
using namespace std;
int n;
class bankAccount {
	string name;
	long accNum;
	string accType;
	float balance;
	
	public:
	bankAccount () {}
	bankAccount(string n, long accN, string accT, float b) {
		name = n;
		accNum = accN;
		accType = accT;
		balance = b;
	}
	bankAccount(const bankAccount& obj) {
		name = obj.name;
		accNum = obj.accNum;
		accType = obj.accType;
		balance = obj.balance;
	}
	
	void setName(string n) {name = n;}
	void setNum(long num) {accNum = num;}
	void setType(string type) {accType = type;}
	void setBalance(float b) {balance = b;}
	
	long getAccNum() {return accNum;}
	string getName() {return name;}
	float getBalance() {return balance;}
	
	void deposit(int amount) {
		balance += amount;
	}
	void withdraw(int amount) {
		if(amount > balance) {
			cout << "Insufficient Funds\n";
			return;
		}
		balance -= amount;
	}
	void display() const {
		cout << "Account Holder Name: " << name << endl;
		cout << "Account Number: " << accNum << endl;
		cout << "Account Type: " << accType << endl;
		cout << "Current Balance: " << balance << endl;
	}
	void copyFrom(const bankAccount& obj) {
		name = obj.name;
		accNum = obj.accNum;
		accType = obj.accType;
		balance = obj.balance;
	}
};

void bankInput(bankAccount& b) {
	string name,type;
	long num;
	float balance;
	cin.ignore();
	cout << "Enter Account Holder Name: ";
	getline(cin,name);
	b.setName(name);
	cout << "Enter Account Type: ";
	getline(cin,type);
	b.setType(type);
	cout << "Enter Account Number: ";
	cin >> num;
	b.setNum(num);
	cout << "Enter Initial Balance: ";
	cin >> balance;
	b.setBalance(balance);
}
void sort(bankAccount b[]) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n-i-1; j++) {
			if(b[j].getBalance() > b[j+1].getBalance()) {
				bankAccount temp = b[j];
				b[j].copyFrom(b[j+1]);
				b[j+1].copyFrom(temp);
			}
		}
	}
	cout << "Accounts Sorted\n";
}
bool isDuplicate(bankAccount b[], int size, long accNum) {
    for (int i = 0; i < size; i++) {
        if (b[i].getAccNum() == accNum) return true;
    }
    return false;
}

int main() {
	bankAccount *b;
	cout << "Enter Number of Bank Accounts: ";
	cin >> n;
	b = new bankAccount[n];
	int num;
	for(int i=0; i<n; i++) {
		cout << "Input Account " << i+1 << " Details\n";
		bankInput(b[i]);
		while (isDuplicate(b, i, b[i].getAccNum())) {
            cout << "Account Number already exists. Enter another Account Number: ";
            long newNum;
            cin >> newNum;
            b[i].setNum(newNum);
        }
	}

	int opt;
	cout << "\n1) Deposit Money\n2) Witdraw Money\n3) Display Accounts Info\n4) Sort Accounts by Balance\n5) Add Account\n6) Remove Account\n7) Exit";
	while(true) {
		cout << "\nEnter Option: ";
		cin >> opt;
		cout << endl;
		if(opt==1) {
			cout << "\nWhich Account wants to deposit money: ";
			cin >> num;
			for(int i=0; i<n; i++) {
				if(num==b[i].getAccNum()) {
					cout << "Enter Amount to Deposit: ";
					cin >> num;
					b[i].deposit(num);
					cout << "Rupees" << num << " Deposited into account of " << b[i].getName();
					break;
				}
				if(i==n-1)	cout << "Account Not Found\n";
			}
		}
		else if(opt==2) {
			cout << "\nWhich Account wants to Withdraw money: ";
			cin >> num;
			for(int i=0; i<n; i++) {
				if(num==b[i].getAccNum()) {
					cout << "Enter Amount to Withdraw: ";
					cin >> num;
					b[i].withdraw(num);
					cout << "Rupees" << num << " Withdrawn from account of " << b[i].getName();
					break;
				}
				if(i==n-1)	cout << "Account Not Found\n";
			}
		}
		else if(opt==3) {
			for(int i=0; i<n; i++) {
				cout << "Account " << i+1 << " Details:-\n";
				b[i].display();
			}
		}
		else if(opt==4) {
			sort(b);
		}
		else if(opt==5) {
			bankAccount* temp = new bankAccount[n+1];
            for (int i=0; i<n; i++) temp[i] = b[i];
            cout << "Enter New Account Details:\n";
            bankInput(temp[n]);
            while (isDuplicate(temp, n, temp[n].getAccNum())) {
                cout << "Account Number already exists. Enter another Account Number: ";
                long newNum;
                cin >> newNum;
                temp[n].setNum(newNum);
            }
            delete[] b;
            b = temp;
            n++;
		}
		else if(opt==6) {
			int found=-1;
			cout << "Enter Account Number to remove: ";
			cin >> num;
			for(int i=0; i<n; i++) {
				if(num==b[i].getAccNum())	found=i;
			}
			if(found==-1) {
				cout << "Account Not Found\n";
				break;
			}
			bankAccount* temp = new bankAccount[n-1];
			for(int i=0, j=0; i<n; i++) {
				if(i==found)	continue;
				temp[i] = b[i];
				j++;
			}
			delete[] b;
			b = temp;
			n--;
			cout << "Account Removed\n";
		}
		else if(opt==7) {
			cout << "Exiting Bank Account\b";
			break;
		}
		else	cout << "Invalid Option\n";
	}
	delete[] b;
}