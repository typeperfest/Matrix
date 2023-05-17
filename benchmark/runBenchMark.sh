function buildBenchRosetta() {
    arch -x86_64 /usr/local/bin/cmake -H. -B../build/benchmark
    arch -x86_64 /usr/local/bin/cmake --build ../build/benchmark
}

buildBenchRosetta

time ../build/benchmark/benchSSE
time ../build/benchmark/benchO3