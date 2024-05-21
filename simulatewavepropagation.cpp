#include <iostream>
#include <vector>



std::vector<double> SimulateWavePropagation(const std::vector<double>& initial_conditions, double speed, int time_steps) {
    if (initial_conditions.empty()) {
        throw std::invalid_argument("Initial conditions cannot be empty.");
    }
    if (speed <= 0) {
        throw std::invalid_argument("Speed must be positive.");
    }
    if (time_steps <= 0) {
        throw std::invalid_argument("Number of time steps must be positive.");
    }
    if (initial_conditions.size() == 1) {
        return initial_conditions;
    }

    std::vector<double> current_state = initial_conditions;
    std::vector<double> next_state(initial_conditions.size(), 0.0);

    for (int t = 0; t < time_steps; ++t) {
        for (size_t i = 1; i < current_state.size() - 1; ++i) {
            next_state[i] = current_state[i] - speed * (current_state[i + 1] - current_state[i - 1]);
        }

        next_state.front() = current_state.front() - speed * (current_state[1] - current_state.front());
        next_state.back() = current_state.back() - speed * (current_state.back() - current_state[current_state.size() - 2]);

        current_state.swap(next_state);
    }

    return current_state;
}

#include <cassert>

int main() {
    // TEST
    try {
        std::vector<double> empty_conditions;
        SimulateWavePropagation(empty_conditions, 1.0, 10);
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        std::vector<double> initial_conditions = {0.0, 1.0, 2.0};
        SimulateWavePropagation(initial_conditions, 0, 10);
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        std::vector<double> initial_conditions = {0.0, 1.0, 2.0};
        SimulateWavePropagation(initial_conditions, 1.0, -1);
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END
    
    // TEST
    std::vector<double> initial_conditions1 = {0.0, 1.0, 2.0};
    auto result1 = SimulateWavePropagation(initial_conditions1, 1.0, 10);
    assert(result1.size() == initial_conditions1.size());
    // TEST_END

    // TEST
    std::vector<double> initial_conditions2 = {1.0};
    auto result2 = SimulateWavePropagation(initial_conditions2, 1.0, 1);
    assert(result2.size() == 1 && result2[0] == initial_conditions2[0]);
    // TEST_END

    return 0;
}



