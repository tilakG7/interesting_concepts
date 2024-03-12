#include <atomic>
#include <memory>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::atomic<Node*> next;

        Node() : next(nullptr) {}
        Node(T value) : data(std::make_shared<T>(std::move(value))), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue() {
        Node* dummy = new Node(); // Dummy node
        head.store(dummy);
        tail.store(dummy);
    }

    ~LockFreeQueue() {
        while (Node* const old_head = head.load()) {
            head.store(old_head->next.load());
            delete old_head;
        }
    }

    void enqueue(T value) {
        Node* new_node = new Node(std::move(value));
        while (true) {
            Node* t = tail.load();
            Node* next = t->next.load();
            if (t == tail.load()) { // Ensure tail has not been modified
                if (next == nullptr) { // Check if it's the actual tail
                    if (t->next.compare_exchange_weak(next, new_node)) {
                        tail.compare_exchange_weak(t, new_node); // Swing tail to the new node
                        return;
                    }
                } else {
                    tail.compare_exchange_weak(t, next); // Try to swing tail to the next node
                }
            }
        }
    }

    std::shared_ptr<T> dequeue() {
        while (true) {
            Node* h = head.load();
            Node* t = tail.load();
            Node* next = h->next.load();
            if (h == head.load()) { // Ensure head has not been modified
                if (h == t) { // Check if the queue is empty or tail is behind
                    if (next == nullptr) {
                        return std::shared_ptr<T>(); // Queue is empty
                    }
                    tail.compare_exchange_weak(t, next); // Tail is behind, try to advance it
                } else {
                    std::shared_ptr<T> res = next->data; // Retrieve value before freeing
                    if (head.compare_exchange_weak(h, next)) {
                        delete h; // Free old head
                        return res;
                    }
                }
            }
        }
    }

    // goal: consume data from head and return value in node
    // check if data exists
    // if data exists, consume from head
    shared_ptr<T> dequeue() {
        while(true) {
            Node *h = head.load();
            Node *h_next = h->next.load();
            Node *t = tail.load();
            if(h == head.load()) {
                if(h == t) {
                    if(h_next == nullptr) {
                        return shared_ptr<T>();
                    }
                    tail.compare_exchange_weak(t, h_next);
                } else {
                    if(head.compare_exchange_weak(h, h_next)) {
                        std::shared_ptr<T> res = h_next->data;
                        delete h;
                        return res;
                    }
                }
            }

        }
    }
   


};