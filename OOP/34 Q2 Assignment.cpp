#include <iostream>
#include <tuple>
using namespace std;

class Ball {
    int x, y;
public:
    Ball(int initialX=0, int initialY=0) : x(initialX), y(initialY) {}
    int getX() { return x; }
    int getY() { return y; }
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
    tuple<int, int> getPosition() {
        return make_tuple(x, y);
    }
};

class Robot {
public:
    string name;
    int hits = 0;
    Robot(string n) : name(n), hits(0) {}

    void hitball(int &BallX, int &BallY, const string &direction) {
        if (direction == "Up") {
        	if(BallY >= 3) {
        		cout << "Outside\n";
			}
            else	BallY++;
        } else if (direction == "Down") {
        	if(BallY <= -3) {
        		cout << "Outside\n";
			}
            else	BallY--;
        } else if (direction == "Left") {
        	if(BallX >= 3) {
        		cout << "Outside\n";
			}
            else    BallX--;
        } else if (direction == "Right") {
        	if(BallX <= -3) {
        		cout << "Outside\n";
			}
            else    BallX++;  
        } else {
            cout << "Invalid Direction\n";
            return;
        }
        hits++;
    }
};

class Goal {
public:
    int x = 3, y = 3;
    Goal(int GoalX = 3, int GoalY = 3) : x(GoalX), y(GoalY) {}
    bool isGoalReached(int ballX, int ballY) {
        return (x == ballX && y == ballY);
    }
};

class Team {
public:
    string name;
    Robot *player;
    Team(string name, Robot *player) : name(name), player(player) {}
    ~Team() { delete player; }
};

class Game {
public:
    Team teamOne;
    Team teamTwo;
    Ball b;
    Goal g;

    Game(string team1Name, string team2Name, string robot1Name, string robot2Name)
        : teamOne(team1Name, new Robot(robot1Name)), 
          teamTwo(team2Name, new Robot(robot2Name)), 
          b(0, 0), g(3, 3) {}

    void play(Team &team) {
        string direction;
        Robot *robot = team.player;
        int ballX = b.getX();
        int ballY = b.getY();

        cout << team.name << "'s Turn. Robot " << robot->name << endl;

        while (!g.isGoalReached(ballX, ballY)) {
            cout << "Ball Position: (" << ballX << "," << ballY << ")" << endl;
            cout << "Goal Position: (3,3)\n";
            cout << "Hits: " << robot->hits << endl;
            cout << "Directions: 1) Up , 2) Down , 3) Left , 4) Right\nEnter Direction: ";
            cin >> direction;

            robot->hitball(ballX, ballY, direction);
            b.move(ballX - b.getX(), ballY - b.getY()); 

            cout << "Ball moved to: (" << b.getX() << "," << b.getY() << ")" << "\n\n";
        }

        cout << team.name << " Reached the goal\nHits Taken: " << robot->hits << endl;
    }

    void declareWinner() const {
        int hitsTeam1 = teamOne.player->hits;
        int hitsTeam2 = teamTwo.player->hits;
        cout << "------- Game Results-----\n";
        cout << teamOne.name << ": " << hitsTeam1 << " hits\n";
        cout << teamTwo.name << ": " << hitsTeam2 << " hits\n";

        if (hitsTeam1 < hitsTeam2) {
            cout << "Winner: " << teamOne.name << "\n";
        } else if (hitsTeam2 < hitsTeam1) {
            cout << "Winner: " << teamTwo.name << "\n";
        } else {
            cout << "Result: It's a tie!\n";
        }
    }

    void startGame() {
        cout << "\t\t-----Football Game Simulation-----\n";
        cout << "\nKick Off Position: (0,0)\n";
        cout << "Goal Position: (3,3)\n";
        play(teamOne);
        b = Ball(0, 0);  
        play(teamTwo);
        declareWinner();
    }
};

int main() {
    Game G("Barcelona", "Real Madrid", "Messi", "Ronaldo");
    G.startGame();
    return 0;
}