#include <vector>
#include <gflags/gflags_declare.h>

#include "concurrent_array.h"
#include "flags.h"
#include "worker.h"

using namespace std;
using namespace pala;

DECLARE_int32(WORKER_NUM);

int main(int argc, char** argv) {
    array<int, ARRAY_SIZE> data;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 1000;
    }

    auto cv = ConcurrentArray<ARRAY_SIZE>::get_instance();
    cv->Init(data);

    vector<Worker> workers(FLAGS_WORKER_NUM);
    for (auto& worker : workers) {
        worker.Wait();
    }
    return 0;
}
