#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("19 data_records.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Error! Can't open file.";
        return 1;
    }

    file.seekg(9 * 2, ios::beg); 
    string line;
    getline(file, line);  
    cout << "Third record: " << line << endl;

    file.close();
    return 0;
}
