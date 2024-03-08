#include <iostream>
#include <memory>
#include <cassert>

using namespace std;
class Resource {
public:
    Resource() {
        cout << "Resource acquired\n" << endl;
    }

    void print() {
        cout << "Printed something" << endl;
    }

    ~Resource() {
        cout << "Resource destroyed\n" << endl;
    }
private:
};

template<typename T>
class TilakSharedPtr {
public:
    TilakSharedPtr(T *ptr) : m_num_ptr(new size_t(1)), m_p(ptr) {}

    TilakSharedPtr(const TilakSharedPtr<T>& p) {
        m_p = p.m_p;
        m_num_ptr = p.m_num_ptr;
        (*m_num_ptr)++;
    }

    TilakSharedPtr(TilakSharedPtr<T> && p) {
        m_p = p.m_p;
        m_num_ptr = p.m_num_ptr;
        (*m_num_ptr)++;
        p.m_p = nullptr;
        p.m_num_ptr = nullptr;
    }

    TilakSharedPtr<T>& operator=(const TilakSharedPtr<T> & p) {
        // if the pointer is already pointing to the same resource, nothing
        // to do
        if(p.m_p == m_p) {
            return *this;
        }
        (*m_num_ptr)--;
        if(*m_num_ptr == 0) {
            cout << "deleting old stuff" << endl;
            delete m_num_ptr;
            delete m_p;
        }
        m_p = p.m_p;
        m_num_ptr = p.m_num_ptr;
        (*m_num_ptr)++;
        return *this;
    }

    TilakSharedPtr& operator=(TilakSharedPtr<T> && p) {
        cout << "Inside move assignment operator" << endl;
        (*m_num_ptr)--;
        if(*m_num_ptr == 0) {
            delete m_num_ptr;
            delete m_p;
        }
        m_num_ptr = p.m_num_ptr;
        m_p = p.m_p;
        p.m_num_ptr = nullptr;
        p.m_p = nullptr;
        return *this;
    }

    T& operator*() {
        return *m_p;
    }

    T* operator->() {
        return m_p;
    }

    T* get() const {
        return *m_num_ptr;
    }

    ~TilakSharedPtr() {
        cout << "TSP destructor called" << endl;
        if(m_p == nullptr || m_num_ptr == nullptr) {
            delete m_p;
            delete m_num_ptr;
            return;
        }

        (*m_num_ptr) = (*m_num_ptr) - 1;
        if(*m_num_ptr == 0) {
            delete m_num_ptr;
            delete m_p;
        }
    }

    void print() {
        cout << "Data: " << m_p << endl;
        cout << "# ptr: " << *m_num_ptr << endl;
    }
private:
    T *m_p;             // pointer to data being managed
    size_t *m_num_ptr;  // pointer to size_t representing number of shared 
                        // pointers pointing to this resource
};

TilakSharedPtr<Resource> getTsp() {
    return TilakSharedPtr<Resource>(new Resource());
}

int main() {
    // TilakSharedPtr<Resource> tsp1(getTsp());
    // TilakSharedPtr<Resource> tsp1(new Resource());
    // {
    //     TilakSharedPtr<Resource> tsp2(tsp1);
    //     {
    //         TilakSharedPtr<Resource> tsp3(tsp2);
    //         cout << "killing 1 shareed pointer" << endl;
    //     }
    //     cout << "killing 2 shared pointer" << endl;
    // }
    // cout << "killing 3 shared pointer" << endl;
    
    TilakSharedPtr p1 = new Resource();
    p1->print();

    return 0;

}