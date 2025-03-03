#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_set>

std::vector<std::string> RuffleShuffle(int seed) {
    const std::vector<char> suits = {'S', 'H', 'D', 'C'};
    const std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::vector<std::string> deck;
    for (char suit : suits) {
        for (const auto& rank : ranks) {
            deck.emplace_back(rank + suit);
        }
    }
    
    std::mt19937 g(seed);
    std::shuffle(deck.begin(), deck.end(), g);
    return deck;
}

#include <cassert>

int main() {
    
    // TEST
    auto deck = RuffleShuffle(10);
    assert(deck.size() == 52);
    // TEST_END

    // TEST
    std::unordered_set<std::string> unique_cards(deck.begin(), deck.end());
    assert(unique_cards.size() == 52);
    // TEST_END


    // TEST
    bool different_shuffle = false;
    for (int i = 0; i < 10; ++i) {
        auto new_deck = RuffleShuffle(i);
        if ( new_deck != deck) {
            different_shuffle = true;
            break;
        }
    }
    assert(different_shuffle);
    // TEST_END
    
    // TEST
    auto deck1 = RuffleShuffle(100);
    auto deck2 = RuffleShuffle(100);
    assert(deck1 == deck2);
    // TEST_END
    
    return 0;
}

