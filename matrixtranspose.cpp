#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


std::vector<std::vector<int>> MatrixTranspose(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("Input matrix must not be empty.");
    }
    
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    
    for (const auto& row : matrix) {
        if (row.size() != cols) {
            throw std::invalid_argument("Input matrix must have consistent row lengths.");
        }
    }
    
    std::vector<std::vector<int>> transposed(cols, std::vector<int>(rows));
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    
    return transposed;
}

#include <cassert>

int main() {
    // TEST
    try {
        std::vector<std::vector<int>> empty_matrix;
        auto result = MatrixTranspose(empty_matrix);
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Input matrix must not be empty.");
    }
    // TEST_END

    // TEST
    std::vector<std::vector<int>> single_element_matrix = {{42}};
    auto result2 = MatrixTranspose(single_element_matrix);
    assert(result2.size() == 1 && result2[0].size() == 1 && result2[0][0] == 42);
    // TEST_END

    // TEST
    std::vector<std::vector<int>> square_matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto result3 = MatrixTranspose(square_matrix);
    assert(result3.size() == 3 && result3[0].size() == 3 && result3[0][0] == 1 && result3[2][2] == 9);
    // TEST_END

    // TEST
    std::vector<std::vector<int>> rectangular_matrix = {{1, 2}, {3, 4}, {5, 6}};
    auto result4 = MatrixTranspose(rectangular_matrix);
    assert(result4.size() == 2 && result4[0].size() == 3 && result4[0][0] == 1 && result4[1][2] == 6);
    // TEST_END
    
    // TEST
    try {
        std::vector<std::vector<int>> non_square_matrix = {{1, 2, 3}, {4, 5}, {6, 7, 8}};
        auto result5 = MatrixTranspose(non_square_matrix);
        assert(false); // Should not reach this point
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Input matrix must have consistent row lengths.");
    }
    // TEST_END

    // TEST
    std::vector<std::vector<int>> one_row_matrix = {{1, 2, 3}};
    auto result6 = MatrixTranspose(one_row_matrix);
    assert(result6.size() == 3 && result6[0].size() == 1 && result6[0][0] == 1 && result6[2][0] == 3);
    // TEST_END
    
    // TEST
    std::vector<std::vector<int>> one_column_matrix = {{1}, {2}, {3}};
    auto result7 = MatrixTranspose(one_column_matrix);
    assert(result7.size() == 1 && result7[0].size() == 3 && result7[0][0] == 1 && result7[0][2] == 3);
    // TEST_END

    return 0;
}

