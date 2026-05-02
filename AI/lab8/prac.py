import math
SIZE=7

def huerestic(agent,opp,goal):
    distToGoal = abs(agent-goal)
    distToOpp = abs(agent-opp)
    return (SIZE-distToGoal)*2 - distToOpp

def get_moves(pos):
    moves = []
    if pos > 0:
        moves.append(pos-1)
    if pos < SIZE-1:
        moves.append(pos+1)
    return moves

def minimax(agent,opp,goal,depth,limit,isMax):
    if agent==goal:
        return 10
    if agent==opp:
        return -10
    if depth==limit:
        return huerestic(agent,opp,goal)
    
    if isMax:
        best = -math.inf
        for move in get_moves(agent):
            score = minimax(move,opp,goal,depth+1,limit,True)
            best = max(best,score)
        return best
    else:
        best = math.inf
        for move in get_moves(agent):
            score = minimax(agent,move,goal,depth+1,limit,True)
            best = min(best,score)
        return best
    
def agentMove(agent,opp,goal,limit):
    bestScore = -math.inf
    best = agent
    for move in get_moves(agent):
        score = minimax(move,opp,goal,1,limit,False)
        if score > bestScore:
            bestScore=score
            best=move
    return best,bestScore

def oppMove(agent,opp,goal,limit):
    bestScore = math.inf
    best = agent
    for move in get_moves(agent):
        score = minimax(agent,move,goal,1,limit,False)
        if score < bestScore:
            bestScore=score
            best=move
    return best,bestScore

def printBoard(agent,opp,goal,score,turn):
    print("Turn: ", turn, "Score:", score)
    row=""
    for cell in range(SIZE):
        if cell == agent:
            row += "[A]"
        elif cell == opp:
            row += "[O]"
        elif cell == goal:
            row += "[G]"
        elif cell == agent and cell == opp:
            row += "[AO]"
        else:
            row += "[]"
    print(row,"\n")
            
def run_agent():
    agent = 0
    opp   = 3
    goal  = 6
    DEPTH = 3

    print("START")
    print("A=Agent  O=Opponent  G=Goal\n")
    for turn in range(1,15):
        scores = huerestic(agent,opp,goal)
        printBoard(agent,opp,goal,DEPTH)
        
        if agent == goal:
            print("Goal Reached")
            break
        if agent == opp:
            print("Opp Reached")
    
    agent, _ = agentMove(agent,opp,goal,DEPTH)
    opp, _ = oppMove(agent,opp,goal,DEPTH)