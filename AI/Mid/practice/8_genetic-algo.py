import random

items = [(2,6), (3,10), (4,12), (5,15), (9,20)]  #index represent item and tuple is weight,value
capacity = 15

numItems = len(items)
mutationRate=0.30
maxGens=5
populationSize=10

def create_population():
    population = []
    for _ in range(populationSize):
        gene = [random.randint(0,1) for _ in range(numItems)]
        population.append(gene)
    return population

def evaluateFitness(gene):
    fitness = 0
    weight = 0
    for i in range(numItems):
        if gene[i]==1:
            fitness += items[i][1]
            weight += items[i][0]
            
    if weight>capacity:
        return 0
    else:
        return fitness
    
def selection(fitnessScores,population):
    scoredPopulation = []
    for i in range(populationSize):
        pair = (fitnessScores[i], population[i])
        scoredPopulation.append(pair)
    scoredPopulation.sort(reverse=True)
    #tournament selection - select top 4 candidates and return any 2
    candidates = scoredPopulation[:4]
    parent1,parent2 = random.sample(candidates,2)
    return parent1,parent2

def crossover(parent1,parent2):
    cutPoint = random.randint(0,numItems-1)
    child = parent1[:cutPoint]+parent2[cutPoint:]
    return child

def mutation(child):
    bit = random.randint(0,numItems-1)
    child[bit] ^= 1     #flips 0->1 or 1->0
    return child

def premature_convergance(fitnessScores):
    return max(fitnessScores) == min(fitnessScores)

def geneticAlgorithm():
    population = create_population()
    print("Initial Population: ", population)
    for generation in range(maxGens):
        fitness = [evaluateFitness(individual) for individual in population]
        if premature_convergance(fitness):
            break
        
        new_population = []
        while len(new_population) < populationSize:
            parent1,parent2 = selection(fitness,population)
            child = crossover(parent1[1],parent2[1])
            if random.random() < 0.10:
                child = mutation(child)
            new_population.append(child)
        
        population = new_population            
        print("Generation:" ,generation)
        print("Population: ",population)
        print("Fitness: ",fitness)
        print("Selection: ", parent1,parent2)
        print("Child: ", child)
        
    finalFitness = [evaluateFitness(individual) for individual in population]
    print("Best Fitness = ", max(finalFitness))
    bestChild = population[fitness.index(max(finalFitness))]
    print("Best Child: " ,bestChild)
    
        
geneticAlgorithm()