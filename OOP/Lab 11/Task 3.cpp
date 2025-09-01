#include <iostream>
#include <fstream>
using namespace std;

class FileException : public std::exception {
	public:
	const char* what() const noexcept override {
		return "File Error Occured\t";
	}
};

class FileNotFoundException : public FileException{
	public:
	const char* what() const noexcept override {
		return "Error: File Not Found";
	}
};
class PermissionDeniedException : public FileException{
	public:
	const char* what() const noexcept override {
		return "Error: Permission Denied";
	}
};

int main() {
	try {
		ofstream file("Task 3 sample.txt");
		throw FileNotFoundException();
	} catch(FileNotFoundException &e) {
		cout << "Reading sample.txt ----- ";
		cout << e.what() << endl;
	}
	
	try {
		ofstream file("Task 3 secret.txt");
		throw PermissionDeniedException();
	} catch(PermissionDeniedException &e) {
		cout << "Reading secret.txt ----- ";
		cout << e.what() << endl;
	}
	
	return 0;
}