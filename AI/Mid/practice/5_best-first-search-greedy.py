graph1 = {
    'S': [('A', 3), ('B', 6), ('C', 5)],
    'A': [('D', 9), ('E', 8)],
    'B': [('F', 12), ('G', 14)],
    'C': [('H', 7)],
    'H': [('I', 5), ('J', 6)],
    'I': [('K', 1), ('L', 10), ('M', 2)],
    'D': [], 'E': [],
    'F': [], 'G': [],
    'J': [], 'K': [],
    'L': [], 'M': []
}
from queue import PriorityQueue

#similar concept: create a PQ and a visit set and put the start element with 0 cost in PQ.
#while queue is not empty, pop element, check if goal and then if not visited, visit it and visit its neighbours
#if a neighbour is not visited, put it in PQ
def bestFirstSearch(start,goal,graph1):
    visited = set()
    pq = PriorityQueue()
    pq.put((0,start))

    while not pq.empty():
        cost, node = pq.get()
        if node == goal:
            print(f"{node}({cost})Goal Found")
            return
        if node in visited:
            continue

        visited.add(node)
        print(f"{node}({cost}) --> ", end="")
        for neighbour,cost in graph1[node]:
            if neighbour not in visited:
                pq.put((cost,neighbour))
    print("Goal Not Found")

bestFirstSearch('S','L',graph1)

graph = {
    'A': {'B': 2, 'C': 1},
    'B': {'D': 4, 'E': 3},
    'C': {'F': 1, 'G': 5},
    'D': {'H': 2},
    'E': {},
    'F': {'I': 6},
    'G': {},
    'H': {},
    'I': {}
}
heuristic = {
    'A': 7, 'B': 6, 'C': 5,
    'D': 4, 'E': 7, 'F': 3,
    'G': 6, 'H': 2, 'I': 0
}

def greedy(start,goal,graph,h):
    visit = set()
    queue = PriorityQueue()
    queue.put((start,h[start]))

    while not queue.empty():
        node,_ = queue.get()
        if node == goal:
            print(f"{node}({h[node]})Goal Found")
            return
        
        if node in visit:
            continue

        visit.add(node)
        print(f"{node}({h[node]}) --> ", end="")
        for neighbour, in graph[node]:
            if neighbour not in visit:
                queue.put((neighbour,h[neighbour]))
    print("Goal Not Found")

greedy('A','G',graph,heuristic)