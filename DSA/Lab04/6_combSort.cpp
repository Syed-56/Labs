#include <iostream>
using namespace std;

int totalSwaps=0;
int totalComparisons=0;

void combSort(int arr[], int n) {
    float shrink=1.3;
    int gap = n;
    bool swapped = true;

    while(gap>1 || swapped) {
        gap = int(gap/shrink);
        if(gap < 1)  gap=1;
        swapped = false;

        for(int i=0; (i+gap)<n; i++) {
            totalComparisons++;
            if(arr[i] > arr[i+gap]) {
                swap(arr[i],arr[i+gap]);
                swapped = true;
                totalSwaps++;
            }
        }
    }
}

int main() {
    int arr[5] = {1,4,2,5,3};
    combSort(arr,5);
    for(int i=0; i<5; i++)  cout << arr[i] << " ";

    cout << "\nTotal Swaps = " << totalSwaps << "\t Total Comparisons = " << totalComparisons;
}