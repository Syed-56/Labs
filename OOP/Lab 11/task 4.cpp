#include <iostream>
#include <cmath>
#include <typeinfo>
using namespace std;

class NegativeNumberException : public std::exception {
	public:
	const char* what() const noexcept override {
		return "NegativeNumberException - Input must be Non-negative";
	}
};
class InvalidTypeException : public std::exception {
	public:
	const char* what() const noexcept override {
		return "InvalidTypeException - Input must be Number";
	}
};

template <typename T>
double squareroot(T num) {
	if(num < 0) {
		throw NegativeNumberException();
	}
	else {
		cout << "Square root of " << num << " = ";
		return sqrt(num);	//since the sqrt function's signature is double, we typecast num into double
	}
}

double squareroot(const char* num) {
    throw InvalidTypeException();
}

int main() {
	try {
		cout << squareroot(16) << endl;
		cout << squareroot(-4) << endl;
	} catch(NegativeNumberException &e) {
		cout << e.what() << endl;
	}
	
	try {
		cout << squareroot(4) << endl;
		cout << squareroot("Aloo") << endl;
	} catch(InvalidTypeException &e) {
		cout << e.what() << endl;
	}
	
}