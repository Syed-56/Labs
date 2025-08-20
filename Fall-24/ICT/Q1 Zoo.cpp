#include<iostream>
#include<string>
using namespace std;
class Animal{
	private:
		string name;
		int age;
	public:
		Animal(string n = "", int a = 0) : name(n), age(a) {}
		string getName() {
			return name;
		}
		void setName(string n) {
			name = n;
		}
		int getAge() {
			return age;
		}
		void setAge(int a) {
			if(a >= 0)	age = a;
			else	cout << "invalid age" << endl;
		}
		void displayInfo() {
			cout << "Animal Name : " << name << endl;
			cout << "Animal Age : " << age << endl;
		}
};
class Mammal : public Animal{
	public:
		void feedBaby() {
			cout << "Feeding Baby Mammal" << endl;
		}
};
class Bird : public Animal{
	public:
		void layEgg() {
			cout << "Laying Egg" << endl;
		}
};
class Reptile : public Animal{
	public:
		void shedSkin() {
			cout << "Shedding Skin" << endl;
		}
};
int main() {
	Mammal m1;
	m1.setName("Lion");
	m1.setAge(15);
	m1.displayInfo();
	m1.feedBaby();
	cout << "\n";
	Bird b1;
	b1.setName("Eagle");
	b1.setAge(3);
	b1.displayInfo();
	b1.layEgg();
	cout << "\n";
	Reptile r1;
	r1.setName("Snake");
	r1.setAge(5);
	r1.displayInfo();
	r1.shedSkin();
	return 0;
}