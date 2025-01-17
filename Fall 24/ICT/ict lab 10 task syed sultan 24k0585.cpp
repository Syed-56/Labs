#include<iostream>
using namespace std;
class libraryBook {
	private:
		int avalaibleCopies;
	public:
		string title;
		string author;
		long ISBN;
		void setCopies(int copies) {
			avalaibleCopies = copies;
		}
		int getCopies() {
			return avalaibleCopies;
		}
		void displayDetails() {
			cout << "\n\tBook Details" << endl;
			cout << "-) Author : " << author << endl;
			cout << "-) Title : " << title << endl;
			cout << "-) ISBN # : " << ISBN << endl;
			cout << "-) Avalaible Copies : " << getCopies() << endl;
		}
};
int main() {
	int copies;
	libraryBook book1;
	book1.getCopies();
	cout<<"\tInput Details\n";
	cout << "-) Enter Author Name : ";
	getline(cin, book1.author);
	cout << "-) Enter Book Title : ";
	getline(cin, book1.title);
	cout << "-) Enter ISBN Number : ";
	cin >> book1.ISBN;
	cout << "-) Enter Avalaible Copies : ";
	cin >> copies;
	book1.setCopies(copies);
	book1.displayDetails();
	
}