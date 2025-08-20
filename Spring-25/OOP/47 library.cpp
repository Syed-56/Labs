#include <iostream>
using namespace std;
class Library;
class Book;

class Library {
	Book **books;
	static int numBooks;
	public:
		Library() {
			books = new Book*[10];
		}
	void addBook(Book& b);
	void displayAllBooks() const;
	Book* findBook(int id);
	static int getNumBooks() {
		return numBooks;
	}
	void borrowBook(Book &b);
	~Library();
};
int Library::numBooks=0;

class Book {
	static int counter;
	const int id;
	string title;
	string author;
	float price;
	bool status;
	
	public:
		Book() : id(25+counter) {counter++;}
	int getID()		   const {return id;}
	string getTitle()  const {return title;}
	string getAuthor() const {return author;}
	float getPrice()   const {return price;}
	bool getStatus()   const {return status;}
	void setStatus(bool s) {status = s;}
	
	void setBookdetails(string t, string a, float p);
	void displayBook() const;
};
int Book::counter=0;

void Book::setBookdetails(string t, string a, float p) {
		title = t;
		author = a;
		price = p;
		status=true;
	}
void Book::displayBook() const {
	if(!this)	return;
		cout << "\nTitle: " << title << "\nAuthor: " << author << "\nID: " << id << "\nPrice: " << price << "\nAvalaibility Status: ";
		if(status)	cout << "Avalaible";
		else	cout << "Not Avalaible";
		cout << "\n\n"; 
	}
	
void Library::displayAllBooks() const {
	for(int i=0; i<numBooks; i++) {
		cout << "Book " << i+1 << endl;
		books[i]->displayBook();
	}
}
void Library::addBook(Book& b) {
	if(numBooks>=10) {
		cout << "Not Enough Capacity\n";
		return;
	}
	books[numBooks] = new Book(b);
	numBooks++;
}
void Library::borrowBook(Book& b) {
		if(b.getStatus()) {
			cout << "Book " << b.getTitle() << " Borrowed\n";
			b.setStatus(0);
		}
		else	cout << "Book not avalaible\n";
	}
Book* Library::findBook(int id) {
	for(int i=0; i<numBooks; i++) {
		if(id==books[i]->getID()) {
			return books[i];
		}
	}
	cout << "Book Not Found\n";
	return nullptr;
}
Library::~Library() {
	for(int i=0; i<numBooks; i++)	delete books[i];
	delete[] books;
}

int main() {
	Library lib;
	Book b1,b2,b3,b4;
	b1.setBookdetails("Harry Potter","Syed Sultan",1500);
	b2.setBookdetails("Atomic Habits","Syed Khizer",1600);
	b3.setBookdetails("Rich Dad Poor Dad","Syed Mubashir",2000);
	lib.addBook(b1);
	lib.addBook(b2);
	lib.addBook(b3);
	lib.borrowBook(b3);
	lib.displayAllBooks();
	lib.borrowBook(b4);
	lib.findBook(b2.getID())->displayBook();
	cout << "Book in Library: " << lib.getNumBooks();
return 0;
}