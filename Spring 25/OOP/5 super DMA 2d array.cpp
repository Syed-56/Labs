#include <iostream>
using namespace std;
int main() {
	int rows,cols;
	cout<<"Enter Rows: "; cin>>rows;
	cout<<"Enter Columns: "; cin>>cols;
	
	int** arr = new int*[rows];
	for(int i=0; i<rows; i++) {
		arr[i] = new int[cols];
	}
	for(int i=0; i<rows; i++) {
		cout << "Enter Row"<<(i+1)<<": ";
		for(int j=0; j<cols; j++) {
			cin >> *(*(arr+i) + j);
		}
	}
	cout<<"\nArray:-\n";
	for(int i=0; i<rows; i++) {
		for(int j=0; j<cols; j++) {
			cout << *(*(arr+i)+j) << " ";
		}
		cout << "\n";
	}
	for(int i=0; i<rows; i++) {
		delete[] *(arr+i);
	}
	delete[] arr;
}