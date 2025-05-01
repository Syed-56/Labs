#include <iostream>
using namespace std;

class Temperature;
class Humidity;

class Temperature {
	float temp;
	public:
	Temperature(float t) : temp(t) {}
	friend float calculateHeatIndex(Temperature t, Humidity h);
};
class Humidity {
	float hum;
	public:
	Humidity(float h) : hum(h)  {}
	friend float calculateHeatIndex(Temperature t, Humidity h);
};

float calculateHeatIndex(Temperature t, Humidity h) {
	return t.temp * h.hum; 
}  

int main() {
	Temperature t(100);
	Humidity h(0.5);
	cout << "Head Index = " << calculateHeatIndex(t,h);
}