#include <iostream>
#include <cstring> 
using namespace std;

class Exam {
private:
    char* studentName;
    char* examDate;
    int score;

public:
    Exam(const char* name, const char* date, int s) {
        studentName = new char[strlen(name) + 1];
        strcpy(studentName, name);

        examDate = new char[strlen(date) + 1];
        strcpy(examDate, date);

        score = s;
    }

    ~Exam() {
        delete[] studentName;
        delete[] examDate;
    }

    void setStudentName(const char* name) {
        delete[] studentName;
        studentName = new char[strlen(name) + 1];
        strcpy(studentName, name);
    }

    void setExamDate(const char* date) {
        delete[] examDate;
        examDate = new char[strlen(date) + 1];
        strcpy(examDate, date);
    }

    void setScore(int s) {
        score = s;
    }

    void display() const {
        cout << "Student Name: " << studentName << endl;
        cout << "Exam Date: " << examDate << endl;
        cout << "Score: " << score << endl;
    }
};

int main() {
    Exam exam1("Alice", "2025-08-20", 95);
    Exam exam2 = exam1;  

    cout << "Original Exam:" << endl;
    exam1.display();

    cout << "\nShallow Copy Exam:" << endl;
    exam2.display();

    exam1.setStudentName("Bob");
    cout << "\nAfter modifying original:" << endl;
    exam1.display();
    exam2.display();  

    return 0;
}
