#include <iostream>
#include <vector>
#include <fstream>
#include "../lib/IntMatrix.h"

const int MATRIX_ROW_SIZE = 1000;

int main(int argc, char* argv[]) {
#ifdef SIMD_EXTENSION_ENABLED
    std::cout << "SIMD_EXTESION_ENABLED is defined" << std::endl;
#else
    std::cout << "SIMD_EXTESION_ENABLED is undefined" << std::endl;
#endif
#ifdef O3_ENABLED
    std::cout << "O3 flag is enabled" << std::endl;
#else
    std::cout << "O3 flag is disabled" << std::endl;
#endif
    std::vector<std::vector<int>> rawMatrix1(MATRIX_ROW_SIZE, std::vector<int>(MATRIX_ROW_SIZE));
    std::ifstream in1("numbers1.txt");
    for (size_t i = 0; i < MATRIX_ROW_SIZE * MATRIX_ROW_SIZE; ++i) {
        int number;
        in1 >> number;
        rawMatrix1[i / MATRIX_ROW_SIZE][i % MATRIX_ROW_SIZE] = number;
    }
    in1.close();
    std::vector<std::vector<int>> rawMatrix2(MATRIX_ROW_SIZE, std::vector<int>(MATRIX_ROW_SIZE));
    std::ifstream in2("numbers1.txt");
    for (size_t i = 0; i < MATRIX_ROW_SIZE * MATRIX_ROW_SIZE; ++i) {
        int number;
        in2 >> number;
        rawMatrix2[i / MATRIX_ROW_SIZE][i % MATRIX_ROW_SIZE] = number;
    }
    matrix::IntMatrix matrix1(rawMatrix1);
    matrix::IntMatrix matrix2(rawMatrix2);
    [[maybe_unused]] auto result = matrix1 + matrix2;
    return 0;
}