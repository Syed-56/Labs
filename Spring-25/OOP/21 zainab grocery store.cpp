#include<iostream>
using namespace std;
class groceryStore {
	public:
	string items[15];
	float prices[15];
	
	void addItems(int* n) {
		int N;
		cout << "How Many Items you want to add: ";
		cin >> N;
		cin.ignore();
		while(*n>15) {
			cout << "Limit Exceeded! Enter Appropriate Item Numbers: ";
			cin >> N;
		}
		int old = *n;
		*n += N;
		for(int i=old; i<*n; i++) {
			cout << "Enter Item "  << i+1 << " Name: ";
			getline(cin,items[i]);
			cout << "Enter " << items[i] << "'s Price: ";
			cin >> prices[i];
			cin.ignore();
		}
	}
	void UpdatePrices(int* n) {
		string name;
		cout << "Enter Item's Name to update price: ";
		getline(cin,name);
		for(int i=0; i<*n; i++) {
			if(name==items[i]) {
				cout << "Enter New Price: ";
				cin >> prices[i];
				return;
			}
		}
		cout << "Item Not Found\n";
	}
	void viewInventory(int* n) {
		for(int i=0; i<*n; i++) {
			cout << "\n" << i+1 << ") " << items[i] << " \t Price: " << prices[i];
		}
	}
};
int main() {
	groceryStore Zainab;
	int n;
	cout << "With How many items you want to setup your grocery store: ";
	cin >> n;
	cin.ignore();
	while(n>15) {
		cout << "Limit Exceeded! Enter Appropriate Item Numbers: ";
		cin >> n;
	}
	cout << "\nSetup your grocery Store\n";
	for(int i=0; i<n; i++) {
		cout << "Enter Item "  << i+1 << " Name: ";
		getline(cin,Zainab.items[i]);
		cout << "Enter " << Zainab.items[i] << "'s Price: ";
		cin >> Zainab.prices[i];
		cin.ignore();
	}
	int opt;
	while(true) {
		cout << "\n1) Add Items\n2) Update Prices\n3) View Inventory\n4) Exit\n Enter Option Number for Action: ";
		cin >> opt;
		cin.ignore();
		
		if	   (opt==1)	 Zainab.addItems(&n);
		else if(opt==2)	 Zainab.UpdatePrices(&n);
		else if(opt==3)	 Zainab.viewInventory(&n);
		else if(opt==4)	 break;
		else	cout << "Invalid Option\n";
	}
	int value=0;
	for(int i=0; i<n; i++) {
		value += Zainab.prices[i];
	}
	cout << "Valuation of Zainab's Grocery Store: " << value << "$";
return 0;
}