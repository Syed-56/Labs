#include <iostream>
using namespace std;

class InvalidValueException : public std::exception {	//std::Exception is a standard class with multpiple exception virtual functions like what()
	public:
	const char* what() {
		return "Invalid Age";
	}
};

int main() {
	int age;
	cout << "Enter Age: ";
	cin >> age;
	
	try {
		if(age>120 || age<0)	throw InvalidValueException();
		else	cout << "Age: " << age;
	}
	catch (InvalidValueException e) {
		cout << "Age: " << e.what();
	}
}