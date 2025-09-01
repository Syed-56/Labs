#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Open the file in both read and write mode
    fstream file("17 confg.txt", ios::in | ios::out);

    // Check if the file was opened correctly
    if (!file.is_open()) {
        cerr << "Error! Can't open file" << endl;
        return 1;
    }

    // Read the entire content of the file into a string
    string content, line;
    while (getline(file, line)) {
        content += line + "\n";  // Read each line and append it to 'content'
    }

    // Find and replace the substring "BBBB" with "XXXX"
    size_t pos = content.find("BBBB");
    if (pos != string::npos) {
        content.replace(pos, 4, "XXXX");
    }

    // Move the file pointer back to the beginning of the file for writing
    file.seekp(0);

    // Write the modified content back to the file
    file << content;

    // Close the file
    file.close();

    cout << "Data replaced successfully!" << endl;
    return 0;
}
