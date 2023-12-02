#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <tuple>
#include <vector>
using namespace std;

// bool possibleSet(const string& set){
//     for(char element : set){
        
//     }
//     return true;
// }

std::tuple<int, string>  getGameNumber(const string& game){
    int firstSpacePos = 0;
    int colonPos = 0;
    int iterator = 0;
    for(char element : game){
        if(element == ' '){
            firstSpacePos = iterator;
        }
        if(element == ':'){
            colonPos = iterator;
            break;
        }
        iterator++; 
    }
    int gameNumber = std::stoi(game.substr(firstSpacePos,colonPos - firstSpacePos));
    return std::make_tuple(gameNumber,game.substr(colonPos+1,game.length())); 
} 

tuple<bool, int> isValidGame(const string& games){
    vector<string> words;
    string word;
    int iterator = 0; 
    int num = 0;
    string colour = "";
    std::map<std::string, int> bag = 
    {
        {"red",12},
        {"green",13},
        {"blue",14}
    };
    
     for (char nchar : games) {
        if (nchar != ' ' && nchar != ',' && nchar != ';'  && nchar != ':') {
            word += nchar;
        } else {
            words.push_back(word);
            word.clear();           
            iterator++;
        }
    }
    words.push_back(word);
    //Now we have a splitted vector obtained from the string
    int counter = 2;
    for(auto iter = words.begin()+2; iter != words.end(); iter=iter+3){
        num = std::stoi(words[counter+1]);
        colour = words[counter+2];
        if(num > bag[colour]){
            return make_tuple(false, std::stoi(words[1]));
        }
        counter+= 3;
    }
    
    return make_tuple(true, std::stoi(words[1]));

}

int possibleGamesIDSum(std::string pathToInput){
    string line;
    ifstream input(pathToInput);
    int sum = 0;

    if(input.is_open()){
        while (getline(input, line)) {
            auto result = isValidGame(line);
            bool isValid = get<0>(result);
            int gameID = get<1>(result);
            if(isValid)
                sum+= gameID;
        }
    }
    else{
            throw std::ios_base::failure("File not found: " + pathToInput);
    }
    return sum;
}

int main(){
    std::cout << "Sum of valid IDs-> " << possibleGamesIDSum("input.txt") << std::endl;
    return 0;
}