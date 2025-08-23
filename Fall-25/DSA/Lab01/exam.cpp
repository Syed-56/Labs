#include <iostream>
#include <cstring> // for strcpy, strlen

class Exam {
private:
    char* studentName;
    char* examDate;
    int score;

public:
    // Constructor
    Exam(const char* name, const char* date, int s) {
        studentName = new char[strlen(name) + 1];
        strcpy(studentName, name);

        examDate = new char[strlen(date) + 1];
        strcpy(examDate, date);

        score = s;
    }

    // Destructor
    ~Exam() {
        delete[] studentName;
        delete[] examDate;
    }

    // Setters
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

    // Display method
    void display() const {
        std::cout << "Student Name: " << studentName << std::endl;
        std::cout << "Exam Date: " << examDate << std::endl;
        std::cout << "Score: " << score << std::endl;
    }
};

int main() {
    // Create an Exam instance
    Exam exam1("Alice", "2025-08-20", 95);

    // Shallow copy (default copy constructor is used)
    Exam exam2 = exam1;  // <-- Shallow copy happens here

    std::cout << "Original Exam:" << std::endl;
    exam1.display();

    std::cout << "\nShallow Copy Exam:" << std::endl;
    exam2.display();

    // Modify original
    exam1.setStudentName("Bob");
    std::cout << "\nAfter modifying original:" << std::endl;
    exam1.display();
    exam2.display();  // <-- Notice the issue

    return 0;
}
