#include <gflags/gflags_declare.h>

#include "worker.h"
#include "tools/random_generator.h"
#include "concurrent_array.h"

using namespace pala;

DECLARE_int32(WORKER_OP_NUM);

static RandomGenerator sRandom;

Worker::Worker() {
    mVec = ConcurrentArray<ARRAY_SIZE>::get_instance();
    mThread = std::thread(&Worker::Run, this);
    mThread.detach();
}

void Worker::Run() {
    // random generate index
    // source1, source2, source3 different required
    int source1,
        source2,
        source3,
        target;
    for (int i = 0; i < FLAGS_WORKER_OP_NUM; i++) {
        sRandom.Generate(source1, source2, source3, target);
        mVec->Op(source1, source2, source3, target);
    }

    mPromise.set_value();
}

void Worker::Wait() {
    mPromise.get_future().wait();
}
