#same as bfs like create queue visit set and came from but also a variable for cost so far.
#just sort the queue in every iteration, then pop, verify, append and check for goal.
#now for appending the child and mark it visit, add the current cost in the cost to reach child and compare if the cost is small only then append and add in path and visit.

tree = {
    'A': [['B', 2], ['C', 5]],
    'B': [['D', 1], ['E', 7]],
    'C': [['F', 3], ['G', 2]],
    'D': [['H', 4], ['I', 8]],
    'E': [['J', 1], ['K', 3]],
    'F': [['L', 6], ['M', 2]],
    'G': [['N', 5], ['O', 1]],
    'H': [['P', 3], ['Q', 4]],
    'I': [['R', 2], ['S', 9]],
    'J': [['T', 1], ['U', 2]],
    'K': [['V', 5], ['W', 3]],
    'L': [['X', 1], ['Y', 4]],
    'M': [['Z', 2]], # Z is the 26th node
    'N': [], 'O': [], 'P': [], 'Q': [], 'R': [], 
    'S': [], 'T': [], 'U': [], 'V': [], 'W': [], 
    'X': [], 'Y': [], 'Z': []
}

def ucs(start,goal,tree):
    queue = []
    visited = set()
    came_from = {start: None}
    cost_sofar = {start: 0}
    queue.append((start,0))

    while queue:
        queue.sort(key=lambda x: x[1])
        node, curr_cost = queue.pop(0)
        print(node,"-->",end="")

        if node in visited:
            continue
        if node == goal:
            print("Goal Found with cost = ", curr_cost)
            path = []
            while node is not None:
                path.append(node)
                node = came_from[node]
            return path[::-1]
        
        visited.add(node)
        for neighbour,cost in tree[node]:
            newCost = cost + curr_cost
            if neighbour not in cost_sofar or newCost < cost_sofar[neighbour]:
                cost_sofar[neighbour] = newCost
                came_from[neighbour] = node
                queue.append((neighbour,newCost))
    
    return "Path Not Found"

print(ucs('A','X',tree))