#we are creating the 8-state puzzle game which will initially have a start state and a required goal state
class PuzzleEnvironment:
    def __init__(self,start,goal):
        self.start=start
        self.goal=goal

    #now for searching we visualize like a tree so we get neighbours which are the states after the move has been made
    def getNeighbours(self,state):
        neighbours=[]
        empty=state.index(0)
        row, col = divmod(empty,3)   #we have the 1d array so to visualize in 2d we convert the index into row/col
        moves = [(-1,0),(1,0),(0,-1),(0,1)]

        for dr,dc in moves:
            r,c = row+dr, col+dc  #we try all 4 possible moves for the empty box
            if (r>=0 and r<3) and (c>=0 and c<3):
                new_idx = r*3 + c   #since originally it is in 1d array so convert back
                newState = list(state)
                newState[empty], newState[new_idx] = newState[new_idx], newState[empty]
                neighbours.append(tuple(newState))
        return neighbours
    
class GoalBasedAgent:
    def __init__(self,goal):
        self.goal=goal
    
    def bfs(self,env):
        start = env.start
        queue = []
        visited = set()
        queue.append((start,[]))  #state and the path to reach the state
        visited.add(start)

        count=0 #check the nods we checked
        while queue:
            node,path = queue.pop(0)
            count+=1
            if node == self.goal:
                print("Nodes Taken: ", count)
                return path + [node]
            
            for neighbours in env.getNeighbours(node):
                if neighbours not in visited:
                    queue.append((neighbours, path+[node]))
                    visited.add(neighbours)
        return None

def run_agent():
    start_state = (7, 2, 4, 5, 0, 6, 8, 3, 1)
    goal_state = (0, 1, 2, 3, 4, 5, 6, 7, 8)
    puzzle = PuzzleEnvironment(start_state,goal_state)
    agent = GoalBasedAgent(goal_state)

    result = agent.bfs(puzzle)
    if result:
        print("Path: ", result)
    
run_agent()