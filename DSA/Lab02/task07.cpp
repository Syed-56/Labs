#include <iostream>
using namespace std;

int main() {

    int numDepartments;
    cout << "Enter Number of Departments: ";
    cin >> numDepartments;

    int **salary = new int*[numDepartments];

    int *numEmployees = new int[numDepartments];
    cout << "Enter Number of Employees in Each Department" << endl;
    for(int i=0; i<numDepartments; i++) {
        cout << i + 1 << ": ";
        cin >> numEmployees[i];
        salary[i] = new int[numEmployees[i]];
    }

    cout << endl << "Enter Salary for Each Employee" << endl;
    for(int i=0; i<numDepartments; i++) {
        cout << "Department " << i + 1 << endl;
        for(int j=0; j<numEmployees[i]; j++) {
            cout << "Employee " << j + 1 << ": ";
            cin >> salary[i][j];
        }
        cout << endl;
    }

    cout << "\nDisplaying Salary Details for Each Department\n";
    float highestAvg = 0;
    for(int i=0; i<numDepartments; i++) {
        int highest = 0;
        cout << "\nDepartment " << i+1 << ": ";
        int total = 0;
        for(int j=0; j<numEmployees[i]; j++) {
            cout << salary[i][j] << " ";
            total += salary[i][j];
            highest = max(salary[i][j], highest);
        }
        cout << "\nHighest: " << highest << endl;
        highestAvg = max(highestAvg, (float)total/numEmployees[i]);
    }

    cout << "\nHighest Department Average: " << highestAvg << endl;

    for(int i=0; i<numDepartments; i++) {
        delete salary[i];
    }
    delete[] salary;
    delete[] numEmployees;
}