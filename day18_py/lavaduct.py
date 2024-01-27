'''
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of chars in each line

The total cost of the algorithm is O(mn)

Pick's theorem
Area = points_inside + points_in_the_boundary/2 +1  ->
points_inside = Area -points_in_the_boundary/2 -1

The result for the problem is the sum of inside and boundary ponts.

So, we need the Area, that we are going to calculate using the Shoelace formula
to calculate the area of the polygon . 
'''



def get_init(file_path):
    try:
        with open(file_path, 'r') as file:
            rows = file.readlines()
            return (len(rows),0)
            
    except FileNotFoundError:
        return None  

def extractDataFromLine(line):
    dir = line[0]
    quant = int(line[2])
    rgb = line[6:11]
    return (dir,quant,rgb)

def calc_next_vertex(origin,data):
    dir = data[0]
    quant = data[1]
    rgb = data[2]
    if(dir == 'U'):
        return (origin[0]+quant,origin[1],rgb)
    elif(dir == 'D'):
        return (origin[0]-quant,origin[1],rgb)
    elif(dir == 'L'):
        return (origin[0],origin[1]-quant,rgb)
    else:
        return (origin[0],origin[1]+quant,rgb)

def getPolygonPoints(file):
    points = []
    boundary_points = 0
    points.append((0,0))
    try:
        with open(file, 'r') as file:
            for line in file:
                data = extractDataFromLine(line)
                boundary_points += data[1]
                points.append(calc_next_vertex(points[-1],data))
        points[0] = points[-1]

    except FileNotFoundError:
        print(f"The file '{file}' was not found.") 
    return points,boundary_points

def shoelace(points):
    left_sum = 0.0
    right_sum = 0.0

    for i in range(len(points)):
        j = (i + 1) % len(points)
        left_sum += points[i][0] * points[j][1]
        right_sum += points[j][0] * points[i][1]

    return 0.5 * abs(left_sum - right_sum)

def calculate_total_points(area,boundary_points,):
    interior_points = area - boundary_points/2.0 +1
    return interior_points + boundary_points


def main():
    #vertex,boundary_points = getPolygonPoints("aux.txt")
    vertex,boundary_points = getPolygonPoints("input.txt")
    print(vertex)
    area = shoelace(vertex)
    print(area)
    cubic_meters = calculate_total_points(area,boundary_points)
    print("Total digged cubic meters:" + str(cubic_meters))
 
if __name__ == "__main__":
    main()