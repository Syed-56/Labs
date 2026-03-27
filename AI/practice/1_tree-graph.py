#tree
tree = {
    'A': ['B','C'],
    'B': ['D'],
    'C': ['E','F','G'],
    'F': ['H'],
    'D': [], 'E': [], 'G': [], 'H': []
}
print(tree)

#graph
graph = {
    'A': ['B','C'], #when iterating, we will do for neighbours in tree[node] and access neighbuor as node=neighbour
    'B': ['D'],
    'C': ['E','F','G'],
    'F': ['H'],
    'H': ['A','B'],
    'G': []
}
print(graph)

#weighted
weightedGraph = {
    'A': [['B',5], ['C',10]],   #when iterating, we will do for neighbours in tree[node] and access neighbour as node=neighbour[0] bcz [1] is weight
    #similarly we can make weighted one like this
}
print(weightedGraph)