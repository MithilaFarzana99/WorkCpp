#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <utility>
#include <cmath>

bool CoordinateValidation(double value)
{
    return !std::isnan(value) && !std::isinf(value);
}
std::pair<std::pair<double, double>, std::pair<double, double>> CalculateMinimumBoundingRectangle(const std::vector<std::pair<double, double>> &coordinates)
{
    if (coordinates.empty())
    {
        throw std::invalid_argument("Input vectors cannot be empty.");
    }
    
    double x_min = std::numeric_limits<double>::max();
    double y_min = std::numeric_limits<double>::max();
    double x_max = std::numeric_limits<double>::lowest();
    double y_max = std::numeric_limits<double>::lowest();
    
    for (const auto &coordinate : coordinates) {
        if(!CoordinateValidation(coordinate.first) || !CoordinateValidation(coordinate.second))
        {
            throw std::invalid_argument("Input vector contains invalid coordinates (NaN or infinity).");
        }
        
        x_max = std::max(x_max, coordinate.first);
        y_max = std::max(y_max, coordinate.second);
        x_min = std::min(x_min, coordinate.first);
        y_min = std::min(y_min, coordinate.second);
    }

    return {{x_min, y_min}, {x_max, y_max}};
}

#include <cassert>

int main()
{
    // TEST
    try {
        CalculateMinimumBoundingRectangle({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(std::string(e.what()) == "Input vectors cannot be empty.");
    }
    // TEST_END
    
    // TEST
    auto check = CalculateMinimumBoundingRectangle({{2.0, 3.0}});
    assert(check.first == std::make_pair(2.0, 3.0));
    assert(check.second == std::make_pair(2.0, 3.0));
    // TEST_END
    
    // TEST
    check = CalculateMinimumBoundingRectangle({{-1.0, 2.0}, {3.0, -4.0}, {-2.0, -1.0}, {1.0, 5.0}});
    assert(check.first == std::make_pair(-2.0, -4.0));
    assert(check.second == std::make_pair(3.0, 5.0));
    // TEST_END
    
    // TEST
    check = CalculateMinimumBoundingRectangle({{0.0, 0.0}, {-5.0, -5.0}, {-5.0, 5.0}, {5.0, -5.0}, {5.0, 5.0}});
    assert(check.first == std::make_pair(-5.0, -5.0));
    assert(check.second == std::make_pair(5.0, 5.0));
    // TEST_END

    // TEST
    check = CalculateMinimumBoundingRectangle({{-10.0, -10.0}, {-20.0, -30.0}, {-5.0, -15.0}});
    assert(check.first == std::make_pair(-20.0, -30.0));
    assert(check.second == std::make_pair(-5.0, -10.0));
    // TEST_END

    // TEST
    check = CalculateMinimumBoundingRectangle({{-10.0, -10.0}, {0.0, 0.0}, {10.0, 10.0}});
    assert(check.first == std::make_pair(-10.0, -10.0));
    assert(check.second == std::make_pair(10.0, 10.0));
    // TEST_END

    // TEST
    check = CalculateMinimumBoundingRectangle({{1e9, 1e9}, {-1e9, -1e9}, {0.0, 0.0}});
    assert(check.first == std::make_pair(-1e9, -1e9));
    assert(check.second == std::make_pair(1e9, 1e9));
    // TEST_END
    
    // TEST
    try {
        CalculateMinimumBoundingRectangle({{std::nan(""), 0.0}, {0.0, 0.0}});
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Input vector contains invalid coordinates (NaN or infinity).");
    }
    // TEST_END
    
    // TEST
    try {
        CalculateMinimumBoundingRectangle({{std::numeric_limits<double>::infinity(), 0.0}, {0.0, 0.0}});
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Input vector contains invalid coordinates (NaN or infinity).");
    }
    // TEST_END

}


// <iostream> Usage: Required for the std::cerr and std::cout statements used for error reporting or debugging (though none are explicitly used in this version). Required by the prompt: Necessary for input and output operations.
// <vector> Usage: The primary data structure used to store the collection of coordinates.
// <algorithm> Usage: The std::min and std::max functions are used to determine the minimum and maximum coordinates.
// <stdexcept> Usage: Provides the std::invalid_argument exception class to handle invalid input scenarios.
// <limits> Usage: Required to get std::numeric_limits for setting initial min and max values.
// <utility> Usage: Necessary for the std::pair data structure to return the bounding rectangle corners.
// <cassert> Usage: Provides assert for test assertions.
// <cmath> Usage: For std::isnan and std::isfinite functions to handle validation of numeric data.



