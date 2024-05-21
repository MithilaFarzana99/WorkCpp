
#include <vector>
#include <algorithm>

std::vector<int> SortAndFilterPositive(std::vector<int> input) {
      input.erase(std::remove_if(input.begin(), input.end(), [](int number) {
        return number <= 0;
    }), input.end());

    std::sort(input.begin(), input.end());

    return input;
}

#include <cassert>

int main() {
    // TEST:
    std::vector<int> input1 = {3, -1, 0, 2, 5};
    std::vector<int> expected1 = {2, 3, 5};
    assert(SortAndFilterPositive(input1) == expected1);
    // TEST_END

    // TEST:
    std::vector<int> input2 = {-4, -2, -5, -1};
    std::vector<int> expected2 = {};
    assert(SortAndFilterPositive(input2) == expected2);
    // TEST_END

    // TEST:
    std::vector<int> input3 = {10, 9, 8, 7, 6};
    std::vector<int> expected3 = {6, 7, 8, 9, 10};
    assert(SortAndFilterPositive(input3) == expected3);
    // TEST_END

    // TEST:
    std::vector<int> input4 = {};
    std::vector<int> expected4 = {};
    assert(SortAndFilterPositive(input4) == expected4);
    // TEST_END
}
