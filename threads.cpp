#include <memory>
#include <atomic>
#include <iostream>

using namespace std;

template<typename T>
class Queue {
public:
    Queue() {
        Node *dummy = new Node();
        head.store(dummy);
        tail.store(dummy);
    }

    bool isEmpty() {
        return head.load() == tail.load();
    }

    void enqueue(const T& val) {
        Node *to_insert = new Node(val);
        while(true) {
            Node *t = tail.load();
            Node *t_after = t->next.load();
            if(t == tail.load()) {
                if(t_after == nullptr) {
                    if(t->next.compare_exchange_weak(t_after, to_insert)) {
                        tail.compare_exchange_weak(t, to_insert);
                        break;
                    }
                } else {
                    // help
                    tail.compare_exchange_weak(t, t_after);
                }
            }
        }
    }

    shared_ptr<T> dequeue() {
        while(true) {
            Node *h = head.load();
            Node *h_next = h->next.load();
            Node *t = tail.load();
            if(h == head.load()) {
                if(h == t) {
                    if(h_next == nullptr) {
                        return nullptr;
                    }
                    tail.compare_exchange_weak(t, h_next);
                } 
                else {
                    shared_ptr<T> data = h_next->val;
                    if(head.compare_exchange_weak(h, h_next)) {
                        delete h;
                        return data;
                    }
                }
            }   
        }
    }

    ~Queue() {
        while(const Node* old_head = head.load()) {
            head.store(old_head->next.load());
            delete old_head;
        }
    }
private:
    struct Node {
        Node() : val(nullptr), next(nullptr){}
        Node(const T& ref) : val(make_shared<T>(ref)), next(nullptr) {}
        shared_ptr<T> val;
        atomic<Node*> next;
    };

    atomic<Node*> head;
    atomic<Node*> tail;
};

int main() {
    Queue<int> q;

    shared_ptr<int> s1 = q.dequeue();
    if(s1) {
        cout << "s1 isnot nullptr: " << *s1 << endl;
    } else {
        cout << "s1 is nullptr" << endl;
    }
    q.enqueue(10);
    q.enqueue(22);
    q.enqueue(33);

    while(shared_ptr<int> s2 = q.dequeue()) {
        if(s2) {
            cout << "s2 isnot nullptr" << *s2.get() << endl;
        } else {
            cout << "s2 is  nullptr: "  << endl;
        }
    }
    

    if(q.isEmpty()) {
        cout << "Queue is empty" << endl;
    }
    else {
        cout << "Queue is not empty" << endl;
    }
}