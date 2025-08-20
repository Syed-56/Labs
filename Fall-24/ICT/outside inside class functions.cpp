#include<iostream>
using namespace std;
class car{
	private:
		int car_number;
		char car_model[10];
	public:
		void getData();
		void showData();
};
void car::getData() {
		cout << "Enter Car Number = ";
		cin >> car_number;
		cout << "Enter Car Model = ";
		cin >> car_model;
	}
void car::showData() {
	cout << "Car Number = " << car_number <<endl;
	cout << "Car Model = "  << car_model <<endl;
}
int main() {
	car c1, c2;
	c1.getData();
	c1.showData();
	c2.getData();
	c2.showData();
}