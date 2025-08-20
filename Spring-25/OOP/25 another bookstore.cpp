#include <iostream>
using namespace std;

class Book {
public:
    string title;
    float price;
    int stock;

	Book() {
		title = "Unknown";
		price = 0.0;
		stock = 30;
	}
    Book(string title, float price, int stock) {
        this->title = title;
        this->price = price;
        this->stock = stock;
    }
    Book(const Book& b) {
    	title = b.title;
    	price = b.price;
    	stock = b.stock;
	}
	void updateBookDetails() {
		string title;
		float price;
		cin.ignore();
		cout << "Enter New Title: ";
		getline(cin, title);
		cout << "Enter Price: ";
		cin >> price;
		this->title = title;
		this->price = price;
	}
    void purchase(int quant) {
        if (quant > stock) {
            cout << "Not enough stock available.\n";
            return;
        }
        float totalPrice = applyDiscount(quant) * quant;
        stock -= quant;
        cout << "You purchased " << quant << " copies of " << title << " at an amount of USD " << totalPrice << endl;
    }
    float applyDiscount(int quant) {
        if (quant > 10) return price * 0.90;
        if (quant > 5) return price * 0.95;
        return price;
    }
    void restock() {
    	stock = 30;
    	cout << "Book" << title << "Restocked!\n";
	}

	 ~Book() {
        cout << "Destructor called for: " << title << endl;
    }
};

int main() {
    Book b("Harry Potter", 15.5, 30);
    int opt, quant;

    while (true) {
        cout << "1) Update Book Details\n2) Purchase Book\n3) Restock book\n4) Create a Copy of Book \n5) Exit";
        cout << "\n Enter Option: ";
        cin >> opt;
        if (opt==1)	{
        	b.updateBookDetails();
		}
        else if (opt==2) {
        	cout << "How many books do you want to purchase? ";
	        cin >> quant;
	        b.purchase(quant);
		}
		else if (opt==3) {
			if (b.stock <= 5)	b.restock();
			else	cout << "Not Needed\n";
		}
		else if (opt==4) {
			Book b1(b);
			cout << "Book 1\n" << b.title << " Price: " << b.price << " Stock: " << b.stock << "\n";
			cout << "Book 2\n" << b1.title << " Price: " << b1.price << " Stock: " << b1.stock << "\n";
		}
        else if (opt == 5) break;
        else	cout << "Enter Valid Option\n";
    }
}