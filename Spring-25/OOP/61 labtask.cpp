#include <iostream>
using namespace std;

class SmartDevice {
    public:
    virtual void turnOn()=0;
    virtual void turnOff()=0;
    virtual bool getStatus()=0;

    virtual ~SmartDevice() {};
};

class LightBulb : public SmartDevice {
    bool isOn;
    int brightness;
    public:
    LightBulb(bool on, int b) : isOn(on), brightness(b) {}
    void turnOn () override {
    	cout << "Light Bulb Turned On!!\n";
        isOn = true;
    }
    void turnOff() override {
    	cout << "Light Bulb Turned Off!!\n";
        isOn = false;
    }
    bool getStatus() override {
        return isOn;
    }
};
class Thermostat : public SmartDevice {
    bool isOn;
    double temperature;
    public:
    Thermostat(bool on, int t) : isOn(on), temperature(t) {}
    void turnOn () override {
    	cout << "Thermostat Turned On!!\n";
        isOn = true;
    }
    void turnOff() override {
    	cout << "Thermostat Turned Off!!\n";
        isOn = false;
    }
    bool getStatus() override {
        return isOn;
    }
};

int main() {
    SmartDevice *s1 = new LightBulb(true,79);
    SmartDevice *s2 = new Thermostat(false,55);

    s1->turnOff();
    s2->turnOn();
    cout << "\nCurrent Status of LightBulb: " << ((s1->getStatus()) ? "On" : "Off");
    cout << "\nCurrent Status of Thermostats: " << ((s2->getStatus()) ? "On" : "Off");

    delete s1;
    delete s2;
    
    return 0;
}