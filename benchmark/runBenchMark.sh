function buildBenchRosetta() {
    arch -x86_64 /usr/local/bin/cmake -H. -B../build/benchmark
    arch -x86_64 /usr/local/bin/cmake --build ../build/benchmark
}

buildBenchRosetta

python3 generateNumbers.py

time ../build/benchmark/benchSSE_O3
echo
time ../build/benchmark/benchO3
echo
time ../build/benchmark/bench