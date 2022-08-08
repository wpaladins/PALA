#ifndef SRC_TOOLS_SCOPED_SHARED_LOCK_H
#define SRC_TOOLS_SCOPED_SHARED_LOCK_H

#include <shared_mutex>

namespace pala {

// implement deadlock avoidance
class ScopedSharedLock {
public:
    ScopedSharedLock(std::shared_mutex* s1,
                     std::shared_mutex* s2,
                     std::shared_mutex* s3,
                     std::shared_mutex* t);
    ScopedSharedLock(std::shared_mutex* s1,
                     std::shared_mutex* s2,
                     std::shared_mutex* t);
    ~ScopedSharedLock();

private:
    std::shared_mutex* s1,
                * s2,
                * s3,
                * t;
};

}  // namespace pala

#endif  // SRC_TOOLS_SCOPED_SHARED_LOCK_H
