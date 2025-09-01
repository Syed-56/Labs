#include <iostream>
using namespace std;

int main() {
    int numStudents;
    cout << "Enter Number of Students: ";
    cin >> numStudents;

    int **marks = new int*[numStudents];

    int *numCourses = new int[numStudents];
    cout << "Enter Number of Courses for Each Student" << endl;
    for(int i=0; i<numStudents; i++) {
        cout << "Student " << i+1 << ": ";
        cin >> numCourses[i];
        marks[i] = new int[numCourses[i]];
    }

    cout << "Enter Marks for Each Student" << endl;
    for(int i=0; i<numStudents; i++) {
        cout << "Student " << i+1 << endl;
        for(int j=0; j<numCourses[i]; j++) {
            cout << "Course " << j+1 << ": ";
            cin >> marks[i][j];
        }
        cout << endl;
    }

    cout << "Average Marks:-\n";
    for(int i=0; i<numStudents; i++) {
        cout << "Student " << i+1 << ": ";
        int total=0;
        for(int j=0; j<numCourses[i]; j++) {
            cout << marks[i][j] << " ";
            total += marks[i][j];
        }
        float average = (float)total/numCourses[i];
        cout << "\nAverage: " << average << endl;
    }

    for(int i = 0; i < numStudents; i++) {
        delete marks[i];
    }
    delete[] numCourses;
    delete[] marks;
}