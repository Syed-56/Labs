#include<iostream>
using namespace std;
class markerPens {
	public:
	string brand;
	string color;
	int inkLevel;
	bool refillability;
	
	void write() {
		inkLevel--;
	}
	void refill() {
		refillability=true;
		inkLevel=5;
	}
};
int main() {
	int n;
	cout << "How many different colour markers do you have Ahmed : ";
	cin >> n;
	markerPens Ahmed[n];
	for(int i=0; i<n; i++) {
		cin.ignore();
		cout << "\nInput for Marker " << i+1 << endl;
		cout << "Enter Brand: ";
		getline(cin, Ahmed[i].brand);
		cout << "Enter Colour: ";
		getline(cin, Ahmed[i].color);
		cout << "Enter Ink Level: ";
		cin >> Ahmed[i].inkLevel;
		while(Ahmed[i].inkLevel > 5) {
			cout << "Ink Level Exceeded. Enter Appropriate: ";
			cin >> Ahmed[i].inkLevel;
		}
		Ahmed[i].refillability = (Ahmed[i].inkLevel > 0) ? true:false;
	}
	int check;
	string ref;
	int opt=1;
	while(opt==1) {
		cout << "\nAhmed Starting His Lecture:-\n";
		for(int i=0; i<n; i++) {
			cout << "Ahmed Writing with " << Ahmed[i].brand << "'s " << Ahmed[i].color << " marker\n";
			Ahmed[i].write();
			if(Ahmed[i].inkLevel <= 0) {
				cout << "Refill Needed!\t Would you like to refill: ";
				cin >> ref;
				if(ref=="yes" || ref=="Yes")	Ahmed[i].refill();
			}
		}
		cout << "Do you want to check your Pen's Ink Level: ";
		cin >> ref;
		if(ref=="yes" || ref=="Yes") {
			for(int i=0; i<n; i++) {
				cout << "Ink Level of " << Ahmed[i].color << " Marker = " << Ahmed[i].inkLevel << endl;
			}	
		}
		cout << "Would You Like to take another class Ahmed?\n 1) Yes, 2) No\t Enter Corresponding Number: ";
		cin >> opt;
	}
return 0;
}