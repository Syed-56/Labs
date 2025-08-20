#include <iostream>
using namespace std;

class BankAccount {
    string name;
    float balance;

    public:
    BankAccount() {
        name = "Account1";
        balance = 0.0;
        cout << balance << endl;
    }
    BankAccount(float balance, string name = "Account2") {
        this->name = name;
        this->balance = balance;
        cout << balance << endl;
    }
    BankAccount(const BankAccount& other) {
        balance = other.balance;
    }

    void withdraw(float cash) {
        if(cash > balance)  cout << "Insufficient Funds\n";
        else {
            balance -= cash;
            cout << "Withdrawn Rs " << cash << endl;
        }
    }
    float getBalance() {
        return balance;
    }
};

int main() {
    BankAccount acc1;
    BankAccount acc2(100.0, "Sultan");
    BankAccount acc3(acc2);
    acc2.withdraw(50.0);
    cout << acc3.getBalance();
}