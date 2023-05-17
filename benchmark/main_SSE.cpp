#include <iostream>
#include "../lib/IntMatrix.h"

int main(int argc, char* argv[]) {
#ifdef SIMD_EXTENSION_ENABLED
    std::cout << "SIMD_EXTESION_ENABLED is defined" << std::endl;
#else
    std::cout << "SIMD_EXTESION_ENABLED is undefined" << std::endl;
#endif
    return 0;
}