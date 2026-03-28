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

def Astar(start,goal,graph,h):
    queue = PriorityQueue()
    visited = set()
    came_from = {start: None}
    gCost = {start: 0}
    #f(n)=h(n)+g(n)
    queue.put((0+h[start],start))

    while queue:
        curr_fCost,node = queue.get()
        if node in visited:
            continue
        visited.add(node)
        print(f"{node}({curr_fCost}) --> ",end="")

        if node==goal:
            print("Goal Reached")
            path = []
            while node is not None:
                path.append(node)
                node = came_from[node]
            path.reverse()
            return path
        
        for neighbour,cost in graph[node].items():
            new_gCost = gCost[node] + cost
            new_fCost = new_gCost + h[neighbour]

            if neighbour not in gCost or new_gCost < gCost[neighbour]:
                gCost[neighbour] = new_gCost
                came_from[neighbour] = node
                queue.put((new_fCost,neighbour))
    print("Goal Not Found")
    return None

print(Astar('A','G',graph,heuristic))


        