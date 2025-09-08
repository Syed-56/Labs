#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        int currentSmallest = i;
        for(int j=i+1; j<n; j++) {
            if(arr[j] < arr[currentSmallest])    currentSmallest = j;    
        }
        swap(arr[i], arr[currentSmallest]);
    }
}

int main() {
    int arr[5] = {1,4,2,5,3};
    selectionSort(arr,5);
    for(int i=0; i<5; i++)  cout << arr[i] << " ";
}