from ortools.sat.python import cp_model

model = cp_model.CpModel()

puzzle = [
    [0, 0, 6, 2, 0, 5],
    [0, 0, 0, 4, 6, 0],
    [0, 1, 2, 0, 0, 0],
    [5, 6, 0, 0, 0, 4],
    [0, 0, 4, 3, 0, 2],
    [3, 0, 0, 5, 0, 6],
]

# Initialize 6x6 grid variables (Values 1-9 as per your range)
cells = {
    (r, c): model.new_int_var(1, 9, f"({r},{c})") 
    for r in range(6) for c in range(6)
}

# Apply initial puzzle values
for r, row in enumerate(puzzle):
    for c, val in enumerate(row):
        if val:
            model.add(cells[(r, c)] == val)

# Rows and Columns constraints
for i in range(6):
    model.add_all_different(cells[(i, j)] for j in range(6))
    model.add_all_different(cells[(j, i)] for j in range(6))

# 2x3 Sub-box constraints
for r_offset in [0, 2, 4]:
    for c_offset in [0, 3]:
        model.add_all_different(
            cells[(r_offset + r, c_offset + c)] 
            for r in range(2) for c in range(3)
        )

solver = cp_model.CpSolver()
if solver.solve(model) in (cp_model.FEASIBLE, cp_model.OPTIMAL):
    for r in range(6):
        if r % 2 == 0 and r > 0: print("-" * 13)
        line = [str(solver.Value(cells[(r, c)])) for c in range(6)]
        print(f"{' '.join(line[:3])} | {' '.join(line[3:])}")
else:
    print("No solution found.")