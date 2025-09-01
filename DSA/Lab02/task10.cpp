#include <iostream>
using namespace std;

class LibraryRecords {
    int** bookIDs;
    int numCategories;
    int* numBooks;
    string* categories;

    public:
    LibraryRecords(int n) {
        numCategories = n;
        bookIDs = new int*[numCategories];
        numBooks = new int[numCategories];
        categories = new string[numCategories];

        for (int i=0; i<numCategories; i++) {
            cout << "Enter Name of Category " << i+1 << ": ";
            cin >> categories[i];

            cout << "Enter Number of Books in " << categories[i] << ": ";
            cin >> numBooks[i];

            bookIDs[i] = new int[numBooks[i]];
            cout << "Enter Book IDs for " << categories[i] << endl;
            for (int j=0; j<numBooks[i]; j++) {
                cout << "\tBook " << j+1 << ": ";
                cin >> bookIDs[i][j];
            }
        }
    }

    void searchBook(int id) {
        for (int i=0; i<numCategories; i++) {
            for (int j=0; j<numBooks[i]; j++) {
                if (bookIDs[i][j] == id) {
                    cout << "Book with ID " << id << " Found in Category " << categories[i] << endl;
                    return;
                }
            }
        }
        cout << "Book " << id << " Not Found in Library Records.\n";
    }

    ~LibraryRecords() {
        for (int i=0; i<numCategories; i++) {
            delete bookIDs[i];
        }
        delete[] bookIDs;
        delete[] numBooks;
        delete[] categories;
    }
};

int main() {
    int n;
    cout << "Enter Number of Categories: ";
    cin >> n;
    LibraryRecords library(n);

    int searchID;
    cout << "Enter Book ID to Search: ";
    cin >> searchID;
    library.searchBook(searchID);
}