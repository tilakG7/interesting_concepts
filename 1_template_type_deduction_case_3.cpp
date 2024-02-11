#include <iostream>
#include <boost/type_index.hpp>

template<typename T>
void foo(T *a) {
    std::cout << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

// void foo(T &a); // call w int&, T = int
// void foo(T a); // call w int&, T = int

// void foo(T *a); // call w int*, T = int
// void foo(T a); // call w int*, T = int*

int main() {
    int *ptr = nullptr;
    foo(ptr);
    return 0;
}