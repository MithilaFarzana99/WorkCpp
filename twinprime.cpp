#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

bool IsPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int iter = 3; iter <= sqrt(num); iter += 2) {
        if (num % iter == 0) return false;
    }
    return true;
}

std::vector<int> GenerateTwinPrimeCandidates(const std::vector<int>& numbers) {
    std::vector<int> twin_candidates;
    for (int num : numbers) {
        if (IsPrime(num)) {
            if (IsPrime(num + 2)) {
                twin_candidates.push_back(num + 2);
            }
            if (num > 2 && IsPrime(num - 2)) {
                twin_candidates.push_back(num - 2);
            }
        }
    }
    return twin_candidates;
}

#include <cassert>

int main() {
    // TEST
    assert(GenerateTwinPrimeCandidates({}).empty());
    // TEST_END
    
    // TEST
    assert(GenerateTwinPrimeCandidates({1, 4, 6, 8, 10}).empty());
    // TEST_END
    
    // TEST
    std::vector<int> test_1 = GenerateTwinPrimeCandidates({11, 14, 20, 17});
    assert((test_1 == std::vector<int>{13, 19}));
    // TEST_END
    
    // TEST
    std::vector<int> test_2 = GenerateTwinPrimeCandidates({-2, -1, 0, 29, 30});
    assert((test_2 == std::vector<int>{31}));
    // TEST_END
    
    // TEST
    std::vector<int> test_3 = GenerateTwinPrimeCandidates({5, 27, 95, 43});
    assert((test_3 == std::vector<int>{7, 3, 41}));
    // TEST_END
    
    // TEST
    std::vector<int> test_4 = GenerateTwinPrimeCandidates({101, 149, 179});
    assert((test_4 == std::vector<int>{103, 151, 181}));
    // TEST_END
    
    // TEST
    std::vector<int> large_input;
    for (int iter = 1; iter < 1000; iter++) {
        large_input.push_back(iter);
    }
    std::vector<int> large_test = GenerateTwinPrimeCandidates(large_input);
    assert(!large_test.empty());
    // TEST_END
    
    return 0;
}
