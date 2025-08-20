#include <iostream>
using namespace std;

class Media {
	protected:
	string title;
	string publicationDate;
	int uniqueID;
	string publisher;
	
	public:
	static int count;
	Media(string t, string date, int id, string p) {
		title = t;
		publicationDate = date;
		uniqueID = id;
		publisher = p;
		count++;
	}
	
	virtual void displayInfo() const {
		cout << "\nTitle: " << title << "\nPublication Date: " << publicationDate << "\nID: " << uniqueID << "\nPublisher: " << publisher << endl;
	}
	void checkout() {
		cout << "Media Bought\n";
		count--;
	}
	void returnItem(string t) {
		if(t==title) {
			cout << "Media Returned\n";
			count++;
		}
		else cout << "Book Not Found\n";
	}
	void returnItem(int id) {
		if(id==uniqueID) {
			cout << "Media Returned\n";
			count++;
		}
		else cout << "Book Not Found\n";
	}
	
};
int Media::count=0;

class Book : public Media {
	string author;
	long ISBN;
	int numberOfPages;
	
	public:
	Book(string t, string date, int id, string p, string a, long i, int pg) : Media(t,date,id,p) {
		author = a;
		ISBN = i;
		numberOfPages = pg;
	}
	void displayInfo() {
		Media::displayInfo();
		cout << "Author: " << author << "\nISBN: " << ISBN << "\nPages#: " << numberOfPages << endl;
	}
};
class DVD : public Media {
	string director;
	int duration;
	float rating;
	
	public:
		DVD(string t, string date, int id, string p, string d, int dur, float r) : Media(t,date,id,p) {
			director = d;
			duration = dur;
			rating = r;
		} 
	void displayInfo() {
		Media::displayInfo();
		cout << "Director: " << director << "\nDuration: " << duration << " minutes\nRating: " << rating << endl;
	}
};
class CD : public Media {
	string artist;
	int numberOfTracks;
	string genre;
	
	public:
	CD(string t, string date, int id, string p, string a, int track, string g) : Media(t,date,id,p) {
		artist = a;
		numberOfTracks = track;
		genre = g;
	} 
	void displayInfo() {
		Media::displayInfo();
		cout << "Artist: " << artist << "\nTracks#: " << numberOfTracks << "\nGenre: " << genre << endl;
	}
};
class Magzine : public Media {
	int fees;
	
	public:
	Magzine(string t, string date, int id, string p, int f) : Media(t,date,id,p) {
		fees = f;
	}
	void displayInfo() {
		Media::displayInfo();
		cout << "Fees: " << fees << endl;
	}
};

int main() {
	Book b1("Harry Potter","24/10/2024",5850, "US Book Store", "JK Rowling", 123456789, 200);
	DVD d1("Interstellar", "10/2/2012", 1000, "Hollywood", "Christopher Nolan", 180, 9.8);
	CD c1("Jawab e Shikwa", "12/12/2020", 4242, "Coke Stodio", "Amjad Sabri", 10, "Poetry");
	Magzine m1("Daily","17/3/2025",2445,"Express",5000);
	
	b1.displayInfo();
	d1.displayInfo();
	c1.displayInfo();
	m1.displayInfo();
	cout << Media::count << endl;
	m1.checkout();
	m1.returnItem("Harry Potter");
	cout << Media::count << endl;
}