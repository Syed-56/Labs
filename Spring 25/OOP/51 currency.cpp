#include <iostream>
using namespace std;

class Currency { // Base currency is USD
protected:
    float amount;
    string currencyCode;
    char currencySymbol;
    float exchangeRate;

public:
    float getAmount() { return amount; }
    float getRate() { return exchangeRate; }

    Currency(float a, string cC, char cS, float eR = 1.0)
        : amount(a), currencyCode(cC), currencySymbol(cS), exchangeRate(eR) {}

    virtual float convertToBase() {
        return amount * exchangeRate;
    }

    float convertToCurrency(Currency c) {
        return (amount * exchangeRate) / c.exchangeRate;
    }

    virtual void displayCurrency() const {
        cout << "\nAmount: " << amount 
             << "\nCurrency Code: " << currencyCode 
             << "\nCurrency Symbol: " << currencySymbol
             << "\nExchange Rate: " << exchangeRate;
    }
};

class Dollar : public Currency {
public:
    Dollar(float a) : Currency(a, "USD", '$', 1.0) {}

    float convertToBase() override {
        return amount; 
    }

    void displayCurrency() const override {
        Currency::displayCurrency();
        cout << "\nCountry: USA";
    }
};

class Euro : public Currency {
public:
    Euro(float a, float eR = 2.7) : Currency(a, "EUR", 'E', eR) {}

    float convertToBase() override {
        return amount * exchangeRate;
    }

    void displayCurrency() const override {
        Currency::displayCurrency();
        cout << "\nCountry: Europe";
    }
};

class Rupee : public Currency {
public:
    Rupee(float a, float eR = 0.100) : Currency(a, "PKR", 'R', eR) {}

    float convertToBase() override {
        return amount * exchangeRate;
    }

    void displayCurrency() const override {
        Currency::displayCurrency();
        cout << "\nCountry: Pakistan";
    }
};

int main() {
    Dollar d(2);
    Euro e(3);
    Rupee r(100);

    d.displayCurrency();
    cout << "\nConverted to Base (USD): " << d.convertToBase() << "\n";

    e.displayCurrency();
    cout << "\nConverted to Base (USD): " << e.convertToBase() << "\n";

    r.displayCurrency();
    cout << "\nConverted to Base (USD): " << r.convertToBase() << "\n";

    return 0;
}