#include <iostream>
#include <string>
using namespace std;

class TeaMug {
public:
    string brand;
    string color;
    int capacity;          
    int currentFillLevel; 

    void sipTea() {
        if (currentFillLevel > 0) {
            currentFillLevel -= 10; 
            cout << "Fatima sipped tea from her " << color << " " << brand << " mug.\n";
        } else {
            cout << "The " << color << " " << brand << " mug is empty. Please refill!" << endl;
        }
    }
    void refillTea() {
        currentFillLevel = capacity;
        cout << color << " " << brand << " mug has been refilled to " << capacity << "ml." << endl;
    }
    bool isEmpty()  {
        return currentFillLevel <= 0;
    }
};

int main() {
    int n;
    cout << "How many tea mugs does Fatima have? ";
    cin >> n;

    TeaMug Fatima[n];
    for (int i = 0; i < n; i++) {
        cin.ignore();
        cout << "\nInput for Mug " << i + 1 << endl;
        cout << "Enter Brand: ";
        getline(cin, Fatima[i].brand);
        cout << "Enter Color: ";
        getline(cin, Fatima[i].color);
        cout << "Enter Capacity (in ml): ";
        cin >> Fatima[i].capacity;
        cout << "Enter Current Fill Level (in ml): ";
        cin >> Fatima[i].currentFillLevel;
        while(Fatima[i].currentFillLevel > Fatima[i].capacity) {
        	cout << "Fill Levl Limit Exceeded. Enter Appropriate: ";
        	cin >> Fatima[i].currentFillLevel;
		}
    }

    int opt = 1;
    while (opt == 1) {
        cout << "\nFatima is drinking tea:-\n";
        for (int i = 0; i < n; i++) {
            cout << "Fatima is drinking from her " << Fatima[i].color << " " << Fatima[i].brand << " mug.\n";
            Fatima[i].sipTea();
            if (Fatima[i].isEmpty()) {
                string ref;
                cout << "The " << Fatima[i].color << " " << Fatima[i].brand << " mug is empty. Would you like to refill it? (yes/no): ";
                cin >> ref;
                if (ref == "yes" || ref == "Yes") {
                    Fatima[i].refillTea();
                }
            }
        }

        cout << "Do you want to check the tea level in Fatima's mugs? (yes/no): ";
        string check;
        cin >> check;
        if (check == "yes" || check == "Yes") {
            for (int i = 0; i < n; i++) {
                cout << "Tea level in " << Fatima[i].color << " " << Fatima[i].brand << " mug = " << Fatima[i].currentFillLevel << "ml" << endl;
            }
        }

        cout << "It's been an exhausting day and nothing would beat a fresh cup of tea. Would Fatima like to drink more tea?\n 1) Yes, 2) No\t Enter Corresponding Number: ";
        cin >> opt;
    }

    return 0;
}