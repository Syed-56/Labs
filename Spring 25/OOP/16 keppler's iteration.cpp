#include<iostream>
using namespace std;
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; 
	        for (int j = 0; j < n - 1 - i; j++) { 
            if (arr[j] > arr[j + 1]) { 
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true; 
            }
        }
        if (!swapped) {
            break;
        }
    }
}
int main() {
	int n1,n2;
	cout << "Enter Number:-\n";
	cin >> n1;
	while(n1>=9999) {
		cout << "To Check Kaprekar's Iteration, Enter 4 digit Number\n";
		cout << "Enter Number Again:-\n";
		cin >> n1;
	}
	int arr1[4], arr2[4];
	for(int i=0; i<4; i++) {
		arr1[4-1-i] = n1%10;
		n1/=10;
	}
	if((arr1[0]==arr1[1] && arr1[1]==arr1[2] && arr1[2]==arr1[3])) {
		cout << "Same Digits Number: Kaprekar's Iteratoin not possible";
		return 0;
	}
	cout << endl;
	int temp1;
	bubbleSort(arr1,4);
	for(int i=0; i<4; i++) {
		arr2[i] = arr1[4-1-i];
	}
	int kepp;
	for(int i=0; i<4; i++) {
		n1 = n1*10 + arr1[i];
		n2 = n2*10 + arr2[i];
	}
	kepp = n1>n2 ? (n1-n2):(n2-n1);
	cout << kepp;
}