#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> createNextIteration(const vector<int> &prevIter) {
    vector<int> iter;
    for (size_t i = 0; i < prevIter.size() - 1; ++i) {
        int difference = prevIter[i + 1] - prevIter[i];
        iter.push_back(difference);
        cout << " " << difference;
    }
    cout << endl;
    return iter;
}

bool iterateAgain(const vector<int> &vec) {
    if (vec.size() == 1) {
        return true;
    }
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        if ((vec[i + 1] - vec[i]) != 0) {
            return true;
        }
    }
    return false;
}

int calculateHistoricNumber(const string &line) {
    vector<int> lineOfNums;
    istringstream iss(line);
    int num;

    while (iss >> num) {
        lineOfNums.push_back(num);
    }

    vector<vector<int>> historics;
    historics.push_back(lineOfNums);

    for (int num : historics[0]) {
        cout << num << " ";
    }
    cout << endl;

    int iterations = 0;
    while (iterateAgain(historics[iterations])) {
        historics.push_back(createNextIteration(historics[iterations]));
        iterations++;
    }

    int lastValue = 0;
    historics[iterations].push_back(0);
    for (int i = iterations - 1; i > 0; i--) {
        lastValue = historics[i].back() + historics[i - 1].back();
        historics[i - 1].push_back(lastValue);
    }

    return lastValue;
}

int main() {
    int total = 0;
    ifstream file("input.txt");
    string line;

    while (getline(file, line)) {
        total += calculateHistoricNumber(line);
    }

    file.close();
    cout << "TOTAL:" << total << endl;

    return 0;
}
