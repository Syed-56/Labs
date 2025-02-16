#include<iostream>
using namespace std;
class Product {
private:
	int productID;
	string productName;
	double price;
	int stockQuantity;
public:
	Product() {
		productID = 0;
		productName = "Unknown";
		price = 0.0;
		stockQuantity = 0;
	}
	Product(int pID, string pName, double p, int stock) {
		productID = pID;
		productName = pName;
		price = p;
		stockQuantity = stock;
	}
	
	void setter(int pID, string pName, double p, int stock) {
		productID = pID;
		productName = pName;
		price = p;
		stockQuantity = stock;
	}
	int getID() {
		return productID;
	}
	string getName() {
		return productName;
	}
	double getPrice() {
		return price;
	}
	int getStock() {
		return stockQuantity;
	}
	
	void display() {
		cout << "\nName : " << productName << "\nID : " << productID << "\nPrice : " << price << "\nStock : " << stockQuantity;
	}
};

int main(void) {
	Product p1;
	Product p2(1234,"Shampoo",25.4,5);
	
	p1.display();
	p2.display();
	p1.setter(2124,"Bottle",10.2, 7);
	cout << endl << p1.getName() << endl << p1.getID() << endl << p1.getPrice() << endl << p1.getStock();
return 0;
}