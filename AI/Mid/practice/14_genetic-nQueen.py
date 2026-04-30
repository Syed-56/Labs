#Genetic Algorithm (N-queen)
import random
n=8
#fitness function - counts non attacking pairs of queen
def calculate_fitness(individual):
    non_attacking_pairs=0
    total_pairs = n*(n-1)//2    #formula for max possible non attacking pair
    for i in range(n):
        for j in range(i+1,n):
            if individual[i]!=individual[j] and abs(individual[i]-individual[j])!=abs(i-j):
                non_attacking_pairs += 1
    
    return non_attacking_pairs/total_pairs

def create_random_individual():
    return random.sample(range(n),n)

def select_parents(population, fitness_scores):
    sorted_population = [board for _, board in sorted(zip(fitness_scores,
population), reverse=True)]
    return sorted_population[:len(population)//2]

def crossover(parent1,parent2):
    point = random.randint(1,n-2)
    child = parent1[:point]+parent2[point:]
    
    #if duplicate values are found (means 2 queens in same row), remove them and replace with missing number
    missing = list(set(range(n)) - set(child))
    for i in range(len(child)):
        if child.count(child[i]) > 1:
            child[i] = missing.pop()
    return child

def mutation(individual):
    idx1, idx2 = random.sample(range(n),2)
    individual[idx1], individual[idx2] = individual[idx2], individual[idx1]
    return individual


def genetic_algorithm():
    populationSize=10
    generation=0
    population = [create_random_individual() for _ in range(populationSize)]

    while True:
        generation+=1
        fitness_scores = [calculate_fitness(ind) for ind in population]
        best_fitness = max(fitness_scores)
        best_individual = population[fitness_scores.index(best_fitness)]

        print(f"Generation: {generation} | Fitness: {best_fitness} | State: {best_individual}")
        if best_fitness==1.0:
            print("\nSolution Found")
            return best_individual

        #select top 50% parents and mutate reproduce
        parents = select_parents(population, fitness_scores)
        new_population = []
        while len(new_population) < populationSize:
            p1, p2 = random.sample(parents,2)
            child = crossover(p1,p2)

            #10% mutation chance
            if random.random() < 0.1:
                child = mutation(child)
            new_population.append(child)

        population = new_population

solution = genetic_algorithm()
print(f"Final Board State: {solution}")   