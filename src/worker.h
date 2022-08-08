#ifndef SRC_WORKER_H
#define SRC_WORKER_H

#include <thread>
#include <future>

#include "flags.h"

namespace pala {

template<std::size_t _Nm>
class ConcurrentArray;

class Worker {
public:
    Worker();
    void Run();
    void Wait();
private:
    std::thread mThread;
    std::promise<void> mPromise;
    ConcurrentArray<ARRAY_SIZE>* mVec;
};

}  // namespace pala

#endif  // SRC_WORKER_H
