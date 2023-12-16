#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>

/*
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of chars in each line

The algorithm would have a cost of O(mn+mn+mn^2+mn) = O(3mn+mn^2) = O(mn^2) in temporal terms.
In spatial terms the cost is O(m*n). 
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

void fillMatrix(std::vector<std::vector<char>>& matrix, std::string& filePath){
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        int i = 0;
        int j = 0;
        while (getline(file, line)) {
            for (char character : line) {
                if (character != '.') {
                    matrix[i][j] = character;
                }
                j++;
            }
            i++;
            j = 0;
        }
    } else {
        throw std::ios_base::failure("File not found or unable to open: " + filePath);
    }
    file.close();
}

void printMatrix(const std::vector<std::vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char element : row) {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void moveRocksNord(std::vector<std::vector<char>>& matrix, int nElements, int rows){
    //O(m*n*n)
    int rowCounter = 0;
    std::vector<int> rockPosition(nElements, 0);
    bool slide = true;
    while(slide){
        slide = false;
        for (int i = 1; i < rows;i++ ) {
            for (int j = 0; j < nElements; j++ ) {
                if(matrix[i-1][j] == '.' && matrix[i][j] != '#' && matrix[i][j] != '.'){
                    matrix[i-1][j] = matrix[i][j];
                    matrix[i][j] = '.';
                    slide = true;
                }
            }
        }
        
    }
}

int countTotalLoad(std::vector<std::vector<char>>& matrix, int nElements, int rows){
    int totalLoad = 0;
    for (int i = 0; i < rows;i++ ) {
            for (int j = 0; j < nElements; j++ ) {
                if(matrix[i][j]  == 'O'){
                    totalLoad+= rows - i;
                }   
            }
    }
    return totalLoad;
}

int main(){
    std::string inputFile = "input.txt";
    std::tuple<int,int> elements = getRowsAndColumns(inputFile);
    int lines = std::get<0>(elements);
    int nElements = std::get<1>(elements);
    std::cout << "Lines " << lines << std::endl;
    std::vector<std::vector<char>> matrix(lines, std::vector<char>(nElements, '.'));
    fillMatrix(matrix, inputFile);
    moveRocksNord(matrix,nElements, lines);
    //printMatrix(matrix);
    int totalLoad = countTotalLoad(matrix,nElements, lines);
    std::cout << "Total load: " << totalLoad << std::endl;

    return 0;
}