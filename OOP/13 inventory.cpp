#include <iostream>
using namespace std;
typedef struct{
	int productID;
	string name;
	int quantity;
	float price;
} product;

void printProduct(int n, product* p) {
	for(int i=0; i<n; i++) {
		cout << "\nName: " << p[i].name;
		cout << "\nID: " << p[i].productID;
		cout << "\nQuantity: " << p[i].quantity;
		cout << "\nPrice: " << p[i].price;
	}
}
void addProduct(int *n, product* p) {
	int newN;
	cout << "How Many Products You Want To Enter: ";
	cin >> newN;
	for(int i=*n; i<(newN+(*n)); i++) {
		cout << "\nEnter Product " << (i+1) << " Details:-\n";
		cout << "Enter Product ID: ";
		cin >> p[i].productID;
		cout << "Enter Product Price: ";
		cin >> p[i].price;
		cout << "Enter Product Quantity: ";
		cin >> p[i].quantity;
		cin.ignore();
		cout << "Enter Product Name: ";
		getline(cin,p[i].name);
	}
	*n += newN;
	printProduct(*n,p);
}
void removeProduct(int* n, product* p) {
	int id;
	cout << "Enter ID of Product you want to remove: ";
	cin >> id;
	for(int i=0; i<*n; i++) {
		if(id==p[i].productID) {
			id=i;
		}
	}
	for(int i=id; i<(*(n)-1); i++) {
		p[i] = p[i+1];
	}
	*n--;
	printProduct(*n,p);
}
void modifyProduct(int n, product* p) {
	int id;
	cout << "Enter ID of Product you want to Modify: ";
	cin >> id;
	for(int i=0; i<n; i++) {
		if(id==p[i].productID) {
			id=i;
		}
	}
	int opt;
	cout << "\n 1) Name\n 2) ID\n 3) Price\n 4) Quantity\n";
	cout << "Enter Corresponding Numbrs for What Do You Want To Modify: ";
	cin >>opt;
	if(opt==4) {
		cout << "Invalid Option\n";
		return;
	}
	if(opt>=1) {
		cin.ignore();
		cout << "Enter New Name: ";
		getline(cin,p[id].name);
	}
	if(opt>=2) {
		cout << "Enter New ID: ";
		cin >> p[id].productID;
	}
	if(opt>=3) {
		cout << "Enter New Price: ";
		cin >> p[id].price;
	}
	if(opt==4) {
		cout << "Enter New Quantity: ";
		cin >> p[id].quantity;
	}
}

int main() {
	product* p = new product[100];
	int n;
	cout << "How Many Products you want to create : ";
	cin >> n;
	for(int i=0; i<n; i++) {
		cout << "\nEnter Product " << (i+1) << " Details:-\n";
		cout << "Enter Product ID: ";
		cin >> p[i].productID;
		cout << "Enter Product Price: ";
		cin >> p[i].price;
		cout << "Enter Product Quantity: ";
		cin >> p[i].quantity;
		cin.ignore();
		cout << "Enter Product Name: ";
		getline(cin,p[i].name);
	}
	cout << "Welcome To Inventory";
	int op;
	while(1) {
		cout << "\n 1) Add Product\n 2) Remove Product\n 3) Modify Product\n 4) Exit\n";
		cout << "Press the corresponding Number to perform that functionality : ";
		cin >> op;
		if(op==1)	addProduct(&n,p);
		if(op==2)	removeProduct(&n,p);
		if(op==3)	modifyProduct(n,p);
		if(op==4)	break;
	}
	int sumQuantity=0;
	float sumPrice=0.0;
	for(int i=0; i<n; i++) {
		sumQuantity += p[i].quantity;
		sumPrice += p[i].price;
	}
	float val = sumQuantity * sumPrice;
	cout << "Total Value of Inventory System is " << val;
	delete[] p;
}