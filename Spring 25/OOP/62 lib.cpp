#include "Book.h"

int main() {
    Library lib;
    Book b1("Harry Potter", "Syed Sultan", "0123421");
    Book b2("Atomic Habits", "Talha Shahid", "532322310");

    lib.addBook(b1);
    lib.addBook(b2);
    lib.removeBook(b1);
    lib.searchBook(b1);
    lib.searchBook(b2);

    return 0;
}
