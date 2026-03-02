#include <vector>
#include <stdexcept>
#include <string>

const double epsilon = 1e-9;

double CalculateAverageSpeed(const std::vector<std::pair<double, double>>& segments) 
{
    if (segments.empty()) 
    {
        return 0.0;
    }

    double total_distance = 0.0;
    double total_time = 0.0;

    for (const auto& segment : segments) 
    {
        double distance = segment.first;
        double time = segment.second;

        if (time <= 0) 
        {
            throw std::invalid_argument("Time must be greater than zero for all segments.");
        }

        total_distance += distance;
        total_time += time;
    }

    if (total_time == 0) 
    {
        throw std::runtime_error("Total time cannot be zero.");
    }

    return total_distance / total_time;
}

#include <cassert>
#include <cmath>

int main() {
    // TEST:
    assert(std::abs(CalculateAverageSpeed({{100.0, 10.0}, {50.0, 5.0}, {150.0, 15.0}}) - 10.0) < epsilon);
    // TEST_END

    // TEST:
    assert(std::abs(CalculateAverageSpeed({{0.0, 10.0}, {0.0, 5.0}, {0.0, 15.0}}) - 0.0) < epsilon);
    // TEST_END

    // TEST:
    assert(std::abs(CalculateAverageSpeed({{100.0, 10.0}, {-50.0, 5.0}, {150.0, 15.0}}) - (6.66666666667)) < epsilon);
    // TEST_END

    // TEST:
    assert(std::abs(CalculateAverageSpeed({}) - 0.0) < epsilon);
    // TEST_END

    // TEST:
    try {
        CalculateAverageSpeed({{100.0, 10.0}, {50.0, -5.0}, {150.0, 15.0}});
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Time must be greater than zero for all segments.");
    }
    // TEST_END
    
    // TEST
    try {
        CalculateAverageSpeed({{100.0, 0.0}});
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Time must be greater than zero for all segments.");
    }
    // TEST_END
    
    // TEST
    try {
        CalculateAverageSpeed({{100.0, 10.0}, {200.0, -10.0}});
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Total time cannot be zero.");
    }
    // TEST_END
    
    return 0;
}
