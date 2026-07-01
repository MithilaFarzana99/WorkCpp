#include <vector>
#include <numeric>
#include <stdexcept>
#include <string>
#include <algorithm>

std::vector<bool> DynamicThresholding(const std::vector<double>& readings, double environmentalFactor) {
    if (readings.empty()) {
        throw std::invalid_argument("Readings cannot be empty");
    }

    double sum = std::accumulate(readings.begin(), readings.end(), 0.0);
    double average = sum / readings.size();
    double threshold = average * environmentalFactor;

    std::vector<bool> results(readings.size());
    std::transform(readings.begin(), readings.end(), results.begin(), [threshold](double reading) { return reading > threshold; });

    return results;
}

#include <cassert>

int main() {
    // TEST
    std::vector<double> sensorReadings = {2.5, 3.5, 2.0, 4.0};
    double environmentalFactor = 1.1;
    std::vector<bool> expectedResults = {false, true, false, true};
    assert(DynamicThresholding(sensorReadings, environmentalFactor) == expectedResults);
    // TEST_END

    // TEST
    sensorReadings = {1.0, 1.2, 0.9, 1.1};
    environmentalFactor = 0.9;
    expectedResults = {true, true, false, true};
    assert(DynamicThresholding(sensorReadings, environmentalFactor) == expectedResults);
    // TEST_END

    // TEST
    sensorReadings = {-1.0, -2.0, -3.0, -4.0};
    environmentalFactor = -0.5;
    expectedResults = {false, false, false, false};
    assert(DynamicThresholding(sensorReadings, environmentalFactor) == expectedResults);
    // TEST_END
    
    // TEST
    sensorReadings = {2.5, 3.5, 2.0, 4.0};
    environmentalFactor = 0.0;
    expectedResults = {true, true, true, true};
    assert(DynamicThresholding(sensorReadings, environmentalFactor) == expectedResults);
    // TEST_END
    
    // TEST
    try {
        std::vector<double> emptyReadings;
        DynamicThresholding(emptyReadings, 1.0);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == std::string("Readings cannot be empty"));
    }
    // TEST_END
}
