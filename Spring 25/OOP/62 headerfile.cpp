#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
using namespace std;

class Book {
protected:
    string title;
    string author;
    string ISBN;

public:
    Book() {} 
    Book(string t, string a, string i) : title(t), author(a), ISBN(i) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }

    bool operator==(const Book &b) const {
        return (title == b.title && author == b.author && ISBN == b.ISBN);
    }

    Book& operator=(const Book &b) {
        if (this != &b) {
            title = b.title;
            author = b.author;
            ISBN = b.ISBN;
        }
        return *this;
    }
};

class Library {
    Book books[5];

public:
    static int bookCount;

    void addBook(const Book &b) {
        if (bookCount >= 5) {
            cout << "Library is Full\n";
            return;
        }
        
        for (int i = 0; i < bookCount; i++) {
            if (b == books[i]) {
                cout << "Book Already Exists\n";
                return;
            }
        }
        
        books[bookCount] = b;
        cout << "Book " << b.getTitle() << " Added in Library\n";
        bookCount++;
    }
};

int Library::bookCount = 0;

#endif