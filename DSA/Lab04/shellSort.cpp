#include <iostream>
using namespace std;

void shellSort(int arr[], int n) {
    for(int gap=n/2; gap>0; gap/=2) {
        for(int i=gap; i<n; i++) {
            int key = arr[i];
            int j=i;

            while(j>=0 && key < arr[j-gap]) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}

int main() {
    int arr[5] = {1,4,2,5,3};
    shellSort(arr,5);
    for(int i=0; i<5; i++)  cout << arr[i] << " ";
}