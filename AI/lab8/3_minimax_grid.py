import math

ROWS = 5
COLS = 5

def heuristic(agent, opp, goal):
    dist_to_goal = abs(agent[0] - goal[0]) + abs(agent[1] - goal[1])
    dist_opp_to_agent = abs(agent[0] - opp[0]) + abs(agent[1] - opp[1])
    return (ROWS + COLS - dist_to_goal) * 2 - dist_opp_to_agent

def get_moves(pos):
    r, c = pos
    candidates = [(r-1,c), (r+1,c), (r,c-1), (r,c+1)]
    moves = []
    for nr, nc in candidates:
        if 0 <= nr < ROWS and 0 <= nc < COLS:
            moves.append((nr, nc))
    return moves

def minimax(agent, opp, goal, depth, limit, maximizing):
    if agent == goal:
        return 10
    if agent == opp:
        return -10
    if depth == limit:
        return heuristic(agent, opp, goal)

    if maximizing:
        best = -math.inf
        for move in get_moves(agent):
            val = minimax(move, opp, goal, depth+1, limit, False)
            best = max(best, val)
        return best
    else:
        best = math.inf
        for move in get_moves(opp):
            val = minimax(agent, move, goal, depth+1, limit, True)
            best = min(best, val)
        return best

def best_move(agent, opp, goal, limit):
    best_score = -math.inf
    best = agent
    for move in get_moves(agent):
        score = minimax(move, opp, goal, 1, limit, False)
        if score > best_score:
            best_score = score
            best = move
    return best, best_score

def opp_move(agent, opp, goal):
    best_score = math.inf
    best = opp
    for move in get_moves(opp):
        score = minimax(agent, move, goal, 1, 2, True)
        if score < best_score:
            best_score = score
            best = move
    return best

def print_board(agent, opp, goal, score, turn):
    print(f"Turn {turn}  |  Score: {score}")
    print("+" + "---+" * COLS)
    for r in range(ROWS):
        row = "|"
        for c in range(COLS):
            pos = (r, c)
            if pos == agent:
                row += " A |"
            elif pos == opp:
                row += " O |"
            elif pos == goal:
                row += " G |"
            else:
                row += "   |"
        print(row)
        print("+" + "---+" * COLS)
    print()

agent = (0, 0)
opp   = (0, 4)
goal  = (4, 4)
DEPTH = 3

print("START")
print(f"A=Agent, O=Opponent, G=Goal\n")

for turn in range(1, 11):
    score = heuristic(agent, opp, goal)
    print_board(agent, opp, goal, score, turn)

    if agent == goal:
        print("Agent reached the goal!")
        break
    if agent == opp:
        print("Opponent caught the agent!")
        break

    agent, _ = best_move(agent, opp, goal, DEPTH)
    opp = opp_move(agent, opp, goal)