import math

class TicTacToe:
    def __init__(self):
        self.board = [[" " for _ in range(3)] for _ in range(3)]
        self.nodes_explored = 0
        self.pruned = 0
        self.max_depth = 0

    def print_board(self):
        for row in self.board:
            print("|".join(row))
            print("-" * 5)

    def check_winner(self):
        b = self.board

        for i in range(3):
            if b[i][0] == b[i][1] == b[i][2] != " ":
                return b[i][0]
            if b[0][i] == b[1][i] == b[2][i] != " ":
                return b[0][i]

        if b[0][0] == b[1][1] == b[2][2] != " ":
            return b[0][0]
        if b[0][2] == b[1][1] == b[2][0] != " ":
            return b[0][2]

        return None

    def is_full(self):
        return all(cell != " " for row in self.board for cell in row)

    def minimax(self, depth, is_max, alpha, beta):
        self.nodes_explored += 1
        self.max_depth = max(self.max_depth, depth)

        winner = self.check_winner()

        if winner == "X":
            return 10 - depth
        elif winner == "O":
            return depth - 10
        elif self.is_full():
            return 0

        if is_max: 
            best = -math.inf

            for i in range(3):
                for j in range(3):
                    if self.board[i][j] == " ":
                        self.board[i][j] = "X"
                        val = self.minimax(depth + 1, False, alpha, beta)
                        self.board[i][j] = " "

                        best = max(best, val)
                        alpha = max(alpha, best)

                        if beta <= alpha:
                            self.pruned += 1
                            return best

            return best

        else: 
            best = math.inf

            for i in range(3):
                for j in range(3):
                    if self.board[i][j] == " ":
                        self.board[i][j] = "O"
                        val = self.minimax(depth + 1, True, alpha, beta)
                        self.board[i][j] = " "

                        best = min(best, val)
                        beta = min(beta, best)

                        if beta <= alpha:
                            self.pruned += 1
                            return best

            return best

    def best_move(self):
        best_val = -math.inf
        move = (-1, -1)

        self.nodes_explored = 0
        self.pruned = 0
        self.max_depth = 0

        for i in range(3):
            for j in range(3):
                if self.board[i][j] == " ":
                    self.board[i][j] = "X"
                    move_val = self.minimax(0, False, -math.inf, math.inf)
                    self.board[i][j] = " "

                    if move_val > best_val:
                        best_val = move_val
                        move = (i, j)

        return move

    def play(self):
        print("Tic-Tac-Toe: Human(O) vs AI(X)\n")

        while True:
            self.print_board()

            try:
                x, y = map(int, input("Enter row and column (0-2): ").split())
            except:
                print("Invalid input!")
                continue

            if self.board[x][y] != " ":
                print("Cell already occupied!")
                continue

            self.board[x][y] = "O"

            if self.check_winner() == "O":
                self.print_board()
                print("You win!")
                break

            if self.is_full():
                self.print_board()
                print("Draw!")
                break

            move = self.best_move()
            self.board[move[0]][move[1]] = "X"

            print("\nAI played:", move)
            print("Depth explored:", self.max_depth)
            print("Nodes explored:", self.nodes_explored)
            print("Branches pruned:", self.pruned, "\n")

            if self.check_winner() == "X":
                self.print_board()
                print("AI wins!")
                break

            if self.is_full():
                self.print_board()
                print("Draw!")
                break


game = TicTacToe()
game.play()