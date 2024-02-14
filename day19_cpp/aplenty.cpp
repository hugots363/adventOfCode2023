#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>
#include <regex>

/*
Theoretical approach

Terms:
n = quantity of chars in the line
m = number of lines

The algorithm would have a cost of O(mn)
*/

using namespace std;

tuple<string,vector<string>> extractList(const string &line){
    string instruction;
    vector<string> words;

    for(char character : line ){
        if(character == '{' || character == '}' || character == ','){
            words.emplace_back(instruction);
            instruction.clear();
        }
        else{
            instruction+= character;
        }
    }
    string key = words[0];
    words.erase(words.begin());
    return {key,words};
}

tuple<int,int,int,int> extractRatings(const string &line){
    regex pattern("\\{x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)\\}");
    smatch matches;

    if (regex_search(line, matches, pattern)) {
        if (matches.size() == 5) {
            return make_tuple(stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), std::stoi(matches[4]));
        }
    }
    exit(0);
}

bool isEvaluation(const string& word){
    if(word[1] == '>' || word[1] == '<' ){
        return true;
    }
    return false;
}

string checkCondition(const string& word,const tuple<int,int,int,int> &parts){
    map<string,int> partsSpec {{"x",0},{"m",1},{"a",2},{"s",3}};
    int pos = partsSpec[word.substr(0,1)];
    int partValue;
    switch(pos) {
        case 0: partValue = get<0>(parts); break;
        case 1: partValue = get<1>(parts); break;
        case 2: partValue = get<2>(parts); break;
        case 3: partValue = get<3>(parts); break;
    }
    string comparator = word.substr(1,1);
    bool conditionMeet = false;
    int conditionValue = 0;
    string nextWorkflow = "";
    bool isConditionValue = true;

    string auxNum = "";
    for (int i = 2; i < word.length(); ++i) {
        if(word[i] == ':'){
            isConditionValue = false;
            conditionValue = stoi(auxNum);
            continue;
        }
        if(isConditionValue){
            auxNum+= word[i];
        }
        else{
            nextWorkflow += word[i];
        }
    }

    if(comparator == ">"){
        if(partValue > conditionValue){return nextWorkflow;}
    }
    else{
        if(partValue < conditionValue){return nextWorkflow;}
    }
    
    return "failed";
    
}

 int calculateSum(const string& filePath) {
    string line;
    ifstream file(filePath);
    bool ratingsPart = false;
    string key; 
    //Data structures
    map<string, vector<string>> workflows;
    vector<tuple<int,int,int,int>> ratings;

    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filePath << std::endl;
        exit(0);
    }

    while (getline(file, line)) {
        if(!ratingsPart && line.empty()){
            ratingsPart = true;
            continue;
        }
        if(!ratingsPart){
            auto tuple = extractList(line);
            workflows[get<0>(tuple)] = get<1>(tuple);
        }
        else{
            ratings.emplace_back(extractRatings(line));
        }

    }

    file.close();

    //Calculate the sum of accepted
    int total = 0;
    for(auto rating : ratings){
        string actualRating = "in";
        string currentWord = workflows[actualRating][0];
        int pos = 0;
        while(true){
            if(currentWord == "A"){
                total += get<0>(rating)+get<1>(rating)+get<2>(rating)+get<3>(rating);
                pos = 0;
                break;
            }
            if(currentWord == "R"){
                pos = 0;
                break;
            } 
            if(isEvaluation(currentWord)){
                string nextWorkflow = checkCondition(currentWord,rating);
                if(nextWorkflow != "failed" ){
                    actualRating = nextWorkflow;
                    if(actualRating != "A" && actualRating != "R"){
                        currentWord = workflows[actualRating][0];
                    }
                    else{
                        currentWord = nextWorkflow;
                    }
                    pos = 0;
                }
                else{
                    pos++;
                    currentWord = workflows[actualRating][pos];
                }
            }
            else{
                actualRating = currentWord;
                currentWord = workflows[actualRating][0];
                pos = 0;
            }

        }
    }

    return total;
}

int main(){

    std::string inputFile = "input.txt";
    int total = calculateSum(inputFile);
    cout << "Total: " << total << endl; 
    return 0;
}