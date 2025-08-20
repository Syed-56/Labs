#include <iostream>
using namespace std;
static int counter=100;

class Book {
public:
    string title;
    float price;
    int stock;
    int id;
    
    Book(string title, float price, int stock) : title(title), price(price), stock(stock) {
        id = ++counter;
    }
    
    void calculatePrice(int quant) {
    	 if (quant > stock) {
            cout << "Not enough stock available.\n";
            return;
        }
        float totalPrice = quant * price;
        stock -= quant;
        if (quant > 10) totalPrice *= 0.90;
        if (quant > 5) totalPrice *= 0.95;
        cout << "You purchased " << quant << " copies of " << title << " at an amount of USD " << totalPrice << endl;
	}
	void display() {
		cout << "Book Details\n Name: " << title << "\n Price: " << price << "\n Stock Left: " << stock << "\n ID: " << id << endl;
	}
};
int main() {
	Book b("Atomic Habits", 100.5, 30);
	int quant;
	cout << "How many books you want to purchase: ";
	cin >> quant;
	b.calculatePrice(quant);
	cout << "Do you want to see book details\n 1) Yes\t 2) No\t Enter Option: ";
	cin >> quant;
	if(quant==1)	b.display();
	else	cout << "ok\n";
	if(b.stock=0)	b.stock=30;
return 0;
}