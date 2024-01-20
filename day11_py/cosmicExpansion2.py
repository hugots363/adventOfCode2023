'''
Theoretical approach

TODO
'''

import bisect 

def loadUniverse(file):
    universe = []
    try:
        with open(file, 'r') as file:
            for line in file:
                line = line.rstrip('\n')
                universe.append(line)
    except FileNotFoundError:
        print(f"The file '{file}' was not found.")
    return universe


def getExpandedRows(universe):
    exp_rows = []

    for x,line in enumerate(universe):
        if '#' not in line:
            bisect.insort(exp_rows, x) 
    return exp_rows

def getExpandedCols(universe):
    exp_cols = []

    for j in range(len(universe[0])): 
        hasGalaxy = any(row[j] == '#' for row in universe)
        if not hasGalaxy:
            index = bisect.bisect_left(exp_cols, j)
            exp_cols.insert(index, j)

    return exp_cols

def getGalaxiesPos(universe):
    galaxies = []
    for i,line in enumerate(universe):
        for j,char in enumerate(line):
            if  char == '#':
                galaxies.append((i,j))
    
    return galaxies

def calculateDistancesInAllPairs(galaxies,exp_rows,exp_cols):
    distance = 0
    nGalaxies = len(galaxies)
    nPos = 1
    for initialPos,galaxy in enumerate(galaxies):
        for i in range (nPos,nGalaxies):
            distance += getDistance(galaxy,galaxies[i],1,exp_cols,exp_rows)
        nPos+=1
    return distance

def binary_search(sorted_sequence, target):
    index = bisect.bisect_left(sorted_sequence, target)
    return index < len(sorted_sequence) and sorted_sequence[index] == target

def getDistance(galA, galB,expanded_dist, expanded_rows, expanded_cols):
    distance = 0 
    #print(galA)
    #print(galB)
    if galA[0] != galB[0]:
        a, b = min(galA[0],galB[0]), max(galA[0],galB[0])
        for x in range(a+1,b+1):
            #print(x)
            if binary_search(expanded_cols,x):
                distance+= expanded_dist
            else:
                distance+= 1
    #print("D: " +str(distance))
    if galA[1] != galB[1]:
        a, b = min(galA[1],galB[1]), max(galA[1],galB[1])
        for y in range(a+1,b+1):
            #print(y)
            if binary_search(expanded_rows,y):
                distance+= expanded_dist
            else:
                distance+= 1  
    #print("D: " +str(distance))
    #print("-------------------")
    return distance        

def main():

    universe = loadUniverse("input.txt")
    exp_rows = getExpandedRows(universe)
    #print(exp_rows)
    exp_cols = getExpandedCols(universe)
    #print(exp_cols)
    galaxies = getGalaxiesPos(universe)
    distance = calculateDistancesInAllPairs(galaxies,exp_rows,exp_cols)
    print("\nTotal galaxies shortest paths: "+str(distance))

if __name__ == "__main__":
    main()
    