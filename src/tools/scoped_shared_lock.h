#ifndef SRC_TOOLS_SCOPED_SHARED_LOCK_H
#define SRC_TOOLS_SCOPED_SHARED_LOCK_H

#include <mutex>
#include <shared_mutex>

namespace pala {

class ScopedSharedLock {
    using SharedLock = std::shared_lock<std::shared_mutex>;
    using UniqueLock = std::unique_lock<std::shared_mutex>;
    using ScopedLock3Shared = std::scoped_lock<SharedLock, SharedLock, SharedLock, UniqueLock>;
    using ScopedLock2Shared = std::scoped_lock<SharedLock, SharedLock, UniqueLock>;
public:
    ScopedSharedLock(std::shared_mutex& s1,
                     std::shared_mutex& s2,
                     std::shared_mutex& s3,
                     std::shared_mutex& t)
                     : mLockS1(s1, std::defer_lock),
                       mLockS2(s2, std::defer_lock),
                       mLockS3(s3, std::defer_lock),
                       mLockT(t, std::defer_lock) {
        mScopedLock3Shared = new ScopedLock3Shared(mLockS1, mLockS2, mLockS3, mLockT);
    }
    ScopedSharedLock(std::shared_mutex& s1,
                     std::shared_mutex& s2,
                     std::shared_mutex& t)
                     : mLockS1(s1, std::defer_lock),
                       mLockS2(s2, std::defer_lock),
                       mLockT(t, std::defer_lock) {
        mScopedLock2Shared = new ScopedLock2Shared(mLockS1, mLockS2, mLockT);
    }
    ~ScopedSharedLock() {
#define DEL_OBJ(obj) if (obj) { delete obj; obj = nullptr; }
        DEL_OBJ(mScopedLock3Shared);
        DEL_OBJ(mScopedLock2Shared);
#undef DEL_OBJ
    }

private:
    SharedLock mLockS1, mLockS2, mLockS3;
    UniqueLock mLockT;
    ScopedLock3Shared* mScopedLock3Shared;
    ScopedLock2Shared* mScopedLock2Shared;
};

}  // namespace pala

#endif  // SRC_TOOLS_SCOPED_SHARED_LOCK_H
