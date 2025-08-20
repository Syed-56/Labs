#include <iostream>
using namespace std;

class Vehicle {
    protected:
    string model;
    double rate;

    public:
    Vehicle(string m, double r) : model(m), rate(r) {}
    virtual float getDailyRate() = 0;
    virtual void displayDetails() = 0;
};

class Car : public Vehicle {
    public:
    Car(string m, double r) : Vehicle(m,r) {}
    float getDailyRate() {
        return rate/30;
    }
    void displayDetails() {
        cout << "\nCar:-\nModel: " << model << "\tRate: " << rate;
    }
};
class Bike : public Vehicle {
    public:
    Bike(string m, double r) : Vehicle(m,r) {}
    float getDailyRate() override {
        return rate/30;
    }
    void displayDetails() override {
        cout << "\nBike:-\nModel: " << model << "\tRate: " << rate;
    }
};

int main() {
    Vehicle *v1 = new Car("Toyota Corolla", 25000);
    Vehicle *v2 = new Bike("Kawasaki ZX10R", 10000);

    v1->displayDetails();
    cout << "\nDaily Rate: " << v1->getDailyRate();
    v2->displayDetails();
    cout << "\nDaily Rate: " << v2->getDailyRate();

    delete v1;
    delete v2;

    return 0;
}