from ortools.sat.python import cp_model

model = cp_model.CpModel()
domain = cp_model.Domain.from_intervals([[0,2]])    #domain
#variables
x = model.new_int_var_from_domain(domain,"x")
y = model.new_int_var_from_domain(domain,"y")
z = model.new_int_var_from_domain(domain,"z")
#constraint
model.add(x!=y)
model.add(y>z)
#solve
solver = cp_model.CpSolver()
status = solver.solve(model)
#verify
if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
    print(f"x={solver.value(x)}, y={solver.value(y)}, z={solver.value(z)}")
else:
    print("No Solutions")