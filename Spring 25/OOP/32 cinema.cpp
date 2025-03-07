#include <iostream>
using namespace std;
class Movie {
	public:
	string title;
	string director;
	float hours;
	Movie () {}
	Movie(string title, string director, float hours) : title(title),director(director),hours(hours) {
		cout << "Movie Creation\n Title: " << title << "\t Director: " << director << "\tHours: " << hours << endl;
	}
};
class Cinema {
	public:
	string name;
	Movie *m = new Movie[3];
	void display() const {
			cout << "\nCinema Name: " << name;
		cout << "\nMovies Premiering: ";
		for(int i=0; i<3; i++)	cout << m[i].title << "  ";
		cout << endl;
	}
	~Cinema() {
		delete[] m;
	}
};
int main(void) {
	Cinema c;
	c.name = "Nueplex";
	c.m[0] = Movie("Maula Jatt","Noman Ijaz",2.5);
	c.m[1] = Movie("Interstellar","Christophar Nolan",2.0);
	c.m[2] = Movie("Oppenheimer","Thomas Shelby",3.5);
	c.display();
}