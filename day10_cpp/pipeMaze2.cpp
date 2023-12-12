#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <stdexcept>
#include <cmath>

/*
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of chars in each line

The total cost of the algorithm is O(m*n). 

I had to search parts of this problem in internet since I didn't know there is a 
theorem for calculatin the area of irregular polygon. We are using this theorem 
to calculate the enclosed points inside the loop.

Pick's theorem
Area = points_inside + points_in_the_boundary/2 -1  ->
Area - points_in_the_boundary/2 + 1 = points_inside

So, we need the Area, that we are going to calculate using the Shoelace formula
to calculate the area of the polygon . For the points_in_the_boundary,
we are generating an array from previous function.
*/

std::tuple<int, int> getRowsAndColumns(const std::string& filePath) {
    // O(m*n)
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file: " << filePath << std::endl;
        return {-1, -1}; // Return a tuple with -1 to indicate an error
    }

    int lineCount = 0;
    int maxColumns = 0;

    std::string line;
    while (std::getline(inputFile, line)) {
        lineCount++;

        int currentColumns = 0;
        for (char c : line) {
            if (c != ' ') {
                currentColumns++;
            }
        }
        maxColumns = std::max(maxColumns, currentColumns);
    }

    inputFile.close();

    return {lineCount, maxColumns};
}

std::tuple<int, int> getStartingPositionAndFillMatrix(const std::string& filePath, std::vector<std::vector<char>>& matrix, int rows, int cols) {
    // O(m*n)
    int startingX = 0;
    int startingY = 0;

    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        int i = 0;
        int j = 0;
        while (getline(file, line)) {
            for (char character : line) {
                matrix[i][j] = character;
                if (matrix[i][j] == 'S') {
                    startingX = i;
                    startingY = j;
                }
                j++;
            }
            i++;
            j = 0;
        }
    } else {
        return {-1, -1};
        throw std::ios_base::failure("File not found or unable to open: " + filePath);
    }
    file.close();
    return {startingX, startingY};
}

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

Direction getNextDir(char pipe, Direction previousDir){
    if(pipe == '|' || pipe == '-' ){
        return previousDir;
    }
    if(pipe == 'L'){
        if(previousDir == DOWN)
            return RIGHT;
        else
            return UP;
    }
    if(pipe == 'J'){
        if(previousDir == RIGHT)
            return UP;
        else
            return LEFT;
    }
    if(pipe == '7'){
        if(previousDir == UP)
            return LEFT;
        else
            return DOWN;
    }
    if(pipe == 'F'){
        if(previousDir == UP)
            return RIGHT;
        else
            return DOWN;
    }
}
Direction getStartingPos(std::vector<std::vector<char>>& matrix, int posX,int posY){
    Direction dir;
    if(matrix[posX-1][posY] == '|' || matrix[posX-1][posY] == '7' || matrix[posX][posY] == 'F' ){
        dir = UP;
        return dir;
    }
    if(matrix[posX][posY+1] == '-' || matrix[posX][posY+1] == '7' ){
        dir = RIGHT;
        return dir;
    }
    if(matrix[posX+1][posY] == '|' || matrix[posX+1][posY] == 'L' || matrix[posX][posY] == 'J' ){
        dir = DOWN;
        return dir;
    }
    if(matrix[posX][posY-1] == '-' || matrix[posX][posY-1] == 'L' || matrix[posX][posY] == 'F' ){
        dir = LEFT;
        return dir;
    }
}

double fillBoundaryPointsVector(std::vector<std::vector<char>>& matrix, int startingX, int startingY,std::vector<std::tuple<int, int>>& bPoints ){
    //O(m*n)
    int nSteps = 0;
    bool endReached = false;
    bool returning = false;
    int posX = startingX;
    int posY = startingY;
    Direction previousDir;
    //Getting first movement
    Direction dir = getStartingPos(matrix, startingX, startingY);
    switch (dir) {
        case UP:
            posX = posX -1;
            break;
        case RIGHT:
            posY = posY +1;
            break;
        case DOWN:
            posX = posX +1;
            break;
        case LEFT:
            posY = posY -1;
            break;
    }
    nSteps++;
    bPoints.push_back(std::make_tuple(posX,posY));
    std::cout << "First dir: " << dir << std::endl;
    //Ending first move

    while(!endReached){
        char pipe = matrix[posX][posY];
        previousDir = dir;
        if(pipe == 'S'){
            endReached = true;
            return nSteps;
        }
        dir = getNextDir(pipe,previousDir);
        switch (dir) {
            case UP:
                posX = posX -1;
                break;
            case RIGHT:
                posY = posY +1;
                break;
            case DOWN:
                posX = posX +1;
                break;
            case LEFT:
                posY = posY -1;
                break;
        }
        nSteps++;
        bPoints.push_back(std::make_tuple(posX,posY));
    }

    return nSteps;
}

double shoelace(const std::vector<std::tuple<int, int>>& points) {
    double leftSum = 0.0;
    double rightSum = 0.0;

    for (int i = 0; i < points.size(); ++i) {
        int j = (i + 1) % points.size();
        leftSum += std::get<0>(points[i]) * std::get<1>(points[j]);
        rightSum += std::get<0>(points[j]) * std::get<1>(points[i]);
    }

    return 0.5 * std::abs(leftSum - rightSum);
}

double calculateInsidePoints(double area, double nBoundaryPoints){
    return (area - nBoundaryPoints/2.0 +1);
}

int main() {

    std::string filePath = "input.txt";
    int rows = 0;
    int cols = 0;
    int startingX = 0;
    int startingY = 0;
    double nBoundaryPoints = 0;
    double area = 0;
    double insidePoints = 0;

    //Generating a matrix and storing the values
    auto RowsAndColumns = getRowsAndColumns(filePath);
    rows = std::get<0>(RowsAndColumns);
    cols = std::get<1>(RowsAndColumns);
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols, '.'));
    auto startingPos =  getStartingPositionAndFillMatrix(filePath, matrix,rows, cols);
    startingX = std::get<0>(startingPos);
    startingY = std::get<1>(startingPos);

    //Filling the boundary points array
    std::vector<std::tuple<int, int>> bPoints;
    nBoundaryPoints = fillBoundaryPointsVector(matrix, startingX,startingY,bPoints);
    bPoints.pop_back();
    //Calculating area 
    area = shoelace(bPoints); 
    insidePoints = calculateInsidePoints(area, nBoundaryPoints);

    std::cout << "Rows and columns:" << rows << "  " << cols << std::endl;
    std::cout << "Starting pos:" << startingX << "  " << startingY  << std::endl;
    std::cout << "Total of external points: " << bPoints.size() << std::endl;
    std::cout << "SHOELACE: " << area  << std::endl;
    std::cout << "Inside points: " << insidePoints << std::endl;

    return 0;
}
