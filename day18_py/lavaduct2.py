'''
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of chars in each line

The total cost of the algorithm is O(mn)

Pick's theorem
Area = points_inside + points_in_the_boundary/2 +1  ->
points_inside = Area -points_in_the_boundary/2 -1

The result for the problem is the sum of inside and boundary points.

So, we need the Area, that we are going to calculate using the Shoelace formula.
After that, we will just use the boundary numer of points that is given in the input
to calculate the number of points inside. Then, we will just sum inside and boundary points.
'''

directions = {"0":'R',"1":'D',"2":'L',"3":'U'}

def get_init(file_path):
    try:
        with open(file_path, 'r') as file:
            rows = file.readlines()
            return (len(rows),0)
            
    except FileNotFoundError:
        return None  

def calc_next_vertex(origin,data):
    dir = data[0]
    quant = data[1]
    if(dir == 'U'):
        return (origin[0]+quant,origin[1])
    elif(dir == 'D'):
        return (origin[0]-quant,origin[1])
    elif(dir == 'L'):
        return (origin[0],origin[1]-quant)
    else:
        return (origin[0],origin[1]+quant)

def extract_rgb_data(line):
    parts = line.split() 
    rgb = parts[2][2:-1]
    dir = directions[rgb[-1]]
    quant = int(rgb[0:5], 16)
    return (dir,quant)

def getPolygonPoints(file):
    points = []
    boundary_points = 0
    points.append((0,0))
    try:
        with open(file, 'r') as file:
            for line in file:
                rgb_data = extract_rgb_data(line)
                points.append(calc_next_vertex(points[-1],rgb_data))
                boundary_points += rgb_data[1]
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

def calculate_total_points(area,boundary_points):
    interior_points = area + 1.0 - (boundary_points*0.5) 
    print("interior_points: "+str(interior_points))
    return interior_points + boundary_points


def main():
    vertex,boundary_points = getPolygonPoints("input.txt")
    area = shoelace(vertex)
    print(vertex)
    print("ARea "+ str(area) )
    print("Boundary P: " +str(boundary_points))
    cubic_meters = calculate_total_points(area,boundary_points)
    print("Total digged cubic meters: " + str(cubic_meters))
 
if __name__ == "__main__":
    main()