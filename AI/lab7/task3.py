from ortools.sat.python import cp_model

puzzle = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9],
]

model = cp_model.CpModel()

cells = {}
for r in range(9):
    for c in range(9):
        cells[(r, c)] = model.new_int_var(1, 9, f"{r}{c}")

for r in range(9):
    for c in range(9):
        if puzzle[r][c] != 0:
            model.add(cells[(r, c)] == puzzle[r][c])

for r in range(9):
    model.add_all_different(cells[(r, c)] for c in range(9))

for c in range(9):
    model.add_all_different(cells[(r, c)] for r in range(9))

for br in range(0, 9, 3):
    for bc in range(0, 9, 3):
        model.add_all_different(
            cells[(br+r, bc+c)]
            for r in range(3) for c in range(3)
        )

solver = cp_model.CpSolver()
if solver.solve(model) in (cp_model.FEASIBLE, cp_model.OPTIMAL):
    for r in range(9):
        print(' '.join(str(solver.value(cells[(r, c)])) for c in range(9)))
else:
    print("No solution.")