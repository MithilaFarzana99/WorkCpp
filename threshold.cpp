#include <vector>
#include <numeric>
#include <stdexcept>
#include <string>
#include <algorithm>

std::vector<bool> DynamicThresholding(const std::vector<double> &sensor_readings, double environmental_factor)
{
if (sensor_readings.empty())
{
throw std::invalid_argument("Readings cannot be empty");
}

double sum = std::accumulate(readings.begin(), sensor_readings.end(), 0.0);
double average = sum / sensor_readings.size();
double threshold = average * environmental_factor;

std::vector<bool> results(sensor_readings.size());
std::transform(sensor_readings.begin(), sensor_readings.end(), results.begin(), [threshold](double sensor_reading) { return sensor_reading > threshold; });

return results;
}


#include <cassert>

int main()
{
    // TEST
    std::vector<double> sensor_readings = {2.5, 3.5, 2.0, 4.0};
    double environmental_factor = 1.1;
    std::vector<bool> expected_results = {false, true, false, true};
    assert(DynamicThresholding(sensor_readings, environmental_factor) == expected_results);
    // TEST_END

    // TEST
    sensor_readings = {1.0, 1.2, 0.9, 1.1};
    environmental_factor = 0.9;
    expected_results = {true, true, false, true};
    assert(DynamicThresholding(sensor_readings, environmental_factor) == expected_results);
    // TEST_END

    // TEST
    sensor_readings = {-1.0, -2.0, -3.0, -4.0};
    environmental_factor = -0.5;
    expected_results = {false, false, false, false};
    assert(DynamicThresholding(sensor_readings, environmental_factor) == expected_results);
    // TEST_END

    // TEST
    sensor_readings = {2.5, 3.5, 2.0, 4.0};
    environmental_factor = 0.0;
    expected_results = {true, true, true, true};
    assert(DynamicThresholding(sensor_readings, environmental_factor) == expected_results);
    // TEST_END

    // TEST
    try
    {
        std::vector<double> empty_readings;
        DynamicThresholding(empty_readings, 1.0);
        assert(false);
    }
    catch (const std::invalid_argument &e)
    {
        assert(std::string(e.what()) == std::string("Readings cannot be empty"));
    }
    // TEST_END
}

