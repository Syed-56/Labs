#f(x) = 2x+1
#a solution is represented in 5 bits (till 32) like in binary so 00001=1 and 00010=2, 01111=15

import random
numBits=5
populationSize=10
maxGens=100
mutationRate=0.10

def toDec(gene):
    number = ""
    for digit in gene:
        number += str(digit)
    x = int(number,2)   #converts string to base-2
    return x

def create_initial_population():
    population = []
    for _ in range(populationSize):
        solution = [random.randint(0,1) for _ in range(numBits)]
        population.append(solution)
    return population

def evaluateFitness(individual):    #fitness function is x^2+x
    x = toDec(individual)
    fitness = x**2 + x
    return fitness
    
def selection(population,fitness_scores):
    scoredPopulation = []
    for i in range(populationSize):
        pair = (fitness_scores[i],population[i])
        scoredPopulation.append(pair)
    scoredPopulation.sort(reverse=True)
    candidates = scoredPopulation[:4]
    parent1,parent2 = random.sample(candidates,2)
    return parent1,parent2

def crossover(parent1,parent2):
    cutPoint = random.randint(0,numBits-1)
    child = parent1[:cutPoint]+parent2[cutPoint:]
    return child

def mutation(child):
    bit = random.randint(0,numBits-1)
    child[bit] ^= 1
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
    print("Best Fitness: ", max(fitness))
    bestChild = population[fitness.index(max(fitness))]
    print("Solution: ", bestChild)
    print("Decimal: ", toDec(bestChild))
    
genetic_algorithm()