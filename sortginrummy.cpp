#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::vector<std::string> SortGinRummy(const std::vector<std::string>& cards) {
    std::vector<char> suits = {'S', 'H', 'D', 'C'};
    std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    auto card_sort_key = [&](const std::string& card) -> std::pair<int, int> {
        if (card.size() < 2 || card.size() > 3 ||
            std::find(suits.begin(), suits.end(), card.back()) == suits.end() ||
            std::find(ranks.begin(), ranks.end(), card.substr(0, card.size() - 1)) == ranks.end()) {
            throw std::invalid_argument("Invalid format.");
        }
        std::string rank = card.substr(0, card.size() - 1);
        char suit = card.back();
        auto rank_index = std::find(ranks.begin(), ranks.end(), rank) - ranks.begin();
        auto suit_index = std::find(suits.begin(), suits.end(), suit) - suits.begin();
        
        return {suit_index, rank_index};
    };

    std::vector<std::string> sorted_cards = cards;
    std::sort(sorted_cards.begin(), sorted_cards.end(), [&](const std::string& a, const std::string& b) {
        return card_sort_key(a) < card_sort_key(b);
    });

    return sorted_cards;
}

#include <cassert>

int main() {
    
    assert(SortGinRummy({"10S", "AH", "3D", "KC", "2H", "JD", "7S", "8C", "9H", "QS"}) == std::vector<std::string>({"7S", "10S", "QS", "AH", "2H", "9H", "3D", "JD", "8C", "KC"}));

    
    assert(SortGinRummy({"KC", "8C", "JD", "3D", "9H", "2H", "AH", "QS", "10S", "7S"}) == std::vector<std::string>({"7S", "10S", "QS", "AH", "2H", "9H", "3D", "JD", "8C", "KC"}));

    
    assert(SortGinRummy({"2S", "KS", "AS", "QS", "JS"}) == std::vector<std::string>({"AS", "2S", "JS", "QS", "KS"}));

    
    assert(SortGinRummy({}) == std::vector<std::string>({}));

    
    assert(SortGinRummy({"AH", "AD", "AC", "AS"}) == std::vector<std::string>({"AS", "AH", "AD", "AC"}));
    
    bool caught = false;
    try {
        SortGinRummy({"10T", "1P", "2X", "AH"});
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);
    return 0;
}
