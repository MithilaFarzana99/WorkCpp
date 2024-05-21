#include <vector>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <algorithm>
//#include <iterator> it was not necessary

struct ColumnStatistics {
    double mean;
    double stddev;
    double min;
    double max;
};

std::vector<ColumnStatistics> CalculateStatistics(const std::vector<std::vector<double>> &data_set) {
    if (data_set.empty() || data_set[0].empty()) {
        throw std::invalid_argument("The input data set must not be empty and must contain data.");
    }

    std::vector<ColumnStatistics> statistics(data_set[0].size());
    size_t num_rows = data_set.size();
    size_t num_columns = data_set[0].size();

    for (size_t col = 0; col < num_columns; ++col) {
        std::vector<double> column_values(num_rows);
        std::transform(data_set.begin(), data_set.end(), column_values.begin(),
                       [col](const std::vector<double>& row) {
                           return row[col];
                       });
 
        double sum = std::accumulate(column_values.begin(), column_values.end(), 0.0);
        double mean = sum / num_rows;
        statistics[col].mean = mean;

        double sq_sum = std::inner_product(column_values.begin(), column_values.end(), column_values.begin(), 0.0);
        double stddev = std::sqrt(sq_sum / num_rows - mean * mean);
        statistics[col].stddev = stddev;

        auto[min_it, max_it] = std::minmax_element(column_values.begin(), column_values.end());
        statistics[col].min = *min_it;
        statistics[col].max = *max_it;
    }
    return statistics;
}

#include <cassert>
#include <limits>


std::vector<ColumnStatistics> CalculateStatistics(const std::vector<std::vector<double>> &data_set);

int main() {
    // TEST
    try {
        CalculateStatistics({});
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CalculateStatistics({{}});
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END

    // TEST
    auto stats1 = CalculateStatistics({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    assert(stats1.size() == 3);
    double epsilon = std::numeric_limits<double>::epsilon() * 100;
    
    assert(std::abs(stats1[0].mean - 4.0) < epsilon);
    assert(std::abs(stats1[1].mean - 5.0) < epsilon);
    assert(std::abs(stats1[2].mean - 6.0) < epsilon);
    assert(std::abs(stats1[0].stddev - std::sqrt(6.0)) < epsilon);
    assert(stats1[0].min == 1);
    assert(stats1[0].max == 7);
    // TEST_END

    // TEST
    auto stats2 = CalculateStatistics({{-1, -2, -3}, {-4, -5, -6}});
    assert(stats2.size() == 3);
    assert(std::abs(stats2[0].mean + 2.5) < epsilon);
    assert(std::abs(stats2[1].mean + 3.5) < epsilon);
    assert(std::abs(stats2[2].mean + 4.5) < epsilon);
    assert(stats2[0].min == -4);
    assert(stats2[0].max == -1);
    // TEST_END
    
    return 0;
}



