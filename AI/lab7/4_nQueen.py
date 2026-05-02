from ortools.sat.python import cp_model
import time

class NQueenPrinter(cp_model.CpSolverSolutionCallback):
    def __init__(self, queens):
        cp_model.CpSolverSolutionCallback.__init__(self)
        self.__queens = queens
        self.__count = 0
        self.__start = time.time()

    def on_solution_callback(self):
        self.__count += 1
        print(f"Solution {self.__count} | time = {time.time() - self.__start:.4f}s")
        n = len(self.__queens)
        for row in range(n):
            for col in range(n):
                if self.Value(self.__queens[col]) == row:
                    print("Q", end=" ")
                else:
                    print("_", end=" ")
        print()

    @property
    def solution_count(self):
        return self.__count

model = cp_model.CpModel()
board_size = 8

# One variable per column, value = row of queen
queens = [model.new_int_var(0, board_size - 1, f"q{i}") for i in range(board_size)]

# Constraints
model.add_all_different(queens)                                          # unique rows
model.add_all_different(queens[i] + i for i in range(board_size))       # unique diagonal
model.add_all_different(queens[i] - i for i in range(board_size))       # unique anti-diagonal

solver = cp_model.CpSolver()
solver.parameters.enumerate_all_solutions = True
printer = NQueenPrinter(queens)
solver.solve(model, printer)
print(f"Total solutions: {printer.solution_count}")