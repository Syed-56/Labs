#include <iostream>
using namespace std;

int main() {
    int n, m;
    cout << "Enter Number of Days: ";
    cin >> n;
    cout << "Enter Number of Readings/Day: ";
    cin >> m;

    float** temps = new float*[n];
    for (int i=0; i<n; i++) {
        temps[i] = new float[m];
    }

    cout << endl << "Enter Temperature Readings" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Day " << i + 1 << ":" << endl;
        for (int j = 0; j < m; j++) {
            cout << "  Reading " << j + 1 << ": ";
            cin >> temps[i][j];
        }
    }

    float* avg = new float[n];
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < m; j++) {
            sum += temps[i][j];
        }
        avg[i] = sum / m;
    }

    int hottestDay = 0, coldestDay = 0;
    for (int i=1; i<n; i++) {
        if (avg[i] > avg[hottestDay]) hottestDay = i;
        if (avg[i] < avg[coldestDay]) coldestDay = i;
    }

    cout << "\nDaily Average Temperatures\n";
    for (int i=0; i<n; i++) {
        cout << "Day " << i+1 << ": " << avg[i] << endl;
    }

    cout << endl << "Hottest Day: Day " << hottestDay + 1 << " (Average = " << avg[hottestDay] << ")" << endl;
    cout << "Coldest Day: Day " << coldestDay + 1 << " (Average = " << avg[coldestDay] << ")" << endl;

    for (int i=0; i<n; i++) {
        delete temps[i];
    }
    delete[] temps;
    delete[] avg;
}