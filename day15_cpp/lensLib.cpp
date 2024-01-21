#include <iostream>
#include <string>
#include <fstream>

/*
Theoretical approach

Terms:
n = quantity of chars in the line
m = max length in the words separated by comma (",")

The algorithm would have a cost of O(mn).
*/

using namespace std;

int hashing(string word){
    int total = 0;
    for(const auto character : word){
        total= ((total+int(character))*17)%256;
    }
    return total;
}

 int getTotalHashes(const string& filePath) {
    ifstream inputFile(filePath);
    int total = 0;

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file: " << filePath << std::endl;
        exit(0);
    }

    string line;
    string hash;
    std::getline(inputFile, line);
    cout << line << endl;
    for(const auto character : line){
        if(character != ','){
            hash+= character;
        }
        else{
            total += hashing(hash);
            hash = "";
        }        
    }
    total += hashing(hash);

    inputFile.close();

    return total;
}

int main(){
    std::string inputFile = "input.txt";
    cout << "Total: " << getTotalHashes(inputFile) << endl; 
    return 0;
}