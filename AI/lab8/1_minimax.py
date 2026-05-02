import math

class Node:
    def __init__(self,name,val=None):
        self.name = name
        self.value = val
        self.childrens = []
        
def minimax(node: Node,isMaximizing: bool):
    if not node.childrens:
        return node.value
    
    if isMaximizing:
        bestVal = -math.inf
        for child in node.childrens:
            value = minimax(child,False)
            bestVal = max(bestVal,value)
        node.value = bestVal
        return bestVal
    else:
        bestVal = math.inf
        for child in node.childrens:
            value = minimax(child,True)
            bestVal = min(bestVal,value)
        node.value = bestVal
        return bestVal
        
A = Node("A")   #max
B = Node("B")   #min
C = Node("C")   #min
D = Node("D",2) #max
E = Node("E",3) #max
F = Node("F",5) #max    
G = Node("G",9) #max
A.childrens = [B,C]
B.childrens = [D,E]
C.childrens = [F,G]

result = minimax(A,True)
print("Root Value: ", result)
print(f"Other Values: B={B.value}, C={C.value}, ")