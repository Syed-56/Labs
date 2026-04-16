#CSP model has variables and domains with specific constraints
#here we create variables x,y,z with domains 0,1,2 having a constraint x!=y

from ortools.sat.python import cp_model
model = cp_model.CpModel()  #initialize model
#declare variables
num_vals=3
x = model.new_int_var(0,num_vals,"x")
y = model.new_int_var(0,num_vals,"y")
z= model.new_int_var(0,num_vals,"z")

model.add(x!=y) #constraint

#model is defined now run solver
solver = cp_model.CpSolver()
status = solver.solve(model)

if status==cp_model.OPTIMAL or status==cp_model.FEASIBLE:
    print(f"x = {solver.value(x)}, y = {solver.value(y)}, z = {solver.value(z)}")
else:
    print("No Solution Found")