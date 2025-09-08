#include <iostream>
using namespace std;

void combSort(int arr[], int n) {
    float shrink=1.3;
    int gap = n;
    bool swapped = true;

    while(gap && swapped) {
        gap = int(gap/shrink);
        if(gap < 1)  gap=1;
        swapped = false;

        for(int i=0; (i+gap)<n; i++) {
            if(arr[i] > arr[i+gap]) {
                swap(arr[i],arr[i+gap]);
                swapped = true;
            }
        }
    }
}

int main() {
    int arr[5] = {1,4,2,5,3};
    combSort(arr,5);
    for(int i=0; i<5; i++)  cout << arr[i] << " ";
}