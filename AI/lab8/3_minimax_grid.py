import math

GRID_SIZE = 5
GOAL_POS = 4
AGENT_START = 0
OPPONENT_START = 2

leaf_heuristics = []

def heuristic(agent_pos, opponent_pos):
    distance_to_goal = abs(agent_pos - GOAL_POS)
    distance_opponent_to_agent = abs(agent_pos - opponent_pos)
    h = (GRID_SIZE - distance_to_goal) * 2 - distance_opponent_to_agent
    return h

def get_moves(pos):
    moves = []
    if pos > 0:
        moves.append(pos - 1)
    if pos < GRID_SIZE - 1:
        moves.append(pos + 1)
    return moves

def minimax(agent_pos, opponent_pos, depth, is_maximizing, depth_limit):
    if agent_pos == GOAL_POS:
        return 10
    if agent_pos == opponent_pos:
        return -10
    if depth == depth_limit:
        h = heuristic(agent_pos, opponent_pos)
        leaf_heuristics.append({
            "agent": agent_pos,
            "opponent": opponent_pos,
            "heuristic": h,
            "depth": depth
        })
        return h

    if is_maximizing:
        best = -math.inf
        for move in get_moves(agent_pos):
            val = minimax(move, opponent_pos, depth + 1, False, depth_limit)
            best = max(best, val)
        return best
    else:
        best = math.inf
        for move in get_moves(opponent_pos):
            val = minimax(agent_pos, move, depth + 1, True, depth_limit)
            best = min(best, val)
        return best

def best_move(agent_pos, opponent_pos, depth_limit):
    best_val = -math.inf
    best = agent_pos
    for move in get_moves(agent_pos):
        val = minimax(move, opponent_pos, 1, False, depth_limit)
        if val > best_val:
            best_val = val
            best = move
    return best, best_val

def simulate(initial_agent, initial_opponent, depth_limit, steps=3):
    global leaf_heuristics
    leaf_heuristics = []

    print(f"SIMULATION  |  Depth Limit = {depth_limit}  |  Grid Size = {GRID_SIZE}")
    print(f"Goal at position {GOAL_POS}  |  Start: Agent={initial_agent}, Opponent={initial_opponent}")

    agent_pos = initial_agent
    opponent_pos = initial_opponent

    game_states = [
        (initial_agent, initial_opponent),
        (initial_agent + 1, initial_opponent),
        (initial_agent + 1, initial_opponent - 1),
    ]

    for i, (a_pos, o_pos) in enumerate(game_states):
        leaf_heuristics = []
        move, score = best_move(a_pos, o_pos, depth_limit)
        print(f"\n  State {i+1}: Agent @ {a_pos}, Opponent @ {o_pos}")
        print(f"  Grid: ", end="")
        for cell in range(GRID_SIZE):
            if cell == a_pos and cell == o_pos:
                print("[AO]", end="")
            elif cell == a_pos:
                print("[ A]", end="")
            elif cell == o_pos:
                print("[ O]", end="")
            elif cell == GOAL_POS:
                print("[ G]", end="")
            else:
                print("[  ]", end="")
        print()
        print(f"Chosen move: Agent moves to position {move}  (score={score})")
        print(f"Heuristic values at leaf nodes:")
        for lh in leaf_heuristics[:6]:
            print(f"    Agent={lh['agent']}, Opponent={lh['opponent']} => h={lh['heuristic']}")
        if len(leaf_heuristics) > 6:
            print(f"    ... ({len(leaf_heuristics) - 6} more leaf nodes)")

def compare_depths():
    print("COMPARISON: depth=2 vs depth=3")

    test_states = [
        (0, 2),
        (1, 3),
        (2, 4),
    ]

    for a, o in test_states:
        move2, score2 = best_move(a, o, depth_limit=2)
        move3, score3 = best_move(a, o, depth_limit=3)
        print(f"\n  State: Agent={a}, Opponent={o}")
        print(f"    depth=2 => move to {move2}, score={score2}")
        print(f"    depth=3 => move to {move3}, score={score3}")
        if move2 != move3:
            print(f"Different decisions! depth=3 sees further ahead.")
        else:
            print(f"Same decision, but depth=3 has more confidence.")

simulate(AGENT_START, OPPONENT_START, depth_limit=3)
compare_depths()

print("LEGEND\n")
print("  A = Agent (Max player) wants to reach G (+10)")
print("  O = Opponent (Min player) tries to block (-10)")
print("  G = Goal position")
print("  Heuristic = (GRID_SIZE - dist_to_goal)*2 - dist_opponent_to_agent")