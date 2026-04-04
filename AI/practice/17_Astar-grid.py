from queue import PriorityQueue
maze = [
    ["S", "2", "0", "1"],
    ["1", "X", "0", "1"],
    ["0", "1", "X", "2"],
    ["1", "2", "0", "1"]
]

def createGraph(maze):
    rows = len(maze)
    cols = len(maze[0])
    graph = {}
    
    moves = [(-1,0),(1,0),(0,-1),(0,1)]
    for i in range(rows):
        for j in range(cols):
            if maze[i][j]=='#':
                continue
            
            node = (i,j,maze[i][j])
            graph[node] = {}
            for dr,dc in moves:
                r,c = dr+i,dc+j
                if maze[i][j]=='#' or (r<0 and r>rows) or (c<0 and c>cols):
                    continue
                
                neighbour = (r,c,maze[i][j])
                graph[node].append(neighbour)
                
def manhattan(node,goal):
    x1,y1 = node[0],node[1]
    x2,y2 = goal[0],goal[1]
    return abs(x2-x1)+abs(y1-y2)

graph=createGraph(maze)

def Astar(start,goal):
    queue = PriorityQueue()
    visit = set()
    came_from = {start: None}
    gCost = {start: 0}
    queue.put((0+manhattan(start),start))
    
    while queue:
        node ,fcost = queue.get()
        if node==goal:
            path=[]
            while node is not None:
                path.append(node)
                node = came_from[node]
            path.reverse()
            return path,fcost
    
        visit.add(node)
        for neighbour, edgeCost in graph[node]:
            new_gCost = edgeCost+gCost[neighbour]
            new_fCost = new_gCost+manhattan(neighbour)
            if neighbour not in gCost or new_gCost < gCost[neighbour]:
                gCost[neighbour] = new_gCost
                queue.put((new_fCost))
                came_from[neighbour] = node
    return None,0

print(Astar)