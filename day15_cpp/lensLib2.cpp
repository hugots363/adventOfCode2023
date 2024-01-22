#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <string>
#include <fstream>

/*
Theoretical approach
Terms:
m = number of words (like for example gjtq=1) in the input file

The algorithm would have a cost of O(m^2);
*/

using namespace std;

int hashing(string word){
    int total = 0;
    for(const auto character : word){
        total= ((total+int(character))*17)%256;
    }
    return total;
}

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(){
    vector<vector<string>> boxes(256);
    unordered_map<string, int> focal_lengths;

    string filePath = "input.txt";
    ifstream inputFile(filePath);
    int total = 0;

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file: " << filePath << std::endl;
        exit(0);
    }

    string line;
    getline(inputFile, line);
    vector<string> inputs = split(line, ',');

    for (const auto& step : inputs) {
        if (step.find('=') != string::npos) {
            string label = step.substr(0, step.find('='));
            int focal_length = stoi(step.substr(step.find('=') + 1));
            int box = hashing(label);
            focal_lengths[label] = focal_length;

            auto it = find(boxes[box].begin(), boxes[box].end(), label);
            if (it != boxes[box].end()) {
                *it = label;
            } else {
                boxes[box].push_back(label);
            }
        }

        if (step.find('-') != string::npos) {
            string label = step.substr(0, step.size() - 1);
            int box = hashing(label);
            boxes[box].erase(remove(boxes[box].begin(), boxes[box].end(), label), boxes[box].end());
        }
    }

    int solution2 = 0;
    for (int box_index = 0; box_index < boxes.size(); ++box_index) {
        for (int slot_index = 0; slot_index < boxes[box_index].size(); ++slot_index) {
            string label = boxes[box_index][slot_index];
            solution2 += (box_index + 1) * (slot_index + 1) * focal_lengths[label];
        }
    }

    cout << "Solution 2: " << solution2 << endl;

    return 0;
}