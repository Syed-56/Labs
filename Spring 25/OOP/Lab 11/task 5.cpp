#include <iostream>
using namespace std;

class InsufficientFundsException : public std::exception {
	public:
	const char* what() const noexcept override {
		return " -- InsufficientFundsException";
	}
};

template <typename T>
class BankAccount {
	int balance;
	public:
	BankAccount(int b) : balance(b) {}
	void withdraw(float money) {
		if(money > balance) {
			cout << "Deficit: " << money-balance;
			throw InsufficientFundsException();
		}
		else {
			cout << "Witdrawn Rs " << money << endl;
			balance -= money;
		}
	}
	
};

int main() {
	BankAccount<int> b1(500);
	b1.withdraw(400);
	
	BankAccount<float> b2(400.5);
	try {
		b2.withdraw(500);
	} catch (InsufficientFundsException &e) {
		cout << e.what();
	}
	
	return 0;
}