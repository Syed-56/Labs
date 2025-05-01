#include <iostream>
using namespace std;

class Currency {
	int val;
	public:
	Currency(int v) : val(v) {}
	
	friend ostream& operator<< (ostream& out, const Currency& c) {
		out << c.val;
		return out;
	}
	
	Currency operator-() {
		return Currency(-val);
	}
	Currency operator+(const Currency& c) {
		return Currency(val+c.val);
	}
	Currency operator-(const Currency& c) {
		return Currency(val-c.val);
	}
	void operator+=(const Currency& c) {
		val += c.val;
	}
	void operator-=(const Currency& c) {
		val -= c.val;
	}
};

int main() {
	Currency rupee(100);
	int money;
	cout << "Avalaible Money:  " << rupee << " Rps" << endl;
	while(1) {
		int opt;
		cout << "1) Spend Money\t 2) Earn Money\n What you want to do: ";
		cin >> opt;
		if(opt==1) {
			cout << "How Much Money you want to Spend: ";
			cin >> money;
			Currency tempMoney(money);
			rupee -= tempMoney;		//similarly rupee = rupee - tempMoney can be used
			cout << "Money Gained: " << -tempMoney << endl;
			cout << "Remaining Money:  " << rupee << " Rps" << endl;
		}
		else if(opt==2) {
			cout << "How Much Money you want to Earn: ";
			cin >> money;
			Currency tempMoney(money);
			rupee = rupee + tempMoney;	//similarly rupee += tempMoney can be used
			cout << "Money Gained: " << tempMoney << endl;
			cout << "Remaining Money:  " << rupee << " Rps" << endl;
		}
		else {
			cout << "\nExiting...\n";
			break;
		}
	}

return 0;
}