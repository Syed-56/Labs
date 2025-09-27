#include <iostream>
using namespace std;

int sumTail(int n, int sum) {
    if(n==0) {
        cout << n << " = ";
        return sum;
    }
    cout << n << " + ";
    return sumTail(n-1,sum+n);
}

int sumNonTail(int n) {
    if(n==0) {
        cout << n << " = ";
        return 0;
    }
    cout << n << " + ";
    int sum = sumNonTail(n-1);
    return n+sum;
}

int main() {
    int sum = sumTail(6,0);
    cout << sum << endl;
    sum = sumNonTail(6);
    cout << sum << endl;
}