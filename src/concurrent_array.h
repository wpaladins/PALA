#ifndef SRC_CONCURRENT_ARRAY_H
#define SRC_CONCURRENT_ARRAY_H

#include <array>
#include <atomic>
#include <cassert>
#include <memory>
#include <shared_mutex>

#include "tools/scoped_shared_lock.h"

namespace pala {

template<std::size_t _Nm>
class ConcurrentArray {
    using data_type = std::array<int, _Nm>;
public:
    void Init(const data_type& data);
    void Op(int source1, int source2, int source3, int target);

    const data_type& get_data() { return mData; }
    static ConcurrentArray* get_instance() {
        static ConcurrentArray instance;
        return &instance;
    }

private:
    ConcurrentArray() : mInited(false) {}
    ConcurrentArray(const ConcurrentArray& rh) = delete;

    data_type                          mData;
    std::array<std::shared_mutex, _Nm> mLocks;
    volatile bool                      mInited;
};

template<std::size_t _Nm>
void ConcurrentArray<_Nm>::Init(const data_type& data) {
    mData = data;
    mInited = true;
}

template<std::size_t _Nm>
void ConcurrentArray<_Nm>::Op(int source1, int source2, int source3, int target) {
    assert(mInited == true);
    assert(source1 >= 0 && source1 < mData.size());
    assert(source2 >= 0 && source2 < mData.size());
    assert(source3 >= 0 && source3 < mData.size());
    assert(target  >= 0 && target  < mData.size());

    auto s1 = &mLocks[source1],
         s2 = &mLocks[source2],
         s3 = &mLocks[source3],
         t  = &mLocks[target];

    // merge and scoped lock
    std::unique_ptr<ScopedSharedLock> _guard;
    if (source1 == target) {
        _guard.reset(new ScopedSharedLock(s2, s3, t));
    } else if (source2 == target) {
        _guard.reset(new ScopedSharedLock(s1, s3, t));
    } else if (source3 == target) {
        _guard.reset(new ScopedSharedLock(s1, s2, t));
    } else {
        _guard.reset(new ScopedSharedLock(s1, s2, s3, t));
    }

    mData[target] = mData[source1] + mData[source2] + mData[source3];
}

}  // namespace pala

#endif  // SRC_CONCURRENT_ARRAY_H
