#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


std::vector<int> FindStatusCodePatterns(const std::vector<int>& log, const std::vector<int>& pattern) {
    if (pattern.empty()) {
        throw std::invalid_argument("Pattern vector cannot be empty.");
    }
    
    std::vector<int> matches;
    if (log.size() < pattern.size()) {
        return matches;
    }
    
    for (size_t i = 0; i <= log.size() - pattern.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < pattern.size(); ++j) {
            if (log[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            matches.push_back(static_cast<int>(i));
        }
    }
    
    return matches;
}

#include <cassert>

int main() 
{
    // TEST
    try {
        std::vector<int> log1 = {200, 500, 200, 404, 500, 200, 404};
        std::vector<int> pattern1 = {500, 200, 404};
        std::vector<int> expected1 = {1, 4};
        assert(FindStatusCodePatterns(log1, pattern1) == expected1);
    } catch (const std::invalid_argument& e) {
        assert(false);
    }
    // TEST_END
    
    // TEST
    try {
        std::vector<int> log2 = {200, 200, 200, 200};
        std::vector<int> pattern2 = {200};
        std::vector<int> expected2 = {0, 1, 2, 3};
        assert(FindStatusCodePatterns(log2, pattern2) == expected2);
    } catch (const std::invalid_argument& e) {
        assert(false);
    }
    // TEST_END

    // TEST
    try {
        std::vector<int> log3 = {400, 400, 400, 400};
        std::vector<int> pattern3 = {500};
        std::vector<int> expected3 = {};
        assert(FindStatusCodePatterns(log3, pattern3) == expected3);
    } catch (const std::invalid_argument& e) {
        assert(false);
    }
    // TEST_END

    // TEST
    try {
        std::vector<int> log4 = {};
        std::vector<int> pattern4 = {500};
        std::vector<int> expected4 = {};
        assert(FindStatusCodePatterns(log4, pattern4) == expected4);
    } catch (const std::invalid_argument& e) {
        assert(false);
    }
    // TEST_END

    // TEST
    try {
        std::vector<int> log5 = {200, 500};
        std::vector<int> pattern5 = {200, 500, 404};
        std::vector<int> expected5 = {};
        assert(FindStatusCodePatterns(log5, pattern5) == expected5);
    } catch (const std::invalid_argument& e) {
        assert(false);
    }
    // TEST_END
    
    // TEST
    try {
        std::vector<int> log6 = {200, 500, 200};
        std::vector<int> pattern6 = {};
        FindStatusCodePatterns(log6, pattern6);
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(true);
    }
    // TEST_END
    
    // TEST
    try {
        std::vector<int> log7 = {-200, -500, -200, -404, -500, -200, -404};
        std::vector<int> pattern7 = {-500, -200, -404};
        std::vector<int> expected7 = {1, 4};
        assert(FindStatusCodePatterns(log7, pattern7) == expected7);
    } catch (const std::invalid_argument& e) {
        assert(false);
    }
    // TEST_END

    return 0;
}


// Develop a C++ function named "FindStatusCodePatterns" that takes two vectors: one large vector representing a sequence of status codes from network logs and a smaller vector representing a specific pattern of interest. The function should return a vector of integers, each an index at which the pattern starts within the large vector.
