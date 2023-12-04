#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <fstream>
using namespace std;

/*
Theoretical approach
Terms:
m = number of lines in the file
n = quantity of numbers in each line

Now the cost of my algorithm is similar: O(2m+n+m(2n+2nlogn)) =  O(n+2m(1+n+nlogn)) = O(mnlogn). The problem I don't
know how to solve at the moment (if it is possible) is how to store the generated copies of the tickets without having
to generate a vector with one entry for each line of the input file.

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

int numberOfLines(const string& filePath){
     std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file: " << filePath << std::endl;
        return -1; // Return -1 to indicate an error
    }

    int lineCount = 0;
    std::string line;

    while (std::getline(inputFile, line)) {
        lineCount++;
    }

    inputFile.close();

    return lineCount;
}

int getAparitionsFromVectors(vector<int>& vectNum,vector<int>& vectPrized,int numbersLen, int prizedLen){
    int apparitions = 0;
    int left = 0;
    int position = 0;


    for (int i = 0; i < numbersLen; ++i) {
        position = isValueInVector(vectPrized,left,prizedLen, vectNum[i]);
        if(position != -1){
            apparitions++;
            left = position+1;
        }
    }
    return apparitions;
}

int getConsumedScratchcards(const string& path){
    string line;
    ifstream input(path);
    int numbersLen = 0;
    int prizedLen = 0;
    int apparitions = 0;
    int cardNumber = 1;
    int totalScratchedCards = 0;
    int fileLen = 0;

    //Not so proud of this part, the vector is going to kill the performance
    fileLen = numberOfLines(path);
    //Index is the card, and value is the number of copies, starting from 1, 0 is ignored
    std::vector<int> copiesOfCard(fileLen+1, 0);

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
            totalScratchedCards += 1;
            //Each apparition is a new scratchcard
            if(apparitions > 0){
                for(int i = cardNumber+1; i <= std::min(cardNumber  + apparitions, fileLen); ++i){
                    copiesOfCard[i]++;
                }
            }
            //Now checking my copies
            if(copiesOfCard[cardNumber] > 0){
                for(int i = cardNumber+1; i <= std::min(cardNumber  + apparitions, fileLen); ++i){
                    copiesOfCard[i] += copiesOfCard[cardNumber];
                }
                //Scratching the copies of the card that i'm playing with
                totalScratchedCards += copiesOfCard[cardNumber];
                copiesOfCard[cardNumber] = 0;
            }
            cardNumber++;
        }
    }
    else{
            throw std::ios_base::failure("File not found: " + path);
    }
    return totalScratchedCards;
}

int main(){

    int cards = getConsumedScratchcards("input.txt");
    std::cout << "Total num of scratchcards-> " << cards << std::endl;

    return 0;
}