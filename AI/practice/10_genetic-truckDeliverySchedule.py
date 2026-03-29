import random
import math
populationSize=10
numTrucks=3
truckCapacity=50
maxGens=10
mutationRate=0.10
numLocs = 5 #excluding depot

locations = {
    0: (0,0),    #start
    1: (2, 4),  
    2: (5, 3),   
    3: (7, 1),   
    4: (1, 6),   
    5: (8, 5) 
}

demands = {
    0: 0,    #start
    1: 2,  
    2: 5,   
    3: 1,   
    4: 6,   
    5: 8 
}
    
def calcDistance(loc1,loc2):
    return math.dist(locations[loc1],locations[loc2])

def create_initial_population():
    population = []
    for _ in range(populationSize):
        gene = list(range(1,numLocs+1)) + [0]*(numTrucks-1)
        random.shuffle(gene)
        while gene[0]==0 or gene[-1]==0 or any(gene[i]==0 and gene[i+1]==0 for i in range(len(gene))):
            random.shuffle(gene)
        population.append(gene)
    return population

#first we calculate routes of trucks by splitting at 0 in a chromosome. 
#then we check capacity by summing demands of locs of truck and penalize if exceed.
#then we calculate distance by adding distance between 2 adjacent locations and initial+final for depot.
def evaluateFitness(gene):
    routes=[]
    current = []

    for location in gene:
        if location==0:
            routes.append(current)
            current = []
        else:
            current.append(location)
    routes.append(current)   #last route
    
    totalDistance=0
    penalty=0
    
    for route in routes:
        if len(route)==0:    #empty truck
            penalty+=10
            continue
        
        totalDemand = sum(demands[loc] for loc in route)
        if totalDemand > truckCapacity:
            penalty+=20
            
        distance = calcDistance(0,route[0])
        for i in range(len(route)-1):
            distance += calcDistance(route[i],route[i+1])
        distance += calcDistance(route[-1],0)
        totalDistance+=distance
    penalty += totalDistance
    return penalty        

def selection(population,fitness_scores):
    scoredPopulation = []
    for i in range(populationSize):
        pair = (fitness_scores[i],population[i])
        scoredPopulation.append(pair)
    scoredPopulation.sort(reverse=False)
    candidates = scoredPopulation[:4]
    parent1,parent2 = random.sample(candidates,2)
    return parent1,parent2

def crossover(parent1,parent2):
    cutPoint1 = random.randint(0,len(parent1))
    cutPoint2 = random.randint(0,len(parent2))
    child = parent1[:cutPoint1]+parent2[cutPoint1:cutPoint2]+parent1[cutPoint2:]
    return child

def mutation(child):
    i,j = random.sample(range(len(child)),2)
    child[i],child[j] = child[j],child[i]
    return child

def premature_convergance(fitness_scores):
    return max(fitness_scores) == min(fitness_scores)

def genetic_algorithm():
    population = create_initial_population()
    print("Initial Population: ", population)
    
    for generation in range(maxGens):
        fitness = [evaluateFitness(individual) for individual in population]
        if premature_convergance(fitness):
            break
        
        newPop = []
        while len(newPop) < populationSize:
            parent1,parent2 = selection(population,fitness)
            child = crossover(parent1[1],parent2[1])
            if random.random() < mutationRate:
                child = mutation(child)
            newPop.append(child)
        population = newPop
        
        print("Generation: ",generation)
        print("Population: ", population)
        print("Fitness: ", fitness)
        print("Selection: ", parent1,parent2)
        print("Child: ", child)

    fitness = [evaluateFitness(individual) for individual in population]
    print("Best Fitness: ", min(fitness))
    bestChild = population[fitness.index(min(fitness))]
    print("Solution: ", bestChild)
    
genetic_algorithm()