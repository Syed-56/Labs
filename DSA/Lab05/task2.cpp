#include <iostream>
using namespace std;

//part1: Direct Recursion
void printNumbers(int n) {
    if(n==0)    return;
    cout << n << "  ";
    printNumbers(n-1);
}

//part2: Indirect Recursion
void checkOrCall(int n);
void printNum(int n);

void printNum(int n) {
    cout << n << "  ";
    checkOrCall(n-1);
}

void checkOrCall(int n) {
    if(n==0)    return;
    else    printNum(n);
}

int main() {
    printNumbers(10);
    cout << endl;
    printNum(10);
}