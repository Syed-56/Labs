from queue import PriorityQueue

def get_manhattan_distance(state, goal):
    """Calculates the sum of distances of tiles from their goal positions."""
    distance = 0
    for r in range(3):
        for c in range(3):
            val = state[r][c]
            if val != 0: 
                for gr in range(3):
                    for gc in range(3):
                        if goal[gr][gc] == val:
                            distance += abs(r - gr) + abs(c - gc)
    return distance

def get_neighbors(state):
    neighbors = []
    r, c = -1, -1
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0:
                r, c = i, j
                break

    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)] 
    for dr, dc in moves:
        nr, nc = r + dr, c + dc
        if 0 <= nr < 3 and 0 <= nc < 3:
            new_state = [list(row) for row in state]
            new_state[r][c], new_state[nr][nc] = new_state[nr][nc], new_state[r][c]
            neighbors.append(tuple(tuple(row) for row in new_state))
    return neighbors

def solve_8_puzzle(start, goal):
    queue = PriorityQueue()
    h_start = get_manhattan_distance(start, goal)
    queue.put((h_start, start))
    
    visited = set()
    came_from = {start: None}
    gCost = {start: 0}

    while not queue.empty():
        curr_f, node = queue.get()

        if node in visited:
            continue
        visited.add(node)

        if node == goal:
            path = []
            while node is not None:
                path.append(node)
                node = came_from[node]
            path.reverse()
            return path

        for neighbor in get_neighbors(node):
            new_g = gCost[node] + 1
            if neighbor not in gCost or new_g < gCost[neighbor]:
                gCost[neighbor] = new_g
                h = get_manhattan_distance(neighbor, goal)
                came_from[neighbor] = node
                queue.put((new_g + h, neighbor))

    return None

start_node = (
    (1, 2, 3),
    (4, 0, 6),
    (7, 5, 8)
)

goal_node = (
    (1, 2, 3),
    (4, 5, 6),
    (7, 8, 0)
)

solution = solve_8_puzzle(start_node, goal_node)

if solution:
    print(f"Solved in {len(solution)-1} moves!")
    for step in solution:
        for row in step:
            print(row)
        print("\n")
