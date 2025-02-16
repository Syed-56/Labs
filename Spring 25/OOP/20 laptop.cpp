#include<iostream>
using namespace std;
class Laptop {
	public:
	string brand;
	string model;
	string processor;
	int RAM;
	int storage;
	
	void power() {
		cout << brand << " is turning on\n";
	}
	void runProgram() {
		int check;
		cout << "1) Google 2) Edge 3) VScode 4) Recycle Bin 5) Games 6) Ms Office\n";
		cout << "Which of the following programs to open: ";
		cin >> check;
		if(check==1)	cout << "Opening Google.exe";
		else if(check==2)	cout << "Opening Edge.exe";
		else if(check==3)	cout << "Opening Vscode.exe";
		else if(check==4)	cout << "Opening Recycle Bin.exe";
		else if(check==5)	cout << "Opening Games.exe";
		else if(check==6)	cout << "Opening Ms Office.exe";
		else	cout << "Program Not avalaible";
		cout << endl;
	}
	void checkSpecs() {
		cout << "\nBrand - " << brand;
		cout << "\nModel - " << model;
		cout << "\nProcessor - " << processor;
		cout << "\nRAM - " << RAM << " GB";
		cout << "\nStorage - " << storage << " SSD\n";
	}
	
	void input() {
		cout << "Enter Laptop Brand: ";
		getline(cin,brand);
		cout << "Enter Laptop Model: ";
		getline(cin,model);
		cout << "Enter Laptop Processor: ";
		getline(cin,processor);
		cout << "Enter Laptop RAM: ";
		cin >> RAM;
		cout << "Enter Laptop Storage: ";
		cin >> storage;
	}
};
int main(void) {
	Laptop ayesha, fatima;
	cout << "Input Ayesha Laptop Details:-\n";
	ayesha.input();
	cin.ignore();
	cout << "Input Fatima Laptop Details:-\n";
	fatima.input();
	int opt;
	
	while(true) {
		cout << "Who want to turn her laptop on? 1) Ayesha, 2) Fatima, 3) None(exit)\n Enter Option Number:   ";
		cin >> opt;
		if(opt==1) {
			ayesha.power();
			cout << "Do you want to run a program Ayesha? 1) Yes, 2) No\n Enter Option Number: ";
			cin >> opt;
			if(opt==1)	ayesha.runProgram();
			
			cout << "Do you want to check Laptop specs Ayesha? 1) Yes, 2) No\n Enter Option Number: ";
			cin >> opt;
			if(opt==1)	ayesha.checkSpecs();
		}
		else if (opt==2) {
			fatima.power();
			cout << "Do you want to run a program Fatima? 1) Yes, 2) No\n Enter Option Number: ";
			cin >> opt;
			if(opt==1)	fatima.runProgram();
			
			cout << "Do you want to check Laptop specs Fatima? 1) Yes, 2) No\n Enter Option Number: ";
			cin >> opt;
			if(opt==1)	fatima.checkSpecs();
		}
		else if (opt==3) {
			cout << "Exiting";
			break;
		}
		else	cout << "Invalid Input";
	}
	cout << endl;
	cout << ((ayesha.RAM > fatima.RAM) ? 
	        fatima.brand : ayesha.brand) 
	     << " has a better RAM than " 
	     << ((ayesha.RAM > fatima.RAM) ? 
	        ayesha.brand : fatima.brand) 
	     << endl;	cout << endl;
	cout << ((ayesha.storage > fatima.storage) ? 
	        fatima.brand : ayesha.brand) 
	     << " has a better RAM than " 
	     << ((ayesha.storage > fatima.storage) ? 
	        ayesha.brand : fatima.brand) 
	     << endl;	cout << endl;	cout << endl;
	cout << ((ayesha.processor > fatima.processor) ? 
	        fatima.brand : ayesha.brand) 
	     << " has a better RAM than " 
	     << ((ayesha.processor > fatima.processor) ? 
	        ayesha.brand : fatima.brand) 
	     << endl;	cout << endl;
return 0;
}