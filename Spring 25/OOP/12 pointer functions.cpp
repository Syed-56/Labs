#include<iostream>
using namespace std;
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void reverse(int* arr) {
	int temp;
	for(int i=0; i<4/2; i++) {
		temp = arr[4-i-1];
		arr[4-1-i] = arr[i];
		arr[i] = temp;
	}
}
int main() {
	int* arr = new int[4];
	cout << "Enter 4 Elements of Array : ";
	for(int i=0; i<4; i++) {
		cin >> arr[i];
	}
	int a,b;
	cout << "At Which indexes you want to swap variables : ";
	cin >> a; cin >> b;
	if(a>=4 || b>=4) {
		cout << "Invalid Index";
		return -1;
	}
	swap(&arr[a], &arr[b]);
	cout << "Modified Array : ";
	for(int i=0; i<4; i++)	cout << arr[i] << " ";
	reverse(arr);
	cout << "Reversed ARray : ";
	for(int i=0; i<4; i++)	cout << arr[i] << " ";
}