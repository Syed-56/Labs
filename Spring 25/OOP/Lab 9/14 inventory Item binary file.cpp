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
	
	file.write(reinterpret_cast<char*>(&i1.itemID), sizeof(i1.itemID));  //writing itemID
//	int nameLegnth = i1.itemName.size();	//getting legnth of item name
//	file.write(reinterpret_cast<char*>(nameLegnth), sizeof(nameLegnth));
//	file.write(i1.itemName.c_str(), i1.itemName);	this is for string datatype
	file.write(i1.itemName, sizeof(i1.itemName));
	
	file.seekg(0);	//move cursor to beginning of file
	file.read(reinterpret_cast<char*>(&i1.itemID), sizeof(i1.itemID));  //writing itemID
//	file.read(reinterpret_cast<char*>(nameLegnth), sizeof(nameLegnth));
//	file.read(i1.itemName.c_str(), i1.itemName);	this is for string datatype
	file.read(i1.itemName, sizeof(i1.itemName));
	file.close();
	
	cout << "Item ID: " << i1.itemID;
	cout << "\nItem Name: " << i1.itemName;	//this will strill work without using write but that means the consolde displays from memory not from file
	return 0;
}