#include <iostream>
using namespace std;

class Box {
private:
    int* value;

public:
    Box(int val = 0) {
        value = new int(val);
        cout << "Constructor: value = " << *value << endl;
    }

    ~Box() {
        cout << "Destructor: deleting value = " << *value << endl;
        delete value;
    }

    Box(const Box& other) {
        value = new int(*(other.value)); 
        cout << "Copy Constructor (Deep Copy): value = " << *value << endl;
    }

    Box& operator=(const Box& other) {
        if (this != &other) {           
            delete value;               
            value = new int(*(other.value));
        }
        cout << "Copy Assignment Operator (Deep Copy): value = " << *value << endl;
        return *this;
    }

    void setValue(int val) {
        *value = val;
    }

    int getValue() const {
        return *value;
    }

    void display() const {
        cout << "Box value = " << *value << endl;
    }
};

int main() {
    cout << "--- Shallow Copy Example (default behavior if Rule of Three is omitted) ---\n";
    Box b1(10);

    Box b2 = b1; 
    cout << "Original b1: "; b1.display();
    cout << "Shallow copy b2: "; b2.display();

    b1.setValue(20);
    cout << "After modifying b1:\n";
    cout << "b1: "; b1.display();
    cout << "b2: "; b2.display(); 

    cout << "\n--- Deep Copy Example (with Rule of Three) ---\n";
    Box b3(100);
    Box b4 = b3; 
    cout << "Original b3: "; b3.display();
    cout << "Deep copy b4: "; b4.display();

    b3.setValue(200);
    cout << "After modifying b3:\n";
    cout << "b3: "; b3.display();
    cout << "b4: "; b4.display(); 

    return 0;
}