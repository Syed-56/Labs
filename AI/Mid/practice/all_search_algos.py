from queue import PriorityQueue
graph = {
    'A': {'B': 4, 'C': 3},
    'B': {'E': 12, 'F': 5},
    'C': {'D': 7, 'E': 10},
    'D': {'E': 2},
    'E': {'G': 5},
    'F': {'G': 16},
    'G': {},
}
heuristic = {'A': 14,'B': 12,'C': 11,'D': 6,'E': 4, 'F': 11,'G': 0 }

def bfs(start,goal):
    queue = []
    visit = set()
    queue.append(start)
    visit.add(start)
    came_from = {start: None}
    
    while queue:
        node = queue.pop(0)
        if node == goal:
            print(f"{node}   Goal Found\n",end="")
            path = []
            while node is not None:
                path.append(node)
                node = came_from[node]
            path.reverse()
            print("Path: ", path)
            return
        
        print(f"{node} --> ",end="")
        for neighbour in graph[node]:
            if neighbour in visit:
                continue
            queue.append(neighbour)
            visit.add(neighbour)
            came_from[neighbour] = node  
    print("Goal Not Found")  
    
def dfs(start,goal):
    stack = []
    visit = set()
    stack.append(start)
    visit.add(start)
    came_from = {start: None}
    
    while stack:
        node = stack.pop()
        if node == goal:
            print(f"{node}   Goal Found\n",end="")
            path = []
            while node is not None:
                path.append(node)
                node = came_from[node]
                path.reverse()
            print("Path: ", path)
            return
        
        print(f"{node} --> ",end="")
        for neighbour in graph[node]:
            if neighbour in visit:
                continue
            stack.append(neighbour)
            visit.add(neighbour)
            came_from[neighbour] = node  
    print("Goal Not Found") 
    
def dls(start,goal,limit):
    stack = []
    visit = set()
    stack.append((start,0))
    visit.add(start)
    came_from = {start: None}
    
    while stack:
        node,depth = stack.pop()
        if depth > limit:
            break
        
        if node == goal:
            print(f"{node}   Goal Found\n",end="")
            path = []
            while node is not None:
                path.append(node)
                came_from[node]=node
                path.reverse()
            print("Path: ", path)
            return path
        
        print(f"{node} --> ",end="")
        for neighbour in graph[node]:
            if neighbour in visit:
                continue
            stack.append((neighbour,depth+1))
            visit.add(neighbour)
            came_from[neighbour] = node  
    print("Goal Not Found") 
    return None
    
def ids(start,goal,limit):
    for depth in range(limit+1):
        print(f"Search at Depth: {depth}\n")
        result = dls(start,goal,depth)
        if result is not None:
            break
        
def ucs(start,goal):
    queue = PriorityQueue()
    visit = set()
    came_from = {start: None}
    cost_sofar = {start: 0}
    queue.put((0,start))
    
    while not queue.empty():
        cost,node = queue.get()
        if node in visit:
            continue
        if node == goal:
            path = []
            print(f"{node}({cost})   Goal Found\n",end="")
            while node is not None:
                path.append(node)
                node=came_from[node]
            path.reverse()
            print("Path: ",path)
            print("Cost: ",cost)
            return
        visit.add(node)
        print(f"{node}({cost}) --> ", end="")
        
        for neighbour,edgecost in graph[node].items():
            newCost = cost+edgecost
            if neighbour not in cost_sofar or newCost < cost_sofar[neighbour]:
                cost_sofar[neighbour] = newCost
                came_from[neighbour] = node
                queue.put((newCost,neighbour))
    print("Goal Not Found")
    
def best_first_search(start,goal):
    queue = PriorityQueue()
    visit = set()
    came_from = {start: None}
    queue.put((0,start))
    
    while not queue.empty():
        cost,node = queue.get()
        if node in visit:
            continue
        if node == goal:
            path = []
            print(f"{node}({cost})   Goal Found\n",end="")
            while node is not None:
                path.append(node)
                node=came_from[node]
            path.reverse()
            print("Path: ",path)
            return
        
        visit.add(node)
        print(f"{node}({cost}) --> ", end="")
        for neighbour,edgecost in graph[node].items():
            if neighbour not in visit:
                queue.put((edgecost,neighbour))
                came_from[neighbour] = node
    print("Goal Not Found")

def greedy(start,goal,h):
    queue = PriorityQueue()
    visit = set()
    came_from = {start: None}
    queue.put((0,start))
    
    while not queue.empty():
        _,node = queue.get()
        if node in visit:
            continue
        if node == goal:
            path = []
            print(f"{node}({h[node]})   Goal Found\n",end="")
            while node is not None:
                path.append(node)
                node=came_from[node]
            path.reverse()
            print("Path: ",path)
            return
        
        visit.add(node)
        print(f"{node}({h[node]}) --> ", end="")
        for neighbour,_ in graph[node].items():
            if neighbour not in visit:
                queue.put((h[neighbour],neighbour))
                came_from[neighbour] = node
    print("Goal Not Found")
    
def Astar(start,goal,h):
    queue = PriorityQueue()
    visit = set()
    came_from = {start: None}
    gCosts = {start: 0}
    queue.put((0+h[start],start))
    
    while not queue.empty():
        cost,node = queue.get()
        if node in visit:
            continue
        if node==goal:
            path=[]
            print(f"{node}({gCosts[node]})    Goal Found\n",end="")
            while node is not None:
                path.append(node)
                node=came_from[node]
            path.reverse()
            print(f"Path: {path} with Cost: {cost}")
            return
        
        visit.add(node)
        print(f"{node}({h[node]}+{gCosts[node]}) --> ", end="")

        for neighbour,edgecost in graph[node].items():
            new_gCost = edgecost+gCosts[node]
            new_fCost = new_gCost+h[neighbour]
            
            if neighbour not in gCosts or new_gCost<gCosts[neighbour]:
                gCosts[neighbour]=new_gCost
                came_from[neighbour]=node
                queue.put((new_fCost,neighbour))
    print("Goal Not Found")
    
import heapq
def local_search(start,goal,beam_width):
    beam = []
    beam.append((0,[start]))
    
    while beam:
        candidates = []
        for cost,path in beam:
            currNode = path[-1]
            if currNode == goal:
                print(f"Path: {path} with Cost: {cost}\n",end="")
                return
            
            for neighbour,edgeCost in graph[currNode].items():
                newCost = cost+edgeCost
                newPath = path+[neighbour]
                candidates.append((newCost,newPath))
                
            beam = heapq.nsmallest(beam_width,candidates,key=lambda x:x[0])
    print("Goal Not Found")
    
def hill_climbing(start,goal,h):
    currentPath = [start]
    currentCost = 0
    
    while True:
        node = currentPath[-1]
        if node == goal:
            print(f"Path: {currentPath} with Cost: {currentCost}",end="")
            return
        
        moved=False
        for neighbour,edgeCost in graph[node].items():
            if h[neighbour]<h[node]:
                currentPath = currentPath+[neighbour]
                currentCost += edgeCost
                moved=True
                break
        if not moved:
            print("Goal Not Found")
            return
        
print("BFS = ", end="")
bfs('A','G')
print("DFS = ", end="")
dfs('A','G')
print("UCS = ", end="")
ucs('A','G')
print("Best First Search = ", end="")
best_first_search('A','G')
print("Greedy = ",end="")
greedy('A','G',heuristic)
print("A* = ",end="")
Astar('A','G',heuristic)
print("Local Search = ",end="")
local_search('A','G',2)
print("Hill Climbing = ",end="")
hill_climbing('A','G',heuristic)