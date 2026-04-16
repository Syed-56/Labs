import sys
import time
from ortools.sat.python import cp_model

model = cp_model.CpModel()
#There are `board_size` number of variables, one for a queen in each column
# of the board. The value of each variable is the row that the queen is in.

board_size = 8
queens = [model.new_int_var(0, board_size - 1, f"x_{i}") for i in range(board_size)]
# All rows must be different.
model.add_all_different(queens)
# No two queens can be on the same diagonal.
model.add_all_different(queens[i] + i for i in range(board_size))
model.add_all_different(queens[i] - i for i in range(board_size))

# Add constraints to prevent queens from attacking diagonally.
diag1 = [ ]
for i in range(board_size): # Reintroduce the loop to define 'i'
    q1 = model.NewIntVar(0, 2 * board_size, 'diag1_%i' % i)
    diag1.append(q1)
    # Need to define j, assuming you want it to be the same as i:
    model.Add(q1 == queens[i] + i)
model.AddAllDifferent(diag1)

class NQueenSolutionPrinter(cp_model.CpSolverSolutionCallback):
    """Print intermediate solutions."""

    def __init__(self, queens: list[cp_model.IntVar]):
        cp_model.CpSolverSolutionCallback.__init__(self)
        self.__queens = queens
        self.__solution_count = 0
        self.__start_time = time.time()

    @property
    def solution_count(self) -> int:
        return self.__solution_count   
    
    def on_solution_callback(self):
        current_time = time.time()
        print(f"Solution {self.__solution_count}, time = {current_time - self.__start_time:.4f} s")
        self.__solution_count += 1
        
        board_range = range(len(self.__queens))
        for row in board_range:
            for col in board_range:
                # Check if the queen in this column (col) is in this row
                if self.Value(self.__queens[col]) == row:
                    print("Q", end=" ")
                else:
                    print("_", end=" ")
            print() 
        print() 
                    
solver = cp_model.CpSolver()
solution_printer = NQueenSolutionPrinter(queens)
solver.parameters.enumerate_all_solutions = True
solver.solve(model, solution_printer)