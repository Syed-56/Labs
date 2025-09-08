#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        // Estimate position
        int pos = low + ((key - arr[low]) * (high - low) / (arr[high] - arr[low]));

        if (arr[pos] == key) return pos;
        if (arr[pos] < key) low = pos + 1; 
        else high = pos - 1;              
    }
    return -1; 
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 90;

    int index = interpolationSearch(arr, n, key);
    if (index != -1) cout << "Found at index " << index;
    else cout << "Not found";
}
