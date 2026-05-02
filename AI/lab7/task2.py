from ortools.sat.python import cp_model

model = cp_model.CpModel()

outfits = {0: "SQ1", 1: "SQ2"}
i = 2
#outfit[0 and 1] are SQ[] and outfit[2...16] are S[]P[]
for s in range(1, 6):
    for p in range(1, 4):
        outfits[i] = f"S{s}-P{p}"
        i += 1

work_days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday"]
vars = {day: model.new_int_var(0, len(outfits) - 1, day) for day in work_days}

model.add_all_different(vars.values())

for day in ["Monday", "Thursday"]:
    model.add(vars[day] >= 2)

model.add(vars["Friday"] <= 1)

solver = cp_model.CpSolver()
if solver.solve(model) in (cp_model.FEASIBLE, cp_model.OPTIMAL):
    for day, var in vars.items():
        print(f"{day}: {outfits[solver.value(var)]}")