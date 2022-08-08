#include <vector>
#include <gflags/gflags_declare.h>
#include <benchmark/benchmark.h>

#include "concurrent_array.h"
#include "flags.h"
#include "worker.h"

using namespace std;
using namespace pala;

DECLARE_int32(WORKER_NUM);

static void BM_PALA(benchmark::State& state) {
    array<int, ARRAY_SIZE> data;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 1000;
    }

    auto cv = ConcurrentArray<ARRAY_SIZE>::get_instance();
    cv->Init(data);

    for (auto _ : state) {
        vector<Worker> workers(FLAGS_WORKER_NUM);
        for (auto& worker : workers) {
            worker.Wait();
        }
    }
}

BENCHMARK(BM_PALA);

BENCHMARK_MAIN();
