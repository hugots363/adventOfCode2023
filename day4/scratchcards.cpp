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

Using bruteforce would have a cost of O(m*(n+n*n)) = O(mn+ mn^2 ). Instead we are going to use an approach 
where we use first a  Quicksort algorithm and then a binary search. This Quicksort+BinarySearch combined algorithm would have a computational cost
of O(m(n+nlogn+logn)) = O(m*n*logn). O(m*n*logn) < O(mn+ mn^2 ), we are using Quicksort+BinarySearch approach.

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
    
    cout << "Line>> " << str << endl;
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
    //int prize = getPrizeSum("input.txt");
    int prize = getPrizeSum("input.txt");
    std::cout << "Sum of all the prizes-> " << prize << std::endl;

    //vector<int> aux = {0,1,2,3};
    //std::cout << isValueInVector(aux, 0, 3,2) << std::endl;
    //tuple<int,int> sizes = getVectorsSize("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53");
    //std::cout << "Vector sizes-> " << get<0>(sizes) << " " << get<1>(sizes)<< std::endl;
   // tuple<int,int> sizes2 = getVectorsSize("Card 151: 67 29  3 38 79 20  8 70 44 53 | 10 20 13 21 70 53 59 92  9 56 79  8  3 78 75 42 38 41 44 80 29 48 47 32  7");
    //std::cout << "Vector sizes-> " << get<0>(sizes2) << " " << get<1>(sizes2)<< std::endl;
    //string test = "Card   1: 81  1 43 40 49 51 38 65 36  4 | 21 15  1 43 60  9 83 81 35 49 40 38 82 65 20  4 58 94 16 89 84 10 77 48 76";
    //tuple<int,int> sizes = getVectorsSize(test);
    //std::cout << "Vector sizes-> " << get<0>(sizes) << " " << get<1>(sizes)<< std::endl;

    return 0;
}