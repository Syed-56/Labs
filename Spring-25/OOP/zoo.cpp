#include<iostream>
using namespace std;
class Animal {
	string name;
	int age;
	
	public:
	void setName(string n) {
		name = n;
	}
	void setAge(int a) {
		age = a;
	}
	string getName() {
		return name;
	}
	int getAge() {
		return age;
	}
	
	void displayInfo() {
		cout<<"Name = "<<getName()<<"\tAge = "<<getAge();
	}
};
class Mammal : public Animal {
	public:
	void feedBaby() {
		cout<<"\t\tFeeding Baby Mammal\n";
	}
};
class Bird : public Animal {
	public:
	void LayEgg() {
		cout<<"\t\tLaying an Egg\n";
	}
};
class Reptile : public Animal {
	public:
	void ShedSkin() {
		cout<<"\t\tShedding Skin\n";
	}
};
int main() {
	Mammal m;
	m.setName("Dog");
	m.setAge(5);
	m.displayInfo();
	m.feedBaby();
	Bird b;
	b.setName("Crow");
	b.setAge(3);
	b.displayInfo();
	b.LayEgg();
	Reptile r;
	r.setName("Snake");
	r.setAge(9);
	r.displayInfo();
	r.ShedSkin();
}