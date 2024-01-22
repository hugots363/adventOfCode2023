'''
Theoretical approach

Terms:
m = number of lines in the file
n = quantity of chars in each line

The total cost of the algorithm is O(m*n+m*n+m*n+(mn)^2) = O(mn+(mn)^2) = O((mn)^2)

This would be in the worst case scenario were all the chars are galaxies
'''

def loadMatrix(file):
    matrix = []
    try:
        with open(file, 'r') as f:
            for line in f:
                line = line.rstrip('\n')
                matrix.append(line)
    except FileNotFoundError:
        print(f"The file '{file}' was not found.")
    return matrix

def shotBeam(initPos, matrix,energyzedBeams):
    new_beams = []
    not_reached_border = True
    x = initPos[0]
    y = initPos[1]
    new_x = initPos[2]
    new_y = initPos[3]

    while(not_reached_border):
        energyzedBeams[x][y] = 1
        x = x+new_x
        y = y+new_y
        #Checking if border reached
        if(x < 0 or y < 0 or x >= len(matrix[0]) or y >= len(matrix)):
            not_reached_border = False
            break
        symbol = matrix[x][y]
        #Movement
        #UP and DOWN
        if(new_x == -1 or new_x == 1):
            if symbol == '-':
                new_beams.append((x,y,0,-1))
                new_beams.append((x,y,0,1))
                break
            elif symbol == '\\':
                new_x = 0
                new_y = -1
            elif symbol == '/':
                new_x = 0
                new_y = 1
        #LEFT 
        elif(new_y == -1):
            if symbol == '|':
                new_beams.append((x,y,-1,0))
                new_beams.append((x,y,1,0))
                break
            elif symbol == '\\':
                new_x = -1 
                new_y = 0
            elif symbol == '/':
                new_x = 1 
                new_y = 0
        #RIGHT
        else:
            if symbol == '|':
                new_beams.append((x,y,-1,0))
                new_beams.append((x,y,1,0))
                break
            elif symbol == '\\':
                new_x = 1 
                new_y = 0
            elif symbol == '/':
                new_x = -1 
                new_y = 0
    return new_beams
    

def main():

    matrix = loadMatrix("aux.txt")
    energyzedBeams = [[0 for j in range(len(matrix[0]))] for i in range(len(matrix))]
    new_beams = [(0,0,0,1)]
    while new_beams:
        new_beams += shotBeam(new_beams.pop(0),matrix,energyzedBeams)
        print("beams:" + str(new_beams))
    
    total = sum(sum(energyzedBeams,[]))
    print("Energyzed beams: "+str(total))

if __name__ == "__main__":
    main()
    