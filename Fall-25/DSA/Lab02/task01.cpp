#include <iostream>
using namespace std;

void updateArray(int pos, int* arr) {
    cout << "Enter New Value: ";
    int val;
    cin >> val;
    arr[pos] = val;
}

int main() {
    int* arr;
    int n;
    cout << "Enter Size: ";
    cin >> n;
    arr = new int[n];

    for(int i=0; i<n; i++)  arr[i]=0;
    for(int i=0; i<n; i++) {
        bool update=false;
        cout << "\nYou want to update value at position " << i << "?\nEnter 1 for Yes and 2 for no: ";
        cin >> update;
        if(update)  updateArray(i,arr);
    }

    cout << "\nArray: ";
    for(int i=0; i<n; i++)  cout << arr[i] << " ";
    delete[] arr;
}