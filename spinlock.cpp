#include <array>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

class SpinLock {
private:
    atomic_flag flag;
public:
    void lock() {
        while(flag.test_and_set(memory_order_acquire)){}
    }

    void unlock() {
        flag.clear(memory_order_release);
    }
};


uint64_t shared_int = 0;
constexpr uint64_t kMaxSharedInt = 0xFFFFFFF;
mutex mut;
SpinLock sl;




void task_w_mutex() {
    cout << "Thread initiated" << endl;
    uint64_t temp_shared_int = 0;
    while(true) {
        {
            const lock_guard<mutex> lg(mut);
            temp_shared_int = ++shared_int;
        }
        if(temp_shared_int > kMaxSharedInt) {
            break;
        }
    }
    return;
}

void task_w_spin_lock() {
    cout << "Thread initiated" << endl;
    uint64_t temp_shared_int = 0;
    while(true) {
        sl.lock();
        temp_shared_int = ++shared_int;
        sl.unlock();
        if(temp_shared_int > kMaxSharedInt) {
            break;
        }
    }
    return;
}



int main() {
    array<thread, 4> thread_array;
    auto start = chrono::high_resolution_clock::now();
    for(auto &t : thread_array) {
        // t = thread(task_w_mutex);
        t = thread(task_w_spin_lock);
    }   

    for(auto &t: thread_array) {
        t.join();
    }
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Elapsed time: " << elapsed.count() << " microseconds\n";
}

// With a mutex & lock_guard (microseconds)
// 7787358
// 8008464
// 7826256

// With a spin lock
// 28926708