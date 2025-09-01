#include <iostream>
using namespace std;

class SafePointer {
    int* ptr;

    public:
    SafePointer() {
        ptr = new int(0);
    }

    void setValue(int val) {
        if(ptr) {
            *ptr = val;
        }
    }

    int getValue() const {
        if (ptr) {
            return *ptr;
        } 
        else {
            cerr << "Null Pointer" << endl;
            return 1;
        }
    }

    ~SafePointer() {
        if (ptr != nullptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
};

int main() {
    const int n = 5;
    SafePointer students[n];

    cout << "Enter marks of " << n << " students\n";
    for (int i=0; i<n; i++) {
        int mark;
        cout << "Student " << i+1 << ": ";
        cin >> mark;
        students[i].setValue(mark);
    }

    cout << "Student Marks:-\n ";
    for (int i=0; i<n; i++) {
        cout << "Student " << i+1 << ": " << students[i].getValue() << endl;
    }
}