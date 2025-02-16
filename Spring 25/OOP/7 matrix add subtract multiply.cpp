#include<iostream>
using namespace std;
void matrixInput(int** arr, int m, int n) {
	cout << "Enter Array\n";
	for(int i=0; i<m; i++) {
		cout << "Enter Row "<<(i+1) << " : ";
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
}
int matrixSum(int** arr, int m, int n) {
	int sum=0;
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			sum += arr[i][j];
		}
	}
	return sum;
}
void matrixProduct(int** arr, int** arr2, int m, int n, int m1, int n1) {
	if(n!=m1) {
		cout << "Multiplication Not Possible";
		return;
	}
	int product[m][n1];
	for(int i=0; i<m; i++) {
		for(int j=0; j<n1; j++) {
			product[i][j] = 0;
		}
	}
	for(int i=0; i<m; i++) {
		for(int j=0; j<n1; j++) {
			for(int k=0; k<n; k++) {
				product[i][j] += (arr[i][k]) * (arr2[k][j]);
			}
		}
	}
	cout << "Matrix Multiplication:-\n";
	for(int i=0; i<m; i++) {
		for(int j=0; j<n1; j++) {
			cout << product[i][j] << " ";
		}
		cout << "\n";
	}
}
void matrixDiff(int** arr, int** arr2, int m, int n, int m1, int n1) {
	if(m!=m1 || n!=n1) {
		cout << "Subtraction Not Possible";
		return;
	}
	cout << "Matrix Subtraction:-\n";
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			cout << arr2[i][j] - arr[i][j] << " ";
		}
		cout << "\n";
	}
}
int main() {
	int m,n;
	cout << "Enter Rows : ";
	cin >> m;
	cout << "Enter Columns : ";
	cin >> n;
	int** arr = new int*[m];
	for(int i=0; i<m; i++) {
		arr[i] = new int[n];
	}
	matrixInput(arr,m,n);
	cout<<"Sum of Matrix = "<<matrixSum(arr,m,n) << endl;
	cout << "Enter Another matrix for multiply and subtraction\n";
	int m1,n1;
	cout << "Enter rows : ";
	cin >> m1;
	cout << "Enter columns : ";
	cin >> n1;
	int** arr2 = new int*[m1];
	for(int i=0; i<m; i++) {
		arr2[i] = new int[n];
	}
	matrixInput(arr2,m1,n1);
	matrixProduct(arr,arr2,m,n,m1,n1);
	matrixDiff(arr,arr2,m,n,m1,n1);
	for(int i=0; i<m; i++) {
		delete[] arr[i];
		delete[] arr2[i];
	}
	delete[] arr, arr2;
}