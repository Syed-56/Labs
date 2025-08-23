#include <iostream>
using namespace std;

class Box {
private:
    int* value;

public:
    // Constructor
    Box(int val = 0) {
        value = new int(val);
        cout << "Constructor: value = " << *value << endl;
    }

    // Destructor
    ~Box() {
        cout << "Destructor: deleting value = " << *value << endl;
        delete value;
    }

    // Copy Constructor (Deep Copy)
    Box(const Box& other) {
        value = new int(*(other.value)); // allocate new memory
        cout << "Copy Constructor (Deep Copy): value = " << *value << endl;
    }

    // Copy Assignment Operator (Deep Copy)
    Box& operator=(const Box& other) {
        if (this != &other) {           // avoid self-assignment
            delete value;               // free old memory
            value = new int(*(other.value)); // allocate new memory
        }
        cout << "Copy Assignment Operator (Deep Copy): value = " << *value << endl;
        return *this;
    }

    // Setter
    void setValue(int val) {
        *value = val;
    }

    // Getter
    int getValue() const {
        return *value;
    }

    // Display
    void display() const {
        cout << "Box value = " << *value << endl;
    }
};

int main() {
    cout << "--- Shallow Copy Example (default behavior if Rule of Three is omitted) ---\n";
    // To simulate shallow copy, comment out copy constructor and assignment operator
    Box b1(10);

    // Shallow copy (if copy constructor is missing)
    Box b2 = b1; // default copy constructor creates shallow copy
    cout << "Original b1: "; b1.display();
    cout << "Shallow copy b2: "; b2.display();

    b1.setValue(20);
    cout << "After modifying b1:\n";
    cout << "b1: "; b1.display();
    cout << "b2: "; b2.display(); // b2 also affected if shallow copy

    cout << "\n--- Deep Copy Example (with Rule of Three) ---\n";
    Box b3(100);
    Box b4 = b3; // Uses our deep copy constructor
    cout << "Original b3: "; b3.display();
    cout << "Deep copy b4: "; b4.display();

    b3.setValue(200);
    cout << "After modifying b3:\n";
    cout << "b3: "; b3.display();
    cout << "b4: "; b4.display(); // b4 unaffected

    return 0;
}
