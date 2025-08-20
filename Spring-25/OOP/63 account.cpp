#include <iostream>
using namespace std;

class PaymentMethod {
    public:
    virtual void processPayment(double balance) = 0;

    virtual ~PaymentMethod() {}
};

class CreditCard : public PaymentMethod {
    string cardNumber; 
    public:
    CreditCard(string c) : cardNumber(c) {}
    void processPayment(double balance) override {
        cout << "Processing Payment of Amount " << balance << " Rs With Card No. = " << cardNumber << endl;
    }
};
class DigitalWallet : public PaymentMethod {
    double Balance; 
    public:
    DigitalWallet(double b) : Balance(b) {}
    void processPayment(double balance) override {
        cout << "Processing Payment of Digital Wallet: Old Balance: " << balance << "\tNew Balance: " << balance + Balance << endl;
    }
};

int main() {
    PaymentMethod *p1 = new CreditCard("1234");
    PaymentMethod *p2 = new DigitalWallet(5000);

    p1->processPayment(1500);
    p2->processPayment(2500);

    delete p1;
    delete p2;
    return 0;
}