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

#BFS - visit root and push in queue. Then until queue is empty, pop the queue and node we get, check its values in dictionary which are neighbours, check first neighbour and if its not visited, visit and push in queue

#also we will be doing the path reconstructoin too
def bfs(start,goal,tree):
    visited = set()
    queue = []
    visited.add(start)
    queue.append(start)
    path_map = {start: None}    #start has no parent  

    while queue:
        node = queue.pop(0)     #to remove the first element added, otherwise last one is removed
        print(node, "-->", end="")
        if node == goal:
            print("Goal Reached")
            path = []
            while node is not None: #backtracking until start
                path.append(node)
                node = path_map[node]   #go to parent
            return path[::-1]   #reversed
            

        for neighbuors in tree[node]:
            nodeName = neighbuors[0]    
            if nodeName in visited:
                continue
            visited.add(nodeName)
            queue.append(nodeName)
            path_map[nodeName] = node   #link child to parent

    return "Path Not Found"

print("BFS:-")
print(bfs('A','X',tree))

#dfs is all same but instead of queue, use stack
def dfs(start,goal,tree):
    visited = set()
    stack = []
    visited.add(start)
    stack.append(start)
    path_map = {start: None}    #start has no parent  

    while stack:
        node = stack.pop()  
        print(node, "-->", end="")
        if node == goal:
            print("Goal Reached")
            path = []
            while node is not None: #backtracking until start
                path.append(node)
                node = path_map[node]   #go to parent
            return path[::-1]   #reversed
            

        for neighbuors in tree[node]:
            nodeName = neighbuors[0]    
            if nodeName in visited:
                continue
            visited.add(nodeName)
            stack.append(nodeName)
            path_map[nodeName] = node   #link child to parent

    return "Path Not Found"

print("DFS:-")
print(dfs('A','X',tree))

#dls is same, just store a tuple (node,depth) in stack.
def dls(start,goal,tree,limit):
    visited = set()
    stack = []
    visited.add(start)
    stack.append((start,0))
    path_map = {start: None}    #start has no parent  

    while stack:
        node,depth = stack.pop()  
        print(node, "-->", end="")
        if depth > limit:
            print("Path Not Found")
            break
        if node == goal:
            print("Goal Reached")
            path = []
            while node is not None: #backtracking until start
                path.append(node)
                node = path_map[node]   #go to parent
            return path[::-1]   #reversed
            

        for neighbuors in tree[node]:
            nodeName = neighbuors[0]    
            if nodeName in visited:
                continue
            visited.add(nodeName)
            stack.append((nodeName,depth+1))
            path_map[nodeName] = node   #link child to parent

    return None

print("DLS:-")
print(dls('A','X',tree,3))

def ids(start,goal,tree,maxDepth):
    for limit in range(maxDepth+1):
        print("Searching at Depth:", limit)
        result = dls(start,goal,tree,limit)
        if result is not None:
            return result
        
    print("No Goal Found at Max-depth")
    return None

print("IDLS:-")
print(ids('A','X',tree,4))