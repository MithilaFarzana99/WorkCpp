#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <cmath>

bool IsValidHand(const std::vector<std::string>& hand) {
    if (hand.size() != 13) {
        return false;
    }
    
    std::set<char> suits;
    for (const auto& card : hand) {
        suits.insert(card.back());
    }

    if (suits.size() == 1) {
        return false;
    }
    return true;
}

int CalculateSpadesStrength(const std::vector<std::string>& spades) {
    std::vector<std::string> high_cards = {"A", "K", "Q", "J"};
    int strength = 0;
    for (const auto& card : spades) {
        std::string rank = card.size() == 3 ? card.substr(0, 2) : card.substr(0, 1);
        if (std::find(high_cards.begin(), high_cards.end(), rank) != high_cards.end()) {
            strength++;
        }
    }
    return strength;
}

int CalculateOtherSuitsStrength(const std::vector<std::string>& hand) {
    int strength = 0;
    for (char suit : {'H', 'D', 'C'}) {
        std::vector<std::string> suit_cards;
        for (const auto& card : hand) {
            if (card.back() == suit) {
                suit_cards.push_back(card);
            }
        }

        if (std::find(hand.begin(), hand.end(), "A" + std::string(1, suit)) != hand.end()) {
            strength += 1;
        }

        if (std::find(hand.begin(), hand.end(), "K" + std::string(1, suit)) != hand.end() && suit_cards.size() >= 3) {
            strength += 0.75;
        }
    }
    return strength;
}

int EstimateBid(const std::vector<std::string>& hand) {
        if (!IsValidHand(hand)) {
            return -1;
        }
        
        std::vector<std::string> spades;
        for (const auto& card : hand) {
            if (card.back() == 'S') {
                spades.push_back(card);
            }
        }

        double total_strength = CalculateSpadesStrength(spades) + CalculateOtherSuitsStrength(hand);
        if (total_strength < 2) {
            return 0;
        }
        return static_cast<int>(std::round(total_strength));
}

#include <cassert>

int main() {
    
    assert(EstimateBid({"AS", "KS", "QS", "JS", "10D", "9D", "8C", "7C", "AD", "5H", "4D", "KC", "2H"}) == 5);
    
    
    assert(EstimateBid({"2S", "3S", "4S", "5S", "6S", "7H", "8H", "9H", "2D", "3D", "4D", "5D", "6D"}) == 0);

    
    assert(EstimateBid({"AS", "KS", "QS", "JS", "10S", "9S", "8S", "7S", "6S", "5S", "4S", "3S", "2S"}) == -1);
    
    
    assert(EstimateBid({"AS", "KS", "QS", "JS"}) == -1);
    
    assert(EstimateBid({"AS", "KS", "6S", "JD", "10D", "9D", "8C", "7C", "AD", "5H", "QH", "KC", "2H"}) == 3);
    
    assert(EstimateBid({"AS", "KS", "QS", "JD", "10D", "9D", "8C", "7C", "AH", "5H", "4H", "KH", "3H"}) == 4);
    
    assert(EstimateBid({"3S", "4S", "9S", "AD", "KD", "9D", "8C", "7C", "AC", "5H", "4D", "5D", "7D"}) == 2);
    

    return 0;
}


