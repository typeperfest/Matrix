#include <gtest/gtest.h>
#include "../lib/IntMatrix.h"
#include <vector>

TEST(TEST01, BasicTesting) {
    std::vector<std::vector<int>> v{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    IntMatrix mat1(v);
    
};
