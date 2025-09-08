#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[i]>arr[j])   swap(arr[i],arr[j]);
        }
    }
}

int main() {
    int arr[5] = {1,4,2,5,3};
    bubbleSort(arr,5);
    for(int i=0; i<5; i++)  cout << arr[i] << " ";
}