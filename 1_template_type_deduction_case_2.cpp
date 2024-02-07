#include <iostream>

/**
* Another case of template type deduction is when we are using universal 
* references.
*/

template<typename T>
void foo1(T&& arg) {
    // careful, if T is a reference, std::is_const always return false
    // must remove_reference!
    if(std::is_const<typename std::remove_reference<T>::type>::value) {
        std::cout << "const ";
    }
    if(std::is_lvalue_reference<T>::value) {
        std::cout << "lvalue reference ";
    }
    if(std::is_rvalue_reference<T>::value) {
        std::cout << "rvalue reference ";
    }
    std::cout << typeid(T).name() << std::endl;
}

int main(int argc, char *argv[]) {
    int a = 1;
    int &b = a;
    const int c = 2;
    const int &d = c;
    int &&e = 2;
    const int &&f = 3;

    // void foo1(T&& arg) {
    foo1(a); // type(T) = int&
    foo1(b); // type(T) = int&
    foo1(c); // type(T) = const int&
    foo1(d); // type(T) = const int&
    foo1(std::move(e)); // type(T) = int&&
    foo1(std::move(f)); // type(T) = const int&&


}