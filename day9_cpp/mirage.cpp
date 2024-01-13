#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

vector<int> createNextIteration(const vector<int> &prevIter) {
    vector<int> iter;
    for (size_t i = 0; i < prevIter.size() - 1; ++i) {
        iter.push_back( prevIter[i + 1] - prevIter[i] );
        cout << " " << prevIter[i + 1] - prevIter[i];
    }
    cout <<  endl;
    return iter;
}

bool iterateAgain(const vector<int> &vec){
    if(vec.size() == 1){
        return true;
    }
    for(int i = 0; i < vec.size() - 1; ++i){
        if((vec[i + 1] - vec[i]) != 0 ){
            return true;
        }
    }
    return false;
}

int calculateHistoricNumber(string line) {
    vector<int> lineOfNums;
    std::istringstream iss(line);
    int num;
    int numQuantity = 0;

    while (iss >> num) {
        lineOfNums.push_back(num);
        numQuantity++;
    }

    vector<vector<int>> historics;
    historics.push_back(lineOfNums);

    for (int num : historics[0]) {
        cout << num << " ";
    }
    cout <<  endl;

    int iterations = 0;
    //Generation the pyramidal structure that stores each iteration
    while ( iterateAgain(historics[iterations]) ) {
        historics.push_back(createNextIteration(historics[iterations]));
        iterations++;
    }

    //Now we are going all the way up storing the last calculated value
    int lastValue = 0;
    historics[iterations].push_back(0);
    for(int i = iterations-1; i > 0;i--){
        lastValue = historics[i].back() + historics[i-1].back();
        historics[i-1].push_back(lastValue);
    }

    return lastValue;
}

int main(void) {
    int total = 0;
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line)) {
        total += calculateHistoricNumber(line);
    }
    file.close();
    cout << "TOTAL:" << total << endl;

    return 0;
}