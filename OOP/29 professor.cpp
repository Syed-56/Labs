#include <iostream>
using namespace std;

class Professor {
public:
    string name;
    string department;

    Professor() {}
    Professor(string name, string department) : name(name), department(department) {}

    void displayProf() const {
        cout << "Name: " << name << "\t Department: " << department << endl;
    }
};

class University {
public:
    string name;
    Professor *p;
    int profNum, index=0;

    University(string name) {
        this->name = name;
        cout << "Enter Number of Professors For this University: ";
        cin >> profNum;
        p = new Professor[profNum];
    }

    void addProfessor(Professor &prof) {
        if (index < profNum) {
            p[index] = prof;
            index++;
        }
    }

    void display() const {
        cout << "\nUniversity Name: " << name;
        cout << "\nProfessors Associated:-\n";
        for (int i=0; i<index; i++) {
            p[i].displayProf();
        }
    }

    ~University() {
        delete[] p;
    }
};

int main() {
    University uni("FAST-NUCES");

    cout << "How many professors you want to create: ";
    int n;
    cin >> n;
    cin.ignore();

    Professor *p = new Professor[n]; 
    string name, dept;

    for (int i=0; i<n; i++) {
        cout << "Input Professor " << i+1 << " Details\n";
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, dept);
        p[i] = Professor(name, dept);
    }

    for (int i=0; i<uni.profNum; i++) {
        cout << "Enter Name of a Professor to associate: ";
        getline(cin, name);
        bool found = false;

        for (int j=0; j<n; j++) {
            if (name==p[j].name) {
                uni.addProfessor(p[j]);
                found = true;
                cout << "Professor " << p[j].name << " of Department " << p[j].department << " is now associated with " << uni.name << endl;
                break;
            }
        }
        if (!found)    cout << "Professor Not Found\n";
    }
    uni.display();
    delete[] p; 
return 0;
}