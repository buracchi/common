#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/concurrency/rwfslock.h>
}

#include <thread>
#include <mutex>
#include <chrono>

TEST(cmn_rwfslock, multiple_rdlock_are_allowed) {
    cmn_rwfslock_t lock = cmn_rwfslock_init();
    for (int i = 0; i < 10; i++) {
        cmn_rwfslock_rdlock(lock, "./pippo");
    }
    cmn_rwfslock_destroy(lock);
    ASSERT_EQ(1, 1);
}

TEST(cmn_rwfslock, wrlock_is_exclusive) {
    cmn_rwfslock_t lock = cmn_rwfslock_init();
    std::atomic<bool> t1_has_lock = false;
    std::atomic<bool> t2_has_lock = false;
    std::mutex consumed_variables;
    bool wrlock_is_shared = false;
    consumed_variables.lock();
    std::thread t1([lock, &t1_has_lock, &consumed_variables] {
        cmn_rwfslock_wrlock(lock, "./pippo");
        t1_has_lock.store(true);
        consumed_variables.lock();
        cmn_rwfslock_unlock(lock, "./pippo");
        consumed_variables.unlock();
        });
    std::thread t2([lock, &t2_has_lock, &consumed_variables] {
        cmn_rwfslock_wrlock(lock, "./pippo");
        t2_has_lock.store(true);
        consumed_variables.lock();
        cmn_rwfslock_unlock(lock, "./pippo");
        consumed_variables.unlock();
    });
    std::thread timer([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    });
    timer.join();
    wrlock_is_shared = t1_has_lock.load() && t2_has_lock.load();
    consumed_variables.unlock();
    t1.join();
    t2.join();
    cmn_rwfslock_destroy(lock);
    ASSERT_EQ(wrlock_is_shared, false);
}

TEST(cmn_rwfslock, lock_is_unique_per_file) {
    cmn_rwfslock_t lock = cmn_rwfslock_init();
    std::thread t1([lock] {
        cmn_rwfslock_wrlock(lock, "./pippo");
    });
    std::thread t2([lock] {
        cmn_rwfslock_wrlock(lock, "./pluto");
    });
    t1.join();
    t2.join();
    cmn_rwfslock_destroy(lock);
    ASSERT_EQ(1, 1);
}
