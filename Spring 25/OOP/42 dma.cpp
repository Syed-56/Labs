#include <iostream>
using namespace std;

int** AllocateMemory(int& row, int& col) {
	int **arr = new int*[row];
	for(int i=0; i<row; i++) {
		arr[i] = new int[col];
	}
	return arr;
}
void inputMatrix(int** arr, const int row, const int col) {
	for(int i=0; i<row; i++) {
		cout << "Input Row " << i+1 << ": ";
		for(int j=0; j<col; j++) {
			cin >> arr[i][j];
		}
	}
}
void displayMatrix(int** arr, const int& row, const int& col) {
	for(int i=0; i<row; i++) {
		cout << endl;
		for(int j=0; j<col; j++) {
			cout << arr[i][j] << "  ";
		}
	}
}
bool isAllDiagonal(int** arr, const int& row, const int& col) {
	if(row!=col)	return false;
	int firstElement = arr[0][0];
	for(int i=0; i<row-1; i++) {
		if(arr[i][i]!=firstElement) {
			return false;
		}
	}
	return true;
}

int main(void) {
	int row,col;
	cout << "Enter Rows: ";
	cin >> row;
	cout << "Enter Columns: ";
	cin >> col;
	
	int** arr = AllocateMemory(row,col);
	inputMatrix(arr,row,col);
	displayMatrix(arr,row,col);
	(isAllDiagonal(arr,row,col)) ? (cout << "\nAll Diagonal\n") : (cout << "\nAll Not Diagonal\n");
	
	for(int i=0; i<row; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}