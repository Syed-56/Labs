#include<iostream>
using namespace std;
class bankAccount{
	private:
		string accountNumber;
		double balance;
	public:
		bankAccount(string accNumber) {
            accountNumber = accNumber;
            balance = 0.0;
        }
        void deposit(double amount) {
            balance += amount;
            cout << "Deposited " << amount << ". New balance: " << balance << endl;
        }
        void withdraw(double amount) {
        	if(amount <= balance) {
         		balance -= amount;
                cout << "Withdrew " << amount << ". New balance: " << balance << endl;
			}
			else 	cout << "Insufficient funds." << endl;
		}
		void checkBalance() {
            cout << "Current balance: " << balance << endl;
        }
};
int main() {
    bankAccount acc("24k-0585");
    int menu;
    double amount;

    while (true) {
        cout << "1) Deposit  2) Withdraw  3) Check Balance  4) Exit\n";
        cout << "What do you want: ";
        cin >> menu;

        if (menu == 1) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            acc.deposit(amount);
        } else if (menu == 2) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            acc.withdraw(amount);
        } else if (menu == 3) {
            acc.checkBalance();
        } else if (menu == 4) {
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid operation. Try again." << endl;
        }
    }
    return 0;
}