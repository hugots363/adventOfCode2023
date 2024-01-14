#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of numbers in each line

This problem has an algorithmic cost of O(mn^2). This is a problem since the running time of the code increases quadratically.

*/

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

string invertNumbers(const string& input) {
    vector<string> numbers;
    size_t start = 0;
    size_t end = input.find(' ');

    while (end != string::npos) {
        numbers.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(' ', start);
    }

    numbers.push_back(input.substr(start, end));

    reverse(numbers.begin(), numbers.end());

    string reversedString;
    for (const string& number : numbers) {
        reversedString += number + " ";
    }

    reversedString.pop_back();

    return reversedString;
}

int calculateHistoricNumber(const string& line) {
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
    
    for (int i = iterations; i > 0; i--) {
        int a = historics[i].back();
        int b = historics[i - 1].back();
        lastValue = a + b;
        historics[i - 1].push_back(lastValue);
    }

    return lastValue;
}

int main() {
    int total = 0;
    ifstream file("input.txt");
    string line;

    while (getline(file, line)) {
        total += calculateHistoricNumber(invertNumbers(line));
    }

    file.close();
    cout << "TOTAL:" << total << endl;

    return 0;
}
