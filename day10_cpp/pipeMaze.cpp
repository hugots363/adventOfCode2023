#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <stdexcept>

/*
TODO
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of numbers in each line

Now the cost of my algorithm is similar: O(2m+n+m(2n+2nlogn)) =  O(n+2m(1+n+nlogn)) = O(mnlogn). The problem I don't
know how to solve at the moment (if it is possible) is how to store the generated copies of the tickets without having
to generate a vector with one entry for each line of the input file.

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

int calculateTotalSteps(std::vector<std::vector<char>>& matrix, int startingX, int startingY){
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
    }

    return nSteps;
}

int main() {

    std::string filePath = "input.txt";
    int rows = 0;
    int cols = 0;
    int startingX = 0;
    int startingY = 0;
    int nSteps = 0;

    //Generating a matrix and storing the values
    auto RowsAndColumns = getRowsAndColumns(filePath);
    rows = std::get<0>(RowsAndColumns);
    cols = std::get<1>(RowsAndColumns);
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols, '.'));
    auto startingPos =  getStartingPositionAndFillMatrix(filePath, matrix,rows, cols);
    startingX = std::get<0>(startingPos);
    startingY = std::get<1>(startingPos);

    nSteps = calculateTotalSteps(matrix, startingX,startingY);

    std::cout << "Rows and columns:" << rows << "  " << cols << std::endl;
    std::cout << "Starting pos:" << startingX << "  " << startingY  << std::endl;
    std::cout << "Total steps: " << nSteps/2 << std::endl;
    return 0;
}
