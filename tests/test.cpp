#include <gtest/gtest.h>
#include "../lib/IntMatrix.h"
#include <vector>

typedef std::vector<std::vector<int>> vvecint;

TEST(TEST01, FormatCheck) {
    vvecint v1{{1, 2, 3}, {1, 2}, {1, 2, 3}};
    vvecint v2{{1}, {1, 2}};
    vvecint v3{{}, {1}, {}};
    vvecint v4{{1, 2, 3, 4}, {1, 2, 3, 4}, {1}};
    EXPECT_THROW(IntMatrix(v1), std::runtime_error);
    EXPECT_THROW(IntMatrix(v2), std::runtime_error);
    EXPECT_THROW(IntMatrix(v3), std::runtime_error);
    EXPECT_THROW(IntMatrix(v4), std::runtime_error);

    EXPECT_THROW(IntMatrix m1({{1, 2, 3}, {1, 2}, {1, 2, 3}}), std::runtime_error);
    EXPECT_THROW(IntMatrix m2({{1}, {1, 2}}), std::runtime_error);
    EXPECT_THROW(IntMatrix m3({{}, {1}, {}}), std::runtime_error);
    EXPECT_THROW(IntMatrix m4({{1, 2, 3, 4}, {1, 2, 3, 4}, {1}}), std::runtime_error);
}

TEST(TEST02, BasicConstruction) {
    vvecint v1{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    vvecint v2{{1}, {1}, {1}, {1}, {1}};
    vvecint v3{{1, 2, 3, 4, 5, 6, 7}};
    EXPECT_NO_THROW(IntMatrix m1(v1));
    EXPECT_NO_THROW(IntMatrix m2(v2));
    EXPECT_NO_THROW(IntMatrix m3(v3));

    EXPECT_NO_THROW(IntMatrix m4({{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}));
    EXPECT_NO_THROW(IntMatrix m4({{1}, {1}, {1}, {1}, {1}}));
    EXPECT_NO_THROW(IntMatrix m4({{1, 2, 3, 4, 5, 6, 7}}));

    IntMatrix mat3;
    IntMatrix mat1(v1);
    IntMatrix mat2(mat1);
    IntMatrix mat3(std::move(mat2));
    vvecint v3{{}};
    IntMatrix mat2(v3);
}

TEST(TEST03, BasicAssignation) {
    vvecint v1{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    IntMatrix m1(v1);
    IntMatrix m2;
    m2 = m1;
    IntMatrix v2{{1, 2, 3}, {1, 2, 3}};
    IntMatrix m3(v2);
    m3 = m2;
    IntMatrix m4;
    m4 = std::move(m3);
}

TEST(TEST04, ArithmeticOperations) {
    vvecint v1{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    vvecint v2{{3, 2, 1}, {3, 2, 1}, {3, 2, 1}};
    vvecint vr{{4, 4, 4}, {4, 4, 4}, {4, 4, 4}};
    IntMatrix mat1(v1);
    IntMatrix mat2(v2);
    IntMatrix matr(vr);
    EXPECT_EQ(mat1 + mat2, matr);
    // TODO: implement compatibility checking
    // TODO: implement substraction
    // TODO: implement multiplication
};
