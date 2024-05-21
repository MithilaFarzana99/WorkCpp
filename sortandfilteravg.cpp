#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
#include <stdexcept>

std::tuple<std::vector<long long>, long long, long long, long long> AnalyzeAndFilterAboveAverage(const std::vector<long long> &data)
{
    if (data.empty())
    {
        throw std::invalid_argument("Input vector must not be empty");
    }
    
    double average = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    std::vector<long long> filtered;
    long long sum_above_average = 0;
    
    for (const auto &num : data)
    {
        if (num > average)
        {
            filtered.push_back(num);
            sum_above_average += num;
        }
    }
    
    auto [min_it, max_it] =  std::minmax_element(data.begin(), data.end());
    long long min_value = *min_it;
    long long max_value = *max_it;
    
    return std::make_tuple(filtered, min_value, max_value, sum_above_average);
}

#include <cassert>

int main()
{
    // TEST
    try {
        std::vector<long long> empty_vector;
        auto result = AnalyzeAndFilterAboveAverage(empty_vector);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(std::string(e.what()) == "Input vector must not be empty");
    }
    // TEST_END
    
    // TEST
    std::vector<long long> single_element = {42};
    auto [filtered2, min2, max2, sum2] = AnalyzeAndFilterAboveAverage(single_element);
    assert(filtered2.empty() && min2 == 42 && max2 == 42 && sum2 == 0);
    // TEST_END

    // TEST
    std::vector<long long> all_same = {7, 7, 7, 7};
    auto [filtered3, min3, max3, sum3] = AnalyzeAndFilterAboveAverage(all_same);
    assert(filtered3.empty() && min3 == 7 && max3 == 7 && sum3 == 0);
    // TEST_END

    // TEST
    std::vector<long long> all_above = {5, 6, 7};
    auto [filtered4, min4, max4, sum4] = AnalyzeAndFilterAboveAverage(all_above);
    assert((filtered4 == std::vector<long long>{7}) && min4 == 5 && max4 == 7 && sum4 == 7);
    // TEST_END
    
    // TEST
    std::vector<long long> negatives = {-10, -20, -30};
    auto [filtered5, min5, max5, sum5] = AnalyzeAndFilterAboveAverage(negatives);
    assert((filtered5 == std::vector<long long>{-10}) && min5 == -30 && max5 == -10 && sum5 == -10);
    // TEST_END

    // TEST
    std::vector<long long> mixed_numbers = {-10, 0, 10, 20};
    auto [filtered6, min6, max6, sum6] = AnalyzeAndFilterAboveAverage(mixed_numbers);
    assert((filtered6 == std::vector<long long>{10, 20}) && min6 == -10 && max6 == 20 && sum6 == 30);
    // TEST_END

    // TEST
    std::vector<long long> large_numbers = {1000000000LL, 2000000000LL, 3000000000LL};
    auto [filtered7, min7, max7, sum7] = AnalyzeAndFilterAboveAverage(large_numbers);
    assert((filtered7 == std::vector<long long>{3000000000LL}) && min7 == 1000000000LL && max7 == 3000000000LL && sum7 == 3000000000LL);
    // TEST_END

    return 0;
}
