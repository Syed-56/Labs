#include <iostream>
using namespace std;

void EnterExpenses(int* expenses, int n) {
    cout << "Enter monthly expenses (in USD$)\n";
    for (int i=0; i<n; i++) {
        cout << "Month " << i+1 << ": ";
        cin >> expenses[i];
    }
    cout << endl;
}

int* AddMoreMonths(int* expenses, int& n, int months) {
    int* temp = expenses;
    expenses = new int[n+months];

    for (int i=0; i<n; i++) {
        expenses[i] = temp[i];
    }

    cout << "Enter monthly expenses for new months added (" << n+1 << " to " << n+months << ")" << endl;

    for (int i=n; i < n+months; i++) {
        cout << "Month " << i+1 << ": ";
        cin >> expenses[i];
    }
    cout << endl;

    delete[] temp;
    n += months;  
    return expenses;
}

void DisplayExpenses(int* expenses, int n) {
    int total=0;
    cout << "Displaying expenses:" << endl;
    for (int i=0; i<n; i++) {
        cout << "Month " << i+1 << ": " << expenses[i] << "$\n";
        total += expenses[i];
    }
    cout << "\nTotal: " << total << "$\n" << "Average: " << (float)total/n << endl;
}

int main() {
    int n=3; 
    int* expenses = new int[n];

    EnterExpenses(expenses, n);
    DisplayExpenses(expenses, n);

    int months;
    cout << "How Many Months You want to Add: ";
    cin >> months;
    expenses = AddMoreMonths(expenses, n, months);
    DisplayExpenses(expenses, n);

    delete[] expenses;
}
