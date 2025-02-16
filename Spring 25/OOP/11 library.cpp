#include<iostream>
using namespace std;
typedef struct {
	int bookID;
	string title;
	string author;
	bool isAvalaible;
} book;

void printBooks(int n, book* b) {
	for(int i=0; i<n; i++) {
		if(!b[i].isAvalaible)	continue;
		cout << "\nTitle: " << b[i].title;
		cout << "\nAuthor: " << b[i].author;
		cout << "\nID: " << b[i].bookID;
		cout << "\nAvalaible\n";
	}
}
void addBook(int *n, book* b) {
	int newN;
	cout << "How Many Books You Want To Enter: ";
	cin >> newN;
	for(int i=*n; i<(newN+(*n)); i++) {
		cout << "\nEnter Book " << (i+1) << " Details:-\n";
		cout << "Enter Book ID: ";
		cin >> b[i].bookID;
		cin.ignore();
		cout << "Enter Book Title: ";
		getline(cin,b[i].title);
		cout << "Enter Book Author: ";
		getline(cin,b[i].author);
		b[i].isAvalaible = 1;
	}
	*n += newN;
	printBooks(*n,b);
}
void removeBook(int n, book* b) {
	int id;
	cout << "Enter ID of Book you want to remove: ";
	cin >> id;
	for(int i=0; i<n; i++) {
		if(id==b[i].bookID) {
			b[i].isAvalaible=0;
		}
	}
	printBooks(n,b);
}
void searchBook(int n, book* b) {
	cin.ignore();
	string name;
	cout << "Enter Book of Name You Want To Search: ";
	getline(cin,name);
	for(int i=0; i<n; i++) {
		if(name==b[i].title) {
			cout << "Title: " << b[i].title;
			cout << "\nAuthor: " << b[i].author;
			cout << "\nID: " <<  b[i].bookID;
			cout << "\nAvalaibility: " << b[i].isAvalaible << endl;
			return;
		}
	}
	cout << "No Book Found\n";
}

int main() {
	
	book* b = new book[100];
	int n;
	cout << "How Many Books you want to create : ";
	cin >> n;
	for(int i=0; i<n; i++) {
		cout << "\nEnter Book " << (i+1) << " Details:-\n";
		cout << "Enter Book ID: ";
		cin >> b[i].bookID;
		cin.ignore();
		cout << "Enter Book Title: ";
		getline(cin,b[i].title);
		cout << "Enter Book Author: ";
		getline(cin,b[i].author);
		b[i].isAvalaible = 1;
	}
	cout << "Welcome To Library";
	int op;
	while(1) {
		cout << "\n 1) Add Book\n 2) Remove Book\n 3) Search Book\n 4) Exit\n";
		cout << "Press the corresponding Number to perform that functionality : ";
		cin >> op;
		if(op==1)	addBook(&n,b);
		if(op==2)	removeBook(n,b);
		if(op==3)	searchBook(n,b);
		if(op==4)	break;
	}
	cout << "Thanks for Visiting.";
	delete[] b;
}