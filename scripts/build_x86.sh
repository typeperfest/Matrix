arch -x86_64 /usr/local/bin/cmake -H. -Bbuild/x86 -DBUILD_X86_WITH_SSE=1 -DBUILD_TESTS=1
arch -x86_64 /usr/local/bin/cmake --build build/x86