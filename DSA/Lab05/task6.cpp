#include <iostream>
using namespace std;
#define N 5   
void printSolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }
}

bool isSafe(int maze[N][N], int x, int y, int sol[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && sol[x][y] == 0);     
}

bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]) {
    if (x == N - 1 && y == N - 1 && maze[x][y] == 1) {
        sol[x][y] = 1;
        return true;
    }

    if (isSafe(maze, x, y, sol)) {
        sol[x][y] = 1;  

        // Move Down
        if (solveMazeUtil(maze, x + 1, y, sol)) return true;
        // Move Right
        if (solveMazeUtil(maze, x, y + 1, sol)) return true;
        // Move Up
        if (solveMazeUtil(maze, x - 1, y, sol)) return true;
        // Move Left
        if (solveMazeUtil(maze, x, y - 1, sol)) return true;

        sol[x][y] = 0;
        return false;
    }
    return false;
}

bool solveMaze(int maze[N][N]) {
    int sol[N][N] = {0};  

    if (!solveMazeUtil(maze, 0, 0, sol)) {
        cout << "No solution exists" << endl;
        return false;
    }

    cout << "Solution Path (1 = path taken):" << endl;
    printSolution(sol);
    return true;
}

int main() {
    int maze[N][N] = {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 1}
    };

    solveMaze(maze);
}
