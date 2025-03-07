#include <iostream>
using namespace std;
class Electronics {
	public:
	string name;
	int id;
	float price;
	
	void inputElectronic() {
		cout << "Enter Name: ";
		getline(cin,name);
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter Price: ";
		cin >> price;
		cin.ignore();
	}
	void display() const {
		cout << "Name: " << name << "\tID: " << id << "\tPrice: " << price << endl;
	}
};
class Clothing {
	public:
	string name;
	int id;
	float price;
	
	void inputClothing() {
		cout << "Enter Name: ";
		getline(cin,name);
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter Price: ";
		cin >> price;
		cin.ignore();
	}
	void display() const {
		cout << "Name: " << name << "\tID: " << id << "\tPrice: " << price << endl;
	}
};
class Groceries {
	public:
	string name;
	int id;
	float price;
	
	void inputGroceries() {
		cout << "Enter Name: ";
		getline(cin,name);
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter Price: ";
		cin >> price;
		cin.ignore();
	}
	void display() const {
		cout << "Name: " << name << "\tID: " << id << "\tPrice: " << price << endl;
	}
};
class Store {
	public:
	string name;
	Electronics *e;
	Clothing *c;
	Groceries *g;
	int grocerySize,clothingSize,electronicSize;
//	int groceryCount=0, clothingCount=0, electronicCount=0;
	
	Store(string name) : name(name) {
		cout << "Enter Quantity of Electronics Products in Store: ";
		cin >> electronicSize;
		cout << "Enter Quantity of Clothing Products in Store: ";
		cin >> clothingSize;
		cout << "Enter Quantity of Grocery Products in Store: ";
		cin >> grocerySize;
		e = new Electronics[electronicSize];
		c = new Clothing[clothingSize];
		g = new Groceries[grocerySize];
	}
	
	void displayProduct() const {
		cout << "Electronics:-\n";
		for(int i=0; i<electronicSize; i++) {
			cout << "Product " << i+1 << " = ";
			e[i].display();
		}
		cout << "\nClothing:-\n";
		for(int i=0; i<clothingSize; i++) {
			cout << "Product " << i+1 << " = ";
			c[i].display();
		}
		cout << "\nGroceries:-\n";
		for(int i=0; i<grocerySize; i++) {
			cout << "Product " << i+1 << " = ";
			g[i].display();
		}
	}
	void searchProduct(string productName) {	
		for(int i=0; i<electronicSize; i++) { 
			if(productName==e[i].name) {
				cout << "Product Class: Electroincs\t Product Name: " << e[i].name << "\tProduct ID: " << e[i].id << "\tProduct Price: " << e[i].price;
				cout << endl;
				return;
			}
		}
		for(int i=0; i<grocerySize; i++) { 
			if(productName==g[i].name) {
				cout << "Product Class: Groceries\t Product Name: " << g[i].name << "\tProduct ID: " << g[i].id << "\tProduct Price: " << g[i].price;
				cout << endl;
				return;
			}
		}
		for(int i=0; i<clothingSize; i++) { 
			if(productName==c[i].name) {
				cout << "Product Class: Clothing\t Product Name: " << c[i].name << "\tProduct ID: " << c[i].id << "\tProduct Price: " << c[i].price;
				cout << endl;
				return;
			}
		}
		cout << "No Product Found\n";
	}
	void sort() {
		Electronics tempE;
		Clothing tempC;
		Groceries tempG;
		
		for(int i=0; i<electronicSize; i++) {
			for(int j=i+1; j<electronicSize; j++) {
				if(e[i].price > e[j].price) {	
					tempE = e[i];
					e[i] = e[j];
					e[j] = tempE;
				}
			}
		}
		for(int i=0; i<clothingSize; i++) {
			for(int j=i+1; j<clothingSize; j++) {
				if(c[i].price > c[j].price) {	
					tempC = c[i];
					c[i] = c[j];
					c[j] = tempC;
				}
			}
		}
		for(int i=0; i<grocerySize; i++) {
			for(int j=i+1; j<grocerySize; j++) {
				if(g[i].price > g[j].price) {	
					tempG = g[i];
					g[i] = g[j];
					g[j] = tempG;
				}
			}
		}
	}
	~Store() {
		delete[] e;
		delete[] c;
		delete[] g;
	}
};
void checkIDs(Store &s) {
	for(int i=0; i<s.electronicSize; i++) {
		for(int j=0; j<i; j++) {
			if(i==j)	continue;
			while(s.e[i].id == s.e[j].id) {
				cout << "Eletronic Product " << i+1 << " and " << j+1 << " Have Conflicting IDs\n";
				cout << "Enter ID of Product " << j+1 << " Again: ";
				cin >> s.e[i].id;
				j=0;
			}
		}
	}
	for(int i=0; i<s.clothingSize; i++) {
		for(int j=0; j<i; j++) {
			if(i==j)	continue;
			while(s.c[i].id == s.c[j].id) {
				cout << "Clothing Product " << i+1 << " and " << j+1 << " Have Conflicting IDs\n";
				cout << "Enter ID of Product " << j+1 << " Again: ";
				cin >> s.c[i].id;
				j=0;
			}
		}
	}
	for(int i=0; i<s.grocerySize; i++) {
		for(int j=0; j<i; j++) {
			if(i==j)	continue;
			while(s.g[i].id == s.g[j].id) {
				cout << "Grocery Product " << i+1 << " and " << j+1 << " Have Conflicting IDs\n";
				cout << "Enter ID of Product " << j+1 << " Again: ";
				cin >> s.g[i].id;
				j=0;
			}
		}
	}
}
int main(void) {
	Store s("Metro Super Store");
	cin.ignore();
	cout << "Input Electronics";
	for(int i=0; i<s.electronicSize; i++) {
		cout << "\nEnter Electronic Product " << i+1 << " detail:-\n";
		s.e[i].inputElectronic();
	}
	cout << endl;
	cout << "Input Clothing";
	for(int i=0; i<s.clothingSize; i++) {
		cout << "\nEnter Clothing Product " << i+1 << " detail:-\n";
		s.c[i].inputClothing();
	}
	cout << endl;
	cout << "Input Groceries";
	for(int i=0; i<s.grocerySize; i++) {
		cout << "\nEnter Grocery Product " << i+1 << " detail:-\n";
		s.g[i].inputGroceries();
	}
	cout << endl;
	
	checkIDs(s);
	string productName;
	cout << "Enter Product Name to search: ";
	getline(cin,productName);
	s.searchProduct(productName);
	cout << "\nBefore Sorting\n";
	s.displayProduct();
	s.sort();
	cout << "\nAfter Sorting\n";
	s.displayProduct();
return 0;
}