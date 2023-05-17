# Matrix.h with SSE extension
Matrix.h uses SSE extension to speed up ADDITIIN and SUBSTRACTION operations

### Build
#### Mac M1
- brew for x86 is required
- cmake installed under x86 brew is required
To build under Rosetta 2 with SSE extension enabled. Compiler adds required defintions automatically.
```bash
./scripts/build_x86.sh
```
To build without SSE support use:
```bash
./scripts/build_arm64.sh
```
#### x86
- cmake is required
```
cmake . -Bbuild/x86 -DBUILD_X86_WITH_SSE=1
cmake --build build/x86
```

### Used SSE intrinsics
See this 
[guide](https://www.laruence.com/sse/#)

1. ```__m128i _mm_lddqu_si128 (__m128i const* mem_addr)```
2. ```__m128i _mm_sub_epi32 (__m128i a, __m128i b)```
3. ```__m128i _mm_add_epi32 (__m128i a, __m128i b)```
4. ```void _mm_storeu_si32 (void* mem_addr, __m128i a)```
5. ```__m128i _mm_bsrli_si128 (__m128i a, int imm8)```

### Testing
You could generate your own tests using script generateTestcases.py. To see usage run without parameters.
Paste generated tests into tests/test.cpp and build.