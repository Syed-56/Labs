#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        int key = arr[i];
        int j = i-1;

        while (j>=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;        
    }
}

int binarySearch(int arr[], int n, int target) {
    int start=0, end=n-1;
    while(start <= end) {
        int mid = (start+end)/2;
        if(arr[mid] > target)    end=mid-1;
        else if(arr[mid] < target)   start=mid+1;
        else    return mid;
    }
    return -1;
}

int main() {
    int arr[5] = {1,4,2,5,3};
    insertionSort(arr,5);
    cout << "Sorted Array: ";
    for(int i=0; i<5; i++)  cout << arr[i] << " ";
    int target=3;
    int found = binarySearch(arr,5,target);
    if(found != -1) cout << "\nTarget Found at index " << found;
    else    cout << "Target Not Found";
}