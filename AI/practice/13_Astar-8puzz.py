from queue import PriorityQueue
import copy

class PuzzleEnvironment:
    def __init__(self,start,goal):
        self.start = start
        self.goal = goal
       
    def get_0_position(self,state):
        for i in range(len(state)):
            for j in range(len(state[0])):
                if state[i][j]==0:
                    return i,j
                
    def getNeighbours(self,state):
        neighbours=[]
        row,col = self.get_0_position(state)
        moves = [(-1,0),(1,0),(0,-1),(0,1)]
            
        for dr, dc in moves:
            r,c = row+dr,col+dc
            if(r>=3 or r<0) or (c>=3 or c<0):
                continue
            newState = copy.deepcopy(state)
            newState[row][col], newState[r][c] = newState[r][c], newState[row][col]
            neighbours.append(newState)
        return neighbours
        
class GoalBasedAgent:
    def __init__(self,goal):
        self.goal=goal
        
    def huerestic(self,state,goal):
        goal_map = {}
        for r in range(3):
            for c in range(3):
                tile = goal[r][c]
                goal_map[tile] = (r,c)
                
        totalDistance=0
        for r in range(3):
            for c in range(3):
                tile = state[r][c]
                if tile==0:
                    continue
                tr,tc = goal_map[tile]  #where it should be
                totalDistance += abs(r-tr)+abs(c-tc)
        return totalDistance
    
    def A_star(self,env):
        queue = PriorityQueue()
        visited = []
        came_from = {start: None}
        start=env.start
        gCosts = {start:0}
        hCosts = self.huerestic(start,env.goal)
        queue.put((gCosts[start]+hCosts[start], start))
        visited.append(start)
        
        while not queue.empty():
            curr_fCost,node = queue.get()
            if node in visited:
                continue
            visited.add(node)
            print(f"{node}({curr_fCost}) --> ",end="")

            if node==env.goal:
                print("Goal Reached")
                path = []
                while node is not None:
                    path.append(node)
                    node = came_from[node]
                path.reverse()
                return path
            
            for neighbour,cost in env.getNeighbours([node]):
                new_gCost = gCosts[node] + cost
                new_fCost = new_gCost + hCosts[neighbour]

                if neighbour not in gCosts or new_gCost < gCosts[neighbour]:
                    gCosts[neighbour] = new_gCost
                    came_from[neighbour] = node
                    queue.put((new_fCost,neighbour))
        print("Goal Not Found")
        return None
        
def run_agent():
    puzzle = [
        [7,2,4],
        [5,0,6],
        [8,3,1]
    ]
    goal = [
        [0,1,2],
        [3,4,5],
        [6,7,8]
    ]
    env = PuzzleEnvironment(puzzle,goal)
    agent = GoalBasedAgent(goal)
    