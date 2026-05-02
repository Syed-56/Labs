from ortools.sat.python import cp_model
#SQ=2, S=5, P=3. SP on mon/thu and SQ on fri
model = cp_model.CpModel()
outfits = {0: "SQ1", 1: "SQ2"}
i=2
for s in range(1,6):
    for p in range(1,4):
        outfits[i] = f"S{s}P{p}"
        i+=1
        
days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday"]
vars = {day: model.new_int_var(0,len(outfits)-1,day) for day in days}

model.add_all_different(vars.values())
model.add(vars["Monday"]>=2)
model.add(vars["Thursday"]>=2)
model.add(vars["Friday"]<=1)

solver = cp_model.CpSolver()
status = solver.solve(model)
if status==cp_model.FEASIBLE or status==cp_model.OPTIMAL:
    for day,var in vars.items():
        print(f"{day} = {outfits[solver.value(var)]}")