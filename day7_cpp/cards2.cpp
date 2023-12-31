#include <iostream>
#include <string>
#include<map>
#include <algorithm>
#include <vector>
#include <fstream>

/*
Theoretical approach (TODO)
Terms:
m = 
n = 


*/


enum Type {
    HighCard,
    Pair,
    TwoPair,
    ThreeOfKind,
    FullHouse,
    FourOfKind,
    FiveOfKind
};

const std::map<char, int> cardVal = {
        {'A', 14},
        {'K', 13},
        {'Q', 12},
        {'T', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2},
        {'J', 1}
    };

struct Hand{
    std::string hand;
    Type type;
    int bet;
};

bool compare(const std::pair<char, int>& a, const std::pair<char, int>& b) {
    return a.second > b.second;
}

int extractJokers(std::string &hand){
    int cont = 0;
    for(auto it = hand.begin(); it != hand.end();){
        if(*it == 'J'){
            cont++;
            it = hand.erase(it);
        }
        else{
            it++;
        }
    }
    return cont;
}


Type calculateHandType(const std::string &hand){
    std::map<char,int> valCount;
    std::string newHand = hand;
    int totalJokers = extractJokers(newHand);

    for(char val : newHand){
        valCount[val]++;
    }
    std::vector<std::pair<char, int>> count_vec(valCount.begin(), valCount.end());

    std::sort(count_vec.begin(), count_vec.end(), compare); 

    int most_repeated = 0;
    auto it = count_vec.begin();
    if(!newHand.empty()){
        most_repeated = it->second + totalJokers;
    }
    else{
        return Type::FiveOfKind;
    }

    switch(most_repeated){
        case 5:
            return Type::FiveOfKind;
        case 4:
            return Type::FourOfKind;
        case 3:
            it++;
            if(it->second == 2){return FullHouse;}
            return Type::ThreeOfKind;
        case 2:
            it++;
            if(it->second == 2){return TwoPair;}
            return Type::Pair;
        default:
            return Type::HighCard;
    }
}

int getHandBet(const std::string &hand){
    bool nowNumber = false;
    std::string num;
    for(char character : hand){
        if(character ==  ' '){
            nowNumber = true;
        }
        if(nowNumber){
            num+= character;
        }
    }
    return std::stoi(num);

}

std::string getCards(const std::string &hand){
    std::string myHand;
    for(char character : hand){
        if(character ==  ' '){
            return myHand;
        }
        myHand += character;
    }
    return myHand;
}

void placeHandByType(const std::string &hand,std::vector<std::vector<Hand>> &orderedHands){
    Hand currentHand;
    currentHand.bet = getHandBet(hand);
    currentHand.hand = getCards(hand);
    currentHand.type = calculateHandType(currentHand.hand);

    switch(currentHand.type){
        case HighCard:
            orderedHands[0].push_back(currentHand);
            break;
        case Pair:
            orderedHands[1].push_back(currentHand);
            break;
        case TwoPair:
            orderedHands[2].push_back(currentHand);
            break;
        case ThreeOfKind:
            orderedHands[3].push_back(currentHand);
            break;
        case FullHouse:
            orderedHands[4].push_back(currentHand);
            break;
        case FourOfKind:
            orderedHands[5].push_back(currentHand);
            break;
        default:
            orderedHands[6].push_back(currentHand);
            break;
    }

}

bool compareHands(const Hand& hand1, const Hand& hand2) {
    const std::string& str1 = hand1.hand;
    const std::string& str2 = hand2.hand;

    for (size_t i = 0; i < str1.size(); ++i) {
        char card1 = str1[i];
        char card2 = str2[i];

        if (cardVal.at(card1) > cardVal.at(card2)) {
            return true;
        } else if (cardVal.at(card1) < cardVal.at(card2)) {
            return false;
        }
    }

    return false;
}


int main() {
    std::string filename = "input.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open: " << filename << std::endl;
        return 1;
    }

    std::string hand;
    std::vector<std::vector<Hand>> orderedHands(7,std::vector<Hand>());
    while (std::getline(file, hand)) {
        placeHandByType(hand,orderedHands);
    }

    //Now traversing and ordering all hand types
    for (auto& category : orderedHands) {
        std::sort(category.begin(), category.end(), compareHands);
    }

    int cont = 1;
    int totalSum = 0;
    for (const auto& category : orderedHands) {
        for (auto it = category.rbegin(); it != category.rend(); ++it) {
            const auto& hand = *it;
            totalSum += hand.bet * cont;
            cont++;
        }
    }

    std::cout << std::endl;
    std::cout << "Total wins: " << totalSum << std::endl;

}
