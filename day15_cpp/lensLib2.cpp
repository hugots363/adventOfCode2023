#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm> 

/*
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of chars in each line

The algorithm would have a cost of O(mn+mn+mn^2+mn) = O(3mn+mn^2) = O(mn^2) in temporal terms.
In spatial terms the cost is O(m*n). 
*/

using namespace std;

int myHashing(string word){
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
        exit(1);
    }

    map<int, vector<tuple<string, int>>> boxes;
    for (int i = 0; i < 255; ++i) {
        boxes[i] = {};
    }

    string line;
    string hash;
    int storedBox;
    int lensPos;
    bool addingLens;
    std::getline(inputFile, line);
    cout << line << endl;

    for(const auto character : line){
        if(character == ','){
            if(addingLens){
                auto it = find_if(boxes[storedBox].begin(), boxes[storedBox].end(),
                       [hash](const auto& tuple) {
                           return get<0>(tuple) == hash;
                       });
                if (it != boxes[storedBox].end()){
                    cout << "found-------------------------"<<endl;
                    get<1>(*it) = lensPos;
                }
                else{
                    boxes[storedBox].emplace_back(make_tuple(hash,lensPos));
                }
                 
            }
            else{
                if (boxes.find(storedBox) != boxes.end() && !boxes[storedBox].empty()) {
                    boxes[storedBox].erase(boxes[storedBox].begin());
                }
            }
            hash = "";
        }
        else{
            if(character == '='|| character == '-'){
                if(character == '='){addingLens = true;}
                else{addingLens = false;}
                storedBox = myHashing(hash);
            }
            else{
                if(!isdigit(character)){
                    hash += character;
                }
                else{
                    lensPos =   character -'0';
                }
            }
        }        
    }
    boxes[storedBox].emplace_back(make_tuple(hash, addingLens ? lensPos : 0)); 

    for (const auto& outerEntry : boxes) {
        std::cout << "Outer Key: " << outerEntry.first << std::endl;
        for (const auto& innerEntry : outerEntry.second) {
            std::cout << "  Inner Key: " << get<0>(innerEntry)
                      << ", Value: " << get<1>(innerEntry) << std::endl; 
        }
    }

    inputFile.close();

    return total;
}

int main(){
    std::string inputFile = "aux.txt";
    int total = getTotalHashes(inputFile);
    cout << "Total: " << total << endl; 
    cout << "hashing: " << myHashing("rn=1") << endl; 
    return 0;
}