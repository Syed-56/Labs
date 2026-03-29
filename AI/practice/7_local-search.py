import heapq
graph = {
    'S': [('A', 3), ('B', 6), ('C', 5)],
    'A': [('D', 9), ('E', 8)],
    'B': [('F', 12),
    ('G', 14)],
    'C': [('H', 7)],
    'H': [('I', 5),
    ('J', 6)],
    'I': [('K', 1),
    ('L', 10), ('M', 2)],
    'D': [],'E': [],
    'F': [],'G': [],
    'J': [],'K': [],
    'L': [],'M': []
}
heuristic = {
    'S': 15,'A': 12,'B': 13, 'C': 11,
    'D': 8,'E': 9,'F': 10,'G': 12,
    'H': 7,'I': 4,'J': 6,'K': 3,
    'L': 2,'M': 0   # goal
}

def local_beam(start,goal,beam_width):
    beam = []
    beam.append((0,[start])) #cost and path
    while beam:
        candidates = []
        for cost,path in beam:
            currentNode = path[-1]
            if currentNode==goal:
                return cost,path
            
            for neighbour,edgeCost in graph[currentNode]:
                newCost = cost+edgeCost
                newPath = path+[neighbour]
                candidates.append((newCost,newPath))
                
            beam = heapq.nsmallest(beam_width,candidates,key=lambda x:x[0])
    return None,0

cost,path = local_beam('S','L',3)   
print(f"Local Beam: Path: {path} and Cost: {cost}")

def hill_climbing(start,goal,graph,h):
    currentPath = [start]
    currentCost = 0
    
    while True:
        node = currentPath[-1]
        if node==goal:
            return currentPath, currentCost
        
        moved=False
        for neighbour,edge_cost in graph[node]:
            if  h[neighbour]<h[node]:
                currentCost += edge_cost
                currentPath=currentPath+[neighbour]
                moved=True
                break
                
        if not moved:
            return None,0
        
path,cost = hill_climbing('S','A',graph,heuristic)
print(f"Hill Climbing: Path: {path} and Cost: {cost}")
