function buildBenchRosetta() {
    arch -x86_64 /usr/local/bin/cmake -H. -Bbuild/benchmark -DBUILD_BENCHMARK=1
    arch -x86_64 /usr/local/bin/cmake --build build/benchmark
}

buildBenchRosetta

python3 benchmark/generateNumbers.py

time build/benchmark/benchSSE
echo
time build/benchmark/benchO3
echo
time build/benchmark/bench

rm -r numbers1.txt
rm -r numbers2.txt