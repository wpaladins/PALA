#include "scoped_shared_lock.h"

using namespace std;
using namespace pala;

ScopedSharedLock::ScopedSharedLock(shared_mutex* s1,
                                   shared_mutex* s2,
                                   shared_mutex* s3,
                                   shared_mutex* t)
                                   : s1(s1),
                                     s2(s2),
                                     s3(s3),
                                     t(t) {
    while (true) {
        int index = 1;
        do {
            s1->lock_shared();

            if (s2->try_lock_shared()) {
                index++;
            } else {
                break;
            }

            if (s3->try_lock_shared()) {
                index++;
            } else {
                break;
            }

            if (t->try_lock()) {
                return;
            }
        } while(0);

        s1->unlock_shared();
        if (index >= 2) {
            s2->unlock_shared();
        }
        if (index >= 3) {
            s3->unlock_shared();
        }
        // this_thread::sleep_for(chrono::milliseconds(10));
    }
}

ScopedSharedLock::ScopedSharedLock(shared_mutex* s1,
                                   shared_mutex* s2,
                                   shared_mutex* t)
                                   : s1(s1),
                                     s2(s2),
                                     s3(nullptr),
                                     t(t) {
    while (true) {
        int index = 1;
        do {
            s1->lock_shared();

            if (s2->try_lock_shared()) {
                index++;
            } else {
                break;
            }

            if (t->try_lock()) {
                return;
            }
        } while(0);

        s1->unlock_shared();
        if (index >= 2) {
            s2->unlock_shared();
        }
        // this_thread::sleep_for(chrono::milliseconds(10));
    }
}

ScopedSharedLock::~ScopedSharedLock() {
#define unlock_obj(s) if (s) { s->unlock_shared(); s = nullptr; }
    unlock_obj(s1)
    unlock_obj(s2)
    unlock_obj(s3)
#undef unlock_obj
    t->unlock();
}
