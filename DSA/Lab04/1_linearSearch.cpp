#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int k) {
    for(int i=0; i<n; i++) {
        if(arr[i]==k)   return i;
    }
    return -1;
}

int main() {
    int array[5] = {1,2,3,4,5};
    int k=2;
    int found = linearSearch(array,5,k);
    if(found!=-1) cout << k << " found at index " << found;
    else    cout << "Element Not Found";
}