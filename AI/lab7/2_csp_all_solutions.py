from ortools.sat.python import cp_model

class VarArraySolutionPrinter(cp_model.CpSolverSolutionCallback):
    """Print Intermediate Solutions"""
    def __init__(self,variables):
        cp_model.CpSolverSolutionCallback.__init__(self)
        self.__variables = variables
        self.__sol_count = 0
        
    def on_solution_callback(self) -> None:
        self.__sol_count+=1
        for v in self.__variables:  #print solutions
            print(f"{v} = {self.value(v)}, ", end="")
        print()
        
    @property   #make a getter function as variable
    def sol_count(self) -> int:
        return self.sol_count

model = cp_model.CpModel()
domain = cp_model.Domain.FromValues([0,1,2])
x = model.new_int_var_from_domain(domain,"x")
y = model.new_int_var_from_domain(domain,"y")
z = model.new_int_var_from_domain(domain,"z")
model.add(x!=y)
solver = cp_model.CpSolver()    #solve
solution_printer = VarArraySolutionPrinter([x,y,z])     #pass to class
solver.parameters.enumerate_all_solutions=True      #find all solutions
status=solver.solve(model,solution_printer)    #call printer
print(f"Solution: ", solver.status_name(status))