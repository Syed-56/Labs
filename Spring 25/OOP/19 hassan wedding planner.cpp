#include <iostream>
#include <string>
using namespace std;

class Planner {
	public:
    string month[30];        
    bool busy[30] = {0};      
    string taskCategory[30];  

    void addTask() {
        int day;
        cout << "Enter Day to add task (1-30): ";
        cin >> day;
        if (day<1 || day>30) {
            cout << "Invalid day! Please enter a day between 1 and 30.\n";
            return;
        }
        while (busy[day-1]) {
            cout << "Day already occupied. Enter another day: ";
            cin >> day;
        }
        cin.ignore(); 
        string category;
        cout << "Enter Task Category (Wedding/Event/Other): ";
        getline(cin, category);
        while (category != "Wedding" && category != "Event" && category != "Other") {
            cout << "Invalid category! Enter a valid category (Wedding/Event/Other): ";
            getline(cin, category);
        }
        taskCategory[day-1] = category;
        cout << "Enter Task: ";
        getline(cin, month[day - 1]);
        busy[day-1] = true;
        cout << "Task added for day " << day << ".\n";
    }
    void removeTask() {
        int day;
        cout << "Enter Day to remove task (1-30): ";
        cin >> day;

        if (day<1 || day>30) {
            cout << "Invalid day! Please enter a day between 1 and 30.\n";
            return;
        }

        busy[day - 1] = false;
        month[day - 1] = "free";
        taskCategory[day - 1] = "";
        cout << "Task removed for day " << day << ".\n";
    }
    void display() {
        int choice;
        cout << "What do you want to see?\n1) Free Days\n2) Busy Days\nEnter your choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Free Days:\n";
            for (int i = 0; i < 30; i++) {
                if (month[i] == "free") {
                    cout << "Day " << i + 1 << " : " << month[i] << endl;
                }
            }
        } else if (choice == 2) {
            cin.ignore();
            string category;
            cout << "1) Wedding\n2) Event\n3) Other\n4) All\nWhich task category do you want to see? ";
            getline(cin, category);

            cout << "Busy Days:\n";
            for (int i=0; i<30; i++) {
                if (month[i] != "free" && (category == "All" || taskCategory[i] == category)) {
                    cout << "Day " << i + 1 << " : " << month[i] << " (Category: " << taskCategory[i] << ")\n";
                }
            }
        } else 	cout << "Invalid choice!\n";
    }
};

int main() {
    Planner hassan;
    int opt;
    
	for (int i=0; i<30; i++) {
            hassan.month[i] = "free";
        }
    while (true) {
        cout << "\n1) Add Task\n2) Remove Task\n3) Display Tasks\n4) Exit\nWhat do you want to do? ";
        cin >> opt;
        switch (opt) {
            case 1:
                hassan.addTask();
                break;
            case 2:
                hassan.removeTask();
                break;
            case 3:
                hassan.display();
                break;
            case 4:
                cout << "Bye Hassan!\n";
                return 0;
            default:
                cout << "Invalid option! Please try again.\n";
                break;
        }
    }
return 0;
}