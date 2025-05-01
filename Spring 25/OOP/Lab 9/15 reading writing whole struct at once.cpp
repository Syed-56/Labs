#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	int itemID;
	char itemName[20];
} InventoryItem;

int main() {
	InventoryItem i1;
	fstream file("14 Inventory.txt", ios::in | ios::out | ios::binary);	//opening binary file in read+write mode
	if(!file.is_open()) {
		cerr << "Error! Can't Open File";
		return 1;
	}
	
	i1.itemID = 1234;
	strcpy(i1.itemName,"Food");
	
	file.write(reinterpret_cast<char*>(&i1), sizeof(i1));  
	//reason for creating diff variable to read is bcz mostly reading are writing are done seperately, and it also shows that we read from file not from mem
	InventoryItem i2;
	file.seekg(0);	//move cursor to beginning of file
	file.read(reinterpret_cast<char*>(&i2), sizeof(i2));  //reading itemID
	file.close();
	
	cout << "Item ID: " << i2.itemID;
	cout << "\nItem Name: " << i2.itemName;	//this wont work without reading from file. however if we didnt created another struct, then it would've worked
	return 0;
}