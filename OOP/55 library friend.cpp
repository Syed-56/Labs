#include <iostream>
using namespace std;

class Librarian;

class Book {
	string title;
	float price;
	friend class Librarian;
	
	public:
	Book(string t, float p) : title(t) , price(p) {}
};
class Librarian {
	string name;
	public:
	Librarian(string n) : name(n) {}
	
	void viewBookDetails(Book b) const {
		cout << "\nBook Title: " << b.title << "\nBook Price: " << b.price;
		cout << endl;
	}
	void applyDiscountPercent(Book &b, float percent) {
		float newPrice = b.price * (percent/100);
		cout << "Book Price changed from " << b.price << " to " << newPrice;
		b.price = newPrice;
	}
};

int main() {
	Book b("Harry Potter",100.5);
	Librarian l("Sultan");
	l.viewBookDetails(b);
	l.applyDiscountPercent(b,50);
	cout << "\nUpdated Details:-\n";
	l.viewBookDetails(b);
return 0;
}