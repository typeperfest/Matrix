#include <gtest/gtest.h>
#include "../lib/IntMatrix.h"
#include <vector>

TEST(TEST01, BasicTesting) {
    std::vector<std::vector<int>> v1{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    std::vector<std::vector<int>> v2{{3, 2, 1}, {3, 2, 1}, {3, 2, 1}};
    std::vector<std::vector<int>> vr{{4, 4, 4}, {4, 4, 4}, {4, 4, 4}};
    IntMatrix mat1(v1);
    IntMatrix mat2(v2);
    IntMatrix matr(vr);
    EXPECT_EQ(mat1 + mat2, matr);
};
