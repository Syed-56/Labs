#include <iostream>
using namespace std;

#define MAX 8

void printSolution(int board[MAX][MAX], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(int board[MAX][MAX], int row, int col, int N) {
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

void solveNQueens(int board[MAX][MAX], int row, int N) {
    if (row == N) { 
        printSolution(board, N);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1; 
            solveNQueens(board, row + 1, N);
            board[row][col] = 0; 
        }
    }
}

int main() {
    int N;
    cout << "Enter N for N-Queens: ";
    cin >> N;
    if(N > 8) {
        cout << "Chessboard too large\n";
        return 1;
    }

    int board[MAX][MAX] = {0}; 
    cout << "All possible solutions for " << N << "-Queens:\n\n";
    solveNQueens(board, 0, N);
}
