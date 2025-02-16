#include <iostream>
using namespace std;
int maxVal(int n, int arr[]) {
	int max=arr[0];
	for(int i=0; i<n; i++) {
		if(arr[i] > max)	max = arr[i];
	}
	return max;
}

int main() {
	int n;
	cout << "Enter Size : ";
	cin >> n;
	int* arr = new int[n];
	cout << "Enter Array : ";
	for(int i=0; i<n; i++)	cin >> arr[i];
	cout << "\nMax Value in array = " << maxVal(n,arr);
	int sum=0;
	for(int i=0; i<n; i++)	sum += arr[i];
	cout << "\nSum of Array = " << sum;
	cout << "\nAverage of Array = " << float(sum)/float(n);
	delete[] arr;
}