#include <array>
#include <iostream>
#include <thread>


/**
* Implemented as a ring buffer
*/
template<typename T, std::size_t N>
class Queue {
    static_assert(N >= 1U);
public:
    bool full() const{
        return (((m_tail + 1U) % (N+1U)) == m_head);
    }

    bool empty() const{
        return m_head == m_tail;
    }

    bool push(const T& element) {
        // queue must not be full
        if(full()) {
            return false;
        }
        m_array[m_tail] = element;
        m_tail = ((m_tail + 1U) % (N+1U));
        return true;
    }

    T front() {
        return m_array[m_head];
    }

    void pop() {
        if(empty()) {
            return;
        }
        m_head = ((m_head + 1U) % (N+1U));
    }

    void print() {
        auto iter = m_head;
        auto end = m_tail;

        while(iter != end) {
            std::cout << m_array[iter] << ", ";
            iter = ((iter + 1U) % (N+1U));
        }
        std::cout << std::endl;
    }

private:
    std::array<T, N> m_array;
    std::size_t m_head{};
    std::size_t m_tail{}; // points to next empty spot
};

template<typename T, std::size_t N>
void pusher(Queue<T, N> &q) {
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
    for(int i=0; i < 5000; i++) {
        q.push(i);
    }
}
template<typename T, std::size_t N>
void popper(Queue<T, N> &q) {
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
    for(int i=0; i < 5000; i++) {
        q.pop();
    }
}

int main(int argc, char *argv[]) {
    Queue<int, 10000> q{};

    std::thread consumer_1(pusher<int, 10000>, std::ref(q));
    std::thread consumer_2(pusher<int, 10000>, std::ref(q));
    std::thread producer_3(popper<int, 10000>, std::ref(q));
    std::thread producer_4(popper<int, 10000>, std::ref(q));

    consumer_1.join();
    consumer_2.join();
    producer_3.join();
    producer_4.join();
    q.print();
}