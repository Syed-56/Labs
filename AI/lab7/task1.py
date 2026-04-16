from ortools.sat.python import cp_model

NODES = ["A", "B", "C", "D", "E"]
EDGES = [("A", "B"), ("A", "E"), ("B", "C"), ("B", "D"), ("C", "D"), ("D", "E")]
COLORS = {0: "Red", 1: "Green", 2: "Blue"}

model = cp_model.CpModel()
node_vars = {node: model.new_int_var(0, len(COLORS) - 1, node) for node in NODES}

for u, v in EDGES:
    model.add(node_vars[u] != node_vars[v])

class SolverPrinter(cp_model.CpSolverSolutionCallback):
    def __init__(self, variables):
        super().__init__()
        self._vars = variables
        self.count = 0

    def on_solution_callback(self):
        self.count += 1
        output = [f"{n}={COLORS[self.Value(v)]}" for n, v in self._vars.items()]
        print(f"Sol {self.count}: {', '.join(output)}")

solver = cp_model.CpSolver()
solver.parameters.enumerate_all_solutions = True 
printer = SolverPrinter(node_vars)
solver.solve(model, printer)

print(f"Total: {printer.count}")