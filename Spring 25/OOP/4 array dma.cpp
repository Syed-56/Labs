#include <iostream>
using namespace std;
int main() {
	int r,c;
	cout<<"Enter Rows: "; cin>>r;
	cout<<"Enter Columns: "; cin>>c;
	
	int** arr = new int*[r];
	for(int i=0; i<r; i++) {
		arr[i] = new int[c];
	}
	cout<<"Enter Array : ";
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j++) {
			cin >> arr[i][j];
		}
	}
	cout<<"\nArray:-\n";
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j++) {
			cout << arr[i][j] << " " ;
		}
		cout<<"\n";
	}
	for(int i=0; i<r; i++) {
		delete[] arr[i];
	}
	delete[] arr;

}