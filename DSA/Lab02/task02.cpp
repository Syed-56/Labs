#include <iostream> 
using namespace std;

int main() {
    int** classroom = new int*[2];
    for(int i=0; i<2; i++) classroom[i] = new int[5];

    for(int i=0; i<2; i++) {
        for(int j=0; j<5; j++) {
            classroom[i][j] = 0;
        }
    }

    cout << "Enter 1 for occupied, 0 for not occupied\n";
    for(int i=0; i<2; i++) {
        cout << "Bench " << i+1 << endl;
        for(int j=0; j<5; j++) {
            cout << "Column " << j+1 << ": ";
            cin >> classroom[i][j];
        }
        cout << endl;
    }

    cout << "Seating Chart:-\n";
    for(int i=0; i<2; i++) {
        for(int j=0; j<5; j++) {
            cout << classroom[i][j] << " ";
        }
        cout << endl;
    }

    for(int i=0; i<2; i++) {
        delete classroom[i];
    }
    delete[] classroom;
}