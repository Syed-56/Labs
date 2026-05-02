#A factory produces three products x, y, z. The production is subject to the following resource constraints:

# Resource A: 2x + 7y + 3z ≤ 50
# Resource B: 3x - 5y + 7z ≤ 45
# Resource C: 5x + 2y - 6z ≤ 37

# Each unit of x gives a profit of 2, each unit of y gives a profit of 2, and each unit of z gives a profit of 3. All quantities must be non-negative integers.
# Find the values of x, y, and z that maximize the total profit:
# Maximize: 2x + 2y + 3z
from ortools.sat.python import cp_model
def main() -> None:
    """Minimal CP-SAT example to showcase calling the solver."""
    # Creates the model.
    model = cp_model.CpModel()
    # Creates the variables.
    var_upper_bound = max(50, 45, 37)
    domain = cp_model.Domain.from_intervals([[0,var_upper_bound]])
    x = model.new_int_var_from_domain(domain, "x")
    y = model.new_int_var_from_domain(domain, "y")
    z = model.new_int_var_from_domain(domain, "z")
    # Creates the constraints.
    model.add(2 * x + 7 * y + 3 * z <= 50)
    model.add(3 * x - 5 * y + 7 * z <= 45)
    model.add(5 * x + 2 * y - 6 * z <= 37)
    
    model.maximize(2 * x + 2 * y + 3 * z)
# Creates a solver and solves the model.
    solver = cp_model.CpSolver()
    status = solver.solve(model)
    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(f"Maximum of objective function: {solver.objective_value}\n")
        print(f"x = {solver.value(x)}")
        print(f"y = {solver.value(y)}")
        print(f"z = {solver.value(z)}")
    else:
        print("No solution found.")
        # Statistics.
    print("\nStatistics")
    print(f" status : {solver.status_name(status)}")
    print(f" conflicts: {solver.num_conflicts}")
    print(f" branches : {solver.num_branches}")
    print(f" wall time: {solver.wall_time} s")
        
main()