#include <iostream>

template<typename T>
class SharedPtr {
public:
    SharedPtr() : m_ptr(nullptr), m_count(nullptr) {}
    SharedPtr(T *ptr) : m_ptr(ptr), m_count(new size_t(1)){}

    ~SharedPtr() {
        if(!m_ptr || !m_count) {
            return;
        }
        (*m_count)--;
        if((*m_count) == 0) {
            delete m_count;
            delete m_ptr;
        }
    }
private:
    T *m_ptr;
    size_t *m_count;
};

int main() {
    SharedPtr<int> sp;
}