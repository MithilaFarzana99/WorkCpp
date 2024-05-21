#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>

std::vector<std::vector<int>> DistributeFiles(const std::vector<std::pair<int, int>>& file_ids_sizes, int unit_capacity)
{
    if (unit_capacity <= 0)
    {
        throw std::invalid_argument("unit capacity must be greater than zero.");
    }

    std::vector<std::vector<int>> distribution;
    std::vector<int> current_unit;
    int current_capacity = 0;

    for (const auto& file : file_ids_sizes)
    {
        int file_id = file.first;
        int file_size = file.second;

        if (file_size > unit_capacity)
        {
            if (!current_unit.empty())
            {
                distribution.push_back(current_unit);
                current_unit.clear();
                current_capacity = 0;
            }
            
            distribution.push_back({file_id});
            continue;
        }

        if (current_capacity + file_size > unit_capacity)
        {
            distribution.push_back(current_unit);
            current_unit.clear();
            current_capacity = 0;
        }

        current_unit.push_back(file_id);
        current_capacity += file_size;
    }

    if (!current_unit.empty())
    {
        distribution.push_back(current_unit);
    }

    return distribution;
}

#include <cassert>

int main()
{
    // TEST
    std::vector<std::vector<int>> expected1 = {{1, 2}, {3}};
    assert(DistributeFiles({{1, 50}, {2, 40}, {3, 60}}, 100) == expected1);
    // TEST_END
    
    // TEST
    std::vector<std::vector<int>> expected2 = {{1}, {2}};
    assert(DistributeFiles({{1, 150}, {2, 50}}, 100) == expected2);
    // TEST_END
    
    // TEST
    std::vector<std::vector<int>> expected3 = {};
    assert(DistributeFiles({}, 100) == expected3);
    // TEST_END
    
    // TEST
    try {
        DistributeFiles({{1, 50}}, -1);
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(true);
    }
    // TEST_END
    
    // TEST
    std::vector<std::vector<int>> expected4 = {{1}, {2}, {3}};
    assert(DistributeFiles({{1, 100}, {2, 100}, {3, 100}}, 100) == expected4);
    // TEST_END
    
    return 0;
}

