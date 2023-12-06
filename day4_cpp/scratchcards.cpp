#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <cctype>
using namespace std;

/*
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of numbers in each line

Using bruteforce would have a cost of O(m*(n+n*n)) = O(mn+ mn^2 ) = O(mn^2). Instead we are going to use an approach 
where we use first a  Quicksort algorithm and then a binary search. This Quicksort+BinarySearch combined algorithm would have a computational cost
of O(n+m(n+nlogn+nlogn) = O(mn+2mnlogn)= O(mnlogn) . O(m*n*logn) < O(mn^2 ), we are using Quicksort+BinarySearch approach.

Implementation specifics

*/

tuple<int,int> getVectorsSize(const string& str){
    bool numbers = false;
    bool prizeNumbers = false;
    int totalNumbers = 0;
    int totalPrized = 0;
    bool inNumber = false;
    bool inPrized = false;

    for (char character : str){
        if(!numbers && !prizeNumbers && character == ':' ){
            numbers = true;
        }
        if(numbers){
            if(isdigit(character) && !inNumber){
                totalNumbers++;
                inNumber = true;
            }
            else if (!isdigit(character)) {
                inNumber = false;
            }
        }
        if(character == '|'){
            numbers = false;
            prizeNumbers = true;
            inNumber = false;
        }
        if(prizeNumbers){
            if(isdigit(character) && !inPrized){
                totalPrized++;
                inPrized = true;
            }
            else if (!isdigit(character)) {
                inPrized = false;
            }
        }
    } 

    return make_tuple(totalNumbers, totalPrized);
}

void fillVectorsOrdered(vector<int>& vectNum,vector<int>& vectPrized,const string& str,int numbersLen, int prizedLen){
    bool numbers = false;
    bool prizeNumbers = false;
    int num = 0;
    int prizedNum = 0;
    string auxNum = "";
    bool numberToPlace = false;
    int counter = 0;
    
    for (char character : str){
        if(!numbers && !prizeNumbers && character == ':' ){
            numbers = true;
        }
        if(numbers){
            if(isdigit(character)){
                auxNum+= character;
                numberToPlace = true;
            }
            else{
                if(numberToPlace){
                    vectNum[counter] = stoi(auxNum);
                    counter++;
                    auxNum.clear();
                    numberToPlace = false;
                }
                
            }
        }
        if(character == '|'){
            numbers = false;
            prizeNumbers = true;
            numberToPlace = false;
            counter = 0;
        }
        if(prizeNumbers){
            if(isdigit(character)){
                auxNum+= character;
                numberToPlace = true;
            }
            else{
                if(numberToPlace){
                    vectPrized[counter] = stoi(auxNum);
                    counter++;
                    auxNum.clear();
                    numberToPlace = false;
                }
                
            }
        }    
    }

    if (!auxNum.empty()) {
        vectPrized[counter] = stoi(auxNum);
    }

    //Ordering vectors
    sort(vectNum.begin(), vectNum.end());
    sort(vectPrized.begin(), vectPrized.end());

}

//Binary search
int isValueInVector(vector<int>& vect, int left, int right,int key){
    while(left <= right){
        int mid = left + (right - left)/2;
        if(vect[mid] == key){
            return mid;
        }
        if(vect[mid] < key){
            left = mid+1;
        }
        else{
            right = mid -1;
        }
    }
    return -1;
}

int getAparitionsFromVectors(vector<int>& vectNum,vector<int>& vectPrized,int numbersLen, int prizedLen){
    int apparitions = 0;
    int left = 0;
    int position = 0;


    for (int i = 0; i < numbersLen; ++i) {
        position = isValueInVector(vectPrized,left,prizedLen, vectNum[i]);
        //std::cout << "Number : "<< vectNum[i]  << " Position-> " << position << std::endl;
        if(position != -1){
            std::cout << "$$Apparition number$$ " << vectNum[i] << std::endl;
            apparitions++;
            left = position+1;
        }
    }
    return apparitions;
}

int getPrizeSum(string path){
    string line;
    ifstream input(path);
    int points = 0;
    int numbersLen = 0;
    int prizedLen = 0;
    int apparitions = 0;

    //Getting the needed length for the vectors
    std::ifstream file(path);
    if(file.is_open()){
        string firstLine;
        getline(file, firstLine);
        tuple<int,int> sizes = getVectorsSize(firstLine);
        numbersLen = get<0>(sizes);
        prizedLen = get<1>(sizes);
    }else{
        throw std::ios_base::failure("File not found or unable to open: " + path);
    }

    //Generating vectors, always keeping same length
    vector<int> orderedNumbers(numbersLen);
    vector<int> orderedPrized(prizedLen);


    //Loop
    if(input.is_open()){
        while (getline(input, line)) {
            fillVectorsOrdered(orderedNumbers,orderedPrized, line, numbersLen,prizedLen);
            apparitions = getAparitionsFromVectors(orderedNumbers,orderedPrized,numbersLen,prizedLen);
            std::cout << "Apparitions-> " << apparitions << std::endl;
            //Get the number of points using the number of  apparitions
            if(apparitions != 0){
                points+= std::pow(2, apparitions-1);
            }
            apparitions = 0;
            std::cout << "Points-> " << points << std::endl;
        }
    }
    else{
            throw std::ios_base::failure("File not found: " + path);
    }
    return points;
}

int main(){
    int prize = getPrizeSum("input.txt");
    std::cout << "Sum of all the prizes-> " << prize << std::endl;

    return 0;
}