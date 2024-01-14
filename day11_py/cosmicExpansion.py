'''
Theoretical approach

TODO
'''
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

def duplicate_columns(matrix, columns_to_duplicate):
    if not matrix or not matrix[0]:
        return matrix

    duplicated_matrix = []

    for row in matrix:
        duplicated_row = []
        for col_idx, value in enumerate(row):
            if col_idx in columns_to_duplicate:
                duplicated_row.append(value)
            duplicated_row.append(value)

        duplicated_matrix.append(duplicated_row)

    return duplicated_matrix

def expandUniverse(universe):
    new_universe = []

    # Expanding rows
    for line in universe:
        if '#' not in line:
            new_universe.append(line)
        new_universe.append(line)

    # Expanding columns
    toClone = set() 
    hasGalaxy = False

    for j in range(len(universe[0])): 
        for i, row in enumerate(universe):
            if row[j] == '#':
                hasGalaxy = True
                break

        if not hasGalaxy:
            toClone.add(j)
        hasGalaxy = False

    return duplicate_columns(new_universe, list(toClone))

def getGalaxiesPos(universe):
    galaxies = []
    for i,line in enumerate(universe):
        for j,char in enumerate(line):
            if  char == '#':
                galaxies.append((i,j))
    
    return galaxies

def calculateDistancesInAllPairs(galaxies):
    distance = 0
    nGalaxies = len(galaxies)
    nPos = 1
    for initialPos,galaxy in enumerate(galaxies):
        for i in range (nPos,nGalaxies):
            distance += getDistance(galaxy,galaxies[i])
        nPos+=1
    return distance




def getDistance(galA, galB):
    return abs(galA[0] - galB[0])+abs(galA[1] - galB[1])

    

def main():

    universe = expandUniverse(loadUniverse("input.txt"))
    galaxies = getGalaxiesPos(universe)
    print("\nTotal galaxies shortest paths: "+str(calculateDistancesInAllPairs(galaxies)))

if __name__ == "__main__":
    main()
    