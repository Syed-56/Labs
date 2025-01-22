#include <iostream>
using namespace std;
bool checkParticipant(string name, int n1, int n2, string event1[], string event2[]) {	
	for(int i=0; i<n1; i++) {
		if(name==event1[i])		return true;
	}
	for(int i=0; i<n2; i++) {
		if(name==event2[i])		return true;
	}
	return false;
}
void printBarChart(int n1, int n2) {
	cout << "\t BarChart\nEvent No.";
	cout << "\n\t1 : ";
	for(int i=0; i<n1; i++)		cout << "*";
	cout << "\n\t2 : ";
	for(int i=0; i<n2; i++) 	cout << "*";
	cout << "\n\t   ";
	for(int i=0; i < ((n1>n2) ? n1 : n2); i++)	cout << "..";
	cout << endl << "\t   ";
	for(int i=0; i < ((n1>n2) ? n1 : n2); i++)	cout << i+1 << " ";
	cout << "\n\t  No. Of Participants";
}
void printParticipantInReverse(int n1, int n2, string event1[], string event2[]) {
	cout << "\nEvent 1\n";
	for(int i=(n1-1); i>=0; i--) {
		cout << "Participant " << i+1 << " : " << event1[i] << endl;
	}
	cout << "Event 2\n";
	for(int i=(n2-1); i>=0; i--) {
		cout << "Participant " << i+1 << " : " << event2[i] << endl;
	}
}
int main() {
	//Task 1
	int n1,n2;
	cout << "Enter Number of Participants in Event 1 : ";
	cin >> n1;
	while(n1>5) {
		cout << "Limit Exceeded for Maximum Number of Participants in Event 1. Enter Again : ";
		cin >> n1;
	}
	cout << "Enter Number of Participants in Event 2 : ";
	cin >> n2;
	while(n2>5) {
		cout << "Limit Exceeded for Maximum Number of Participants in Event 2. Enter Again : ";
		cin >> n2;
	}
	cin.ignore();
	string event1[n1], event2[n2];
	for(int i=0; i<n1; i++) {
		cout << "Enter Name of Participant " << i+1 << " In Event 1 : ";
		getline(cin,event1[i]);
	}
	for(int i=0; i<n2; i++) {
		cout << "Enter Name of Participant " << i+1 << " In Event 2 : ";
		getline(cin,event2[i]);
	}
	
	//Task 2
	string name;
	cout << "Enter Name to check if it is a Participant : ";
	getline(cin,name);
	cout << "Does " << name << " Participated in either of events? : ";
	int check = checkParticipant(name,n1,n2,event1,event2);
	cout << ((check) ? "Yes" : "No");
	
	//Task 3
	int amount = (n1*10) + (n2*10);
	cout << "\nTotal Amoun of Donation Calculated from Both Events : " << amount;
	
	//Task 4
	printParticipantInReverse(n1,n2,event1,event2);
	
	//Task 5
	printBarChart(n1,n2);
	
}