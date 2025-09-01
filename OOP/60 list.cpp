#include <iostream>
using namespace std;

class MyList {
    string *items;
    int size;
    int capacity;

public:
    MyList(int cap = 10) : size(0), capacity(cap) {
        items = new string[capacity];
    }

    // Overload + to add item to list
    friend MyList& operator+(string i, MyList &list) {
        if (list.size < list.capacity) {
            list.items[list.size] = i;
            list.size++;
        } else {
            cout << "List is full!" << endl;
        }
        return list;
    }

    friend ostream& operator << (ostream &out, const MyList &list) {
        for (int i = 0; i < list.size; i++) {
            out << list.items[i] << "  ";
        }
        out << endl;
        return out;
    }

    ~MyList() {
        delete[] items;
    }
};
