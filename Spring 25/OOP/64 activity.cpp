#include <iostream>
using namespace std;

class Activity {
    public:
    virtual void calculateCaloriesBurned() = 0;
    virtual ~Activity() {}
};

class Running : public Activity {
    double distance;
    double time;
    public:
    Running(double d, double t) : distance(d), time(t) {}
    void calculateCaloriesBurned() {
        cout << "Calories Burned = " << distance*time << " k/cal" << endl;
    }
};
class Cycling : public Activity {
    double speed;
    double time;
    public:
    Cycling(double s, double t) : speed(s), time(t) {}
    void calculateCaloriesBurned() {
        cout << "Calories Burned = " << speed*time << " k/cal" << endl;
    }
};

int main() {
    Activity *a1 = new Running(10,60);
    Activity *a2 = new Cycling(50,40);

    a1->calculateCaloriesBurned();
    a2->calculateCaloriesBurned();

    delete a1;
    delete a2;
    return 0;
}