#include <iostream>
using namespace std;
class tourGuide {
	public:
	string name;
	string speciality;
	int experience;
	tourGuide(string name, string speciality, int experience) : name(name),speciality(speciality),experience(experience) {
		cout << "Tour Guide Created:-\nName: " << name << "\t Speciality: " << speciality << "\tYears of Experience: " << experience << endl;
	}
	tourGuide(){}
};
class travelAgency {
	public:
	string name;
	tourGuide *tG;
	int tGcapacity;
	int tGcount=0;
	travelAgency(string name) {
		this->name = name;
		cout << "\nEnter Tour Guide Capacity for " << name << " Agency: ";
		cin >> tGcapacity;
		while(tGcapacity > 5) {
			cout << "Tour Guide Limit Exceeded! Enter Valid Capacity: ";
			cin >> tGcapacity;
		}
		tG = new tourGuide[tGcapacity];
	}
	void addTourGuide(const tourGuide &guide) {
		if(tGcount>=tGcapacity) {
			cout << "Tour Guides Limit Full\n";
			return;
		}
		tG[tGcount] = guide;
		cout << "Tour Guide " << tG[tGcount].name << " With Expertise in " << tG[tGcount].speciality << " is now associated with " << name << endl;
		tGcount++;
	}
	void display() const {
		cout << "Agency Name: " << name << endl;
		cout << "Tour Guides:-\n";
		for(int i=0; i<tGcount; i++) {
			cout << i+1 << ") Name: " << tG[i].name << "\t Speciality: " << tG[i].speciality << "\tYears of Experience: " << tG[i].experience << endl;
		}
	}
	~travelAgency() {
		delete[] tG;
	}
};
int main(void) {
	tourGuide guide[5] = { {"Kashan","History",10},{"Sultan","Sports",5},{"Ali","Heritage",7},{"Khizar","Infrastructure",3},{"Mubashir","Religion",2} };
	travelAgency tA("Deluxe Travels");
	for(int i=0; i<tA.tGcapacity; i++) {
		tA.addTourGuide(guide[i]);
	}
	cout << endl;
	tA.display();
return 0;
}