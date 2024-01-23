'''
Theoretical approach

Terms:
m = 
n = 
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

def shotBeam(initPos, matrix,energyzedBeams,visited):
    new_beams = []
    not_reached_border = True
    x = initPos[0]
    y = initPos[1]
    new_x = initPos[2]
    new_y = initPos[3]

    while(not_reached_border):
        energyzedBeams[x][y] = 1
        visited.add((x, y,new_x,new_y))
        x = x+new_x
        y = y+new_y
        #Checking if border reached
        if(x < 0 or y < 0 or x >= len(matrix[0]) or y >= len(matrix)):
            not_reached_border = False
            break
        symbol = matrix[x][y]
        #Movement
        #UP
        if(new_x == -1 ):
            if symbol == '-':
                if (x,y,0,-1) not in visited:
                    new_beams.append((x,y,0,-1))
                if (x,y,0,1) not in visited:
                    new_beams.append((x,y,0,1))
                break
            elif symbol == '\\':
                new_x = 0
                new_y = -1
            elif symbol == '/':
                new_x = 0
                new_y = 1
        #DOWN
        elif(new_x == 1):
            if symbol == '-':
                if (x,y,0,-1) not in visited:
                    new_beams.append((x,y,0,-1))
                if (x,y,0,1) not in visited:
                    new_beams.append((x,y,0,1))
                break
            elif symbol == '\\':
                new_x = 0
                new_y = 1
            elif symbol == '/':
                new_x = 0
                new_y = -1       
        #LEFT 
        elif(new_y == -1):
            if symbol == '|':
                if (x,y,-1,0) not in visited:
                    new_beams.append((x,y,-1,0))
                if (x,y,1,0) not in visited:
                    new_beams.append((x,y,1,0))
                break
            elif symbol == '\\':
                new_x = -1 
                new_y = 0
            elif symbol == '/':
                new_x = 1 
                new_y = 0
        #RIGHT
        elif(new_y == 1):
            if symbol == '|':
                if (x,y,-1,0) not in visited:
                    new_beams.append((x,y,-1,0))
                if (x,y,1,0) not in visited:
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

    matrix = loadMatrix("input.txt")
    #matrix = loadMatrix("aux.txt")
    energyzedBeams = [[0 for j in range(len(matrix[0]))] for i in range(len(matrix))]
    visited = set()
    new_beams = [(0,0,1,0)]
    while new_beams:
        new_beams += shotBeam(new_beams.pop(0),matrix,energyzedBeams,visited)
    
    total = sum(sum(energyzedBeams,[]))
    print("Energyzed beams: "+str(total))

if __name__ == "__main__":
    main()
    