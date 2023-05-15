#include <gtest/gtest.h>
#include "../lib/IntMatrix.h"
#include <vector>

typedef std::vector<std::vector<int>> vvecint;
using namespace matrix;

TEST(TEST01, FormatCheck) {
    vvecint v1{{1, 2, 3}, {1, 2}, {1, 2, 3}};
    vvecint v2{{1}, {1, 2}};
    vvecint v3{{}, {1}, {}};
    vvecint v4{{1, 2, 3, 4}, {1, 2, 3, 4}, {1}};
    EXPECT_THROW(IntMatrix mv1(v1), std::runtime_error);
    EXPECT_THROW(IntMatrix mv2(v2), std::runtime_error);
    EXPECT_THROW(IntMatrix mv3(v3), std::runtime_error);
    EXPECT_THROW(IntMatrix mv4(v4), std::runtime_error);

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

    IntMatrix mat0;
    IntMatrix mat1(v1);
    IntMatrix mat2(mat1);
    IntMatrix mat3(std::move(mat2));
    vvecint v4{{}};
    IntMatrix mat4(v3);

    IntMatrix numbersConstructed1(7, 7);
    IntMatrix zeros1({{0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0}});
    EXPECT_EQ(numbersConstructed1, zeros1);
    IntMatrix numbersConstructed2(1, 1);
    IntMatrix zeros2({{0}});
    EXPECT_EQ(numbersConstructed2, zeros2);
    IntMatrix numbersConstructed3(2, 4);
    IntMatrix zeros3({{0, 0, 0, 0}, {0, 0, 0, 0}});
    EXPECT_EQ(numbersConstructed3, zeros3);
    IntMatrix numbersConstructed4(4, 2);
    IntMatrix zeros4({{0, 0}, {0, 0}, {0, 0}, {0, 0}});
    EXPECT_EQ(numbersConstructed4, zeros4);
}

TEST(TEST03, BasicAssignation) {
    vvecint v1{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    IntMatrix m1(v1);
    IntMatrix m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
    IntMatrix v2{{1, 2, 3}, {1, 2, 3}};
    IntMatrix m3(v2);
    m3 = m2;
    EXPECT_EQ(m2, m3);
    IntMatrix m4;
    m4 = std::move(m3);
    EXPECT_EQ(m4, m2);
}

TEST(TEST04, CompatibilityChecking) {
    IntMatrix mat1({{1, 2, 3, 4, 5}});
    IntMatrix mat2({{1}, {2}, {3}, {4}, {5}});
    IntMatrix mat3({{1}});
    IntMatrix squaredMat1({{1, 2, 3}, {1, 2, 3}, {1, 2, 3}});
    IntMatrix squaredMat2({{1, 2, 3}, {1, 2, 3}, {1, 2, 3}});
    IntMatrix mat6({{1, 2, 3, 4, 5}});
    IntMatrix empMat({{}});

    EXPECT_TRUE(squaredMat1.isCompatible(squaredMat2, Operation::ADDITION));
    EXPECT_TRUE(squaredMat1.isCompatible(squaredMat2, Operation::SUBSTRACTION));
    EXPECT_TRUE(squaredMat1.isCompatible(squaredMat2, Operation::MULTIPLICATION));
    EXPECT_TRUE(squaredMat1.isCompatible(squaredMat2, Operation::COMPARISON));

    EXPECT_TRUE(mat1.isCompatible(mat2, Operation::MULTIPLICATION));
    EXPECT_TRUE(mat2.isCompatible(mat1, Operation::MULTIPLICATION));
    EXPECT_FALSE(mat1.isCompatible(mat2, Operation::ADDITION));
    EXPECT_FALSE(mat1.isCompatible(mat2, Operation::SUBSTRACTION));
    EXPECT_FALSE(mat1.isCompatible(mat2, Operation::COMPARISON));

    EXPECT_TRUE(mat1.isCompatible(mat6, Operation::ADDITION));
    EXPECT_TRUE(mat1.isCompatible(mat6, Operation::SUBSTRACTION));
    EXPECT_TRUE(mat1.isCompatible(mat6, Operation::COMPARISON));
    EXPECT_FALSE(mat1.isCompatible(mat6, Operation::MULTIPLICATION));

    EXPECT_FALSE(empMat.isCompatible(mat1, Operation::ADDITION));
    EXPECT_FALSE(empMat.isCompatible(mat1, Operation::MULTIPLICATION));
    EXPECT_FALSE(empMat.isCompatible(mat1, Operation::SUBSTRACTION));
    EXPECT_FALSE(empMat.isCompatible(mat1, Operation::COMPARISON));
}

TEST(TEST05, ArithmeticOperations) {
    vvecint v1{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    vvecint v2{{3, 2, 1}, {3, 2, 1}, {3, 2, 1}};
    vvecint vr{{4, 4, 4}, {4, 4, 4}, {4, 4, 4}};
    IntMatrix mat1(v1);
    IntMatrix mat2(v2);
    IntMatrix matr(vr);
    EXPECT_EQ(mat1 + mat2, matr);
    IntMatrix rectMat1({{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}});
    IntMatrix rectMat2({{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}});
    IntMatrix rectMat3({{2, 4, 6, 8}, {2, 4, 6, 8}, {2, 4, 6, 8}});
    EXPECT_EQ(rectMat1 + rectMat2, rectMat3);
    IntMatrix rowMat1({{7, 7, 7}});
    IntMatrix rowMat2({{3, 3, 3}});
    IntMatrix rowMat3({{4, 4, 4}});
    IntMatrix rowMat5 = rowMat1 - rowMat2; 
    EXPECT_EQ(rowMat5, rowMat3);
    IntMatrix rowMat4({{5, 5, 5}});
    IntMatrix colMat1({{4}, {4}, {4}});
    IntMatrix singleMat1({{60}});
    IntMatrix colMat2({{20, 20, 20}, {20, 20, 20}, {20, 20, 20}});
    EXPECT_EQ(rowMat4 * colMat1, singleMat1);
    EXPECT_EQ(colMat1 * rowMat4, colMat2);
};
