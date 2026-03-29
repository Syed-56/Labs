#W water L land R rock T treasure. cant traverse water or rock
import copy
class puzzle_Environment:
    def __init__(self,state,start,goal):
        self.start=start
        self.goal=goal
        self.state=state
    
    def get_player_position(self,state):
        for i in range(len(state)):
            for j in range(len(state[0])):
                if state[i][j]=='P':
                    return i,j
    
    def getNeighbours(self,state):
        moves = [(-1,0),(1,0),(0,-1),(0,1)]
        neighbours = []
        row,col = self.get_player_position(state)
        
        for dr,dc in moves:
            r,c = row+dr, col+dc
            if(r>4 or r<0) or (c>4 or c<0) or state[r][c] == 'W' or state[r][c] == 'R':
                continue
            newState = copy.deepcopy(state)
            newState[row][col], newState[r][c] = newState[r][c], newState[row][col]
            neighbours.append(newState)
        return neighbours
        
class GoalBasedAgent:
    def __init__(self,goal):
        self.goal=goal
        
    def bfs(self,env):
        queue = []
        visit = []
        queue.append((env.state,[env.start]))
        visit.append(env.state)
        
        while queue:
            node,path = queue.pop(0)
            row,col = env.get_player_position(node)
            print(f"Visiting: ({row},{col})")  # add this

            if (row,col) == env.goal:
                return path+[(row,col)]
            
            for state in env.getNeighbours(node):
                if state not in visit:
                    queue.append((state,path+[(row,col)]))
                    visit.append(state)
        return None            

def run_agent():
    maze = [
        ['L','L','L','W','R'],
        ['L','R','L','W','L'],
        ['L','L','L','L','L'],
        ['R','R','L','R','W'],
        ['L','L','L','L','T']
    ]
    start = (0,0)
    goal = (4,4)
    maze[0][0] = 'P'
    environment = puzzle_Environment(maze,start,goal)
    agent = GoalBasedAgent(goal)
    path = agent.bfs(environment)
    print(path)
    
run_agent()