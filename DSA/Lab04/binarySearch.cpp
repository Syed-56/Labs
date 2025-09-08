#include <iostream>
using namespace std;

int binarysearch(int arr[], int n, int k) {
    int start=0, end=n-1;
    while(start <= end) {
        int mid = (start+end)/2;
        if(arr[mid] > k)    end = mid-1;
        else if(arr[mid] < k)   start = mid+1;
        else    return mid;
    }
    return -1;
}

int main() {
    int array[5] = {1,2,3,4,5};
    int k=2;
    cout << k << " found at index " << binarysearch(array,5,k);
}