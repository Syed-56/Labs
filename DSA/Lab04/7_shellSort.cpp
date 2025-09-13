#include <iostream>
using namespace std;
int totalSwaps=0;
int totalComparisons=0;

void shellSort(int arr[], int n) {
    totalSwaps=0,totalComparisons=0;
    for(int gap=n/2; gap>0; gap/=2) {
        for(int i=gap; i<n; i++) {
            int key = arr[i];
            int j=i;

            while(j>=gap) {
                totalComparisons++;
                if(key < arr[j-gap]) {
                    totalSwaps++;
                    arr[j] = arr[j-gap];
                    j -= gap;
                }
                else break;
            }
            arr[j] = key;
            totalSwaps++;
        }
    }
}

void bubbleSort(int arr[], int n) {
    totalSwaps=0,totalComparisons=0;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n; j++) {
            totalComparisons++;
            if(arr[i]>arr[j]) {   
                swap(arr[i],arr[j]);
                totalSwaps++;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    totalSwaps=0,totalComparisons=0;
    for(int i=1; i<n; i++) {
        int key = arr[i];
        int j = i-1;

        while (j>=0) {                
            totalComparisons++;
            if(arr[j] > key) {
                totalSwaps++;
                arr[j+1] = arr[j];
                j--;
            }
            else break;
        }
        arr[j+1] = key;    
        totalSwaps++;    
    }
}

int main() {
    int unsortedArr[10] = {10,9,8,7,6,5,4,3,2,1};
    int arr[10];
    for(int i=0; i<10; i++)  arr[i] = unsortedArr[i];

    shellSort(arr,10);
    cout << "Shell Sort: ";
    for(int i=0; i<10; i++)  cout << arr[i] << " ";
    cout << "\nTotal Swaps = " << totalSwaps << "\tTotal Comparisons = " << totalComparisons;
    for(int i=0; i<10; i++)  arr[i] = unsortedArr[i];

    insertionSort(arr,10);
    cout << "\nInsertion Sort: ";
    for(int i=0; i<10; i++)  cout << arr[i] << " ";
    cout << "\nTotal Swaps = " << totalSwaps << "\tTotal Comparisons = " << totalComparisons;
    for(int i=0; i<10; i++)  arr[i] = unsortedArr[i];

    bubbleSort(arr,10);
    cout << "\nBubble Sort: ";
    for(int i=0; i<10; i++)  cout << arr[i] << " ";
    cout << "\nTotal Swaps = " << totalSwaps << "\tTotal Comparisons = " << totalComparisons;
    for(int i=0; i<10; i++)  arr[i] = unsortedArr[i];
}