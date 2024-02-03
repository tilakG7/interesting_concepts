/**
* template<typename T>
* void tilak_func(param_type pt);
* 
* tilak_func(expression)
* 
* ------------------------------------------------------------------------------
* Compiler figures out type of T and param_type by looking at expression.
* T is also determined by param_type
* 
* 3 cases for template type deduction:
* 
* 1. param_type is a reference or pointer, but not a universal reference
* 2. param_type is a universal reference
* 3. para_type is neither a pointer, nor a reference
* 
*/

// Discuss CASE 1:
// When param_type is a pointer or reference to T:
// Give T the base type of expression, and add qualifiers as needed to maintain
// correctness.

#include <iostream>
#include <type_traits>


template<typename T>
void foo1(T& arg) {
    if(std::is_const<std::remove_reference_t<T>>::value) {
        std::cout << "const ";
    }
    if(std::is_lvalue_reference<T>::value) {
        std::cout << " lvalue reference ";
    }
    if(std::is_rvalue_reference<T>::value) {
        std::cout << " rvalue reference ";
    }
    std::cout << typeid(T).name() << std::endl;
}

template<typename T>
void foo2(T *arg) {
    if(std::is_const<std::remove_reference_t<T>>::value) {
        std::cout << "const ";
    }
    if(std::is_lvalue_reference<T>::value) {
        std::cout << " lvalue reference ";
    }
    if(std::is_rvalue_reference<T>::value) {
    std::cout << " rvalue reference ";
    }   
    std::cout << typeid(T).name() << std::endl;
}

template<typename T>
void foo3(const T& arg) {
    if(std::is_const<std::remove_reference_t<T>>::value) {
        std::cout << "const ";
    }
    if(std::is_lvalue_reference<T>::value) {
        std::cout << " lvalue reference ";
    }
    if(std::is_rvalue_reference<T>::value) {
        std::cout << " rvalue reference ";
    }
    std::cout << typeid(T).name() << std::endl;
}

template<typename T>
void foo4(const T* const arg) {
    if(std::is_const<std::remove_reference_t<T>>::value) {
        std::cout << "const ";
    }
    if(std::is_lvalue_reference<T>::value) {
        std::cout << "lvalue reference ";
    }
    if(std::is_rvalue_reference<T>::value) {
        std::cout << " rvalue reference ";
    }
    std::cout << typeid(T).name() << std::endl;
}

int main(int argc, char *argv[]) {
    int l_val = 0;
    const int const_l_val = 1;
    int &l_val_ref = l_val;
    const int &const_l_val_ref = const_l_val;

    // void foo1(T& arg) {
    std::cout << "foo1(): " << std::endl;
    // foo1(1); <--- compiler error
    foo1(l_val);               // type(expression) = int         type(T) = int          type(param) = int&
    foo1(const_l_val);         // type(expression) = const int   type(T) = const int    type(param) = const int &
    foo1(l_val_ref);           // type(expression) = int&        type(T) = int          type(param) = int&
    foo1(const_l_val_ref);     // type(expression) = const int&  type(t) = const int    type(param) = const int &
    std::cout << std::endl;

    // void foo3(const T& arg) {
    std::cout << "foo3(): " << std::endl;
    foo3(2);                   // type(expression) = int&&      type(T) = int  type(param) = const int&
    foo3(l_val);               // type(expression) = int        type(T) = int  type(param) = const int&
    foo3(const_l_val);         // type(expression) = const int  type(T) = int  type(param) = const int&
    foo3(l_val_ref);           // type(expression) = int&       type(T) = int  type(param) = const int&
    foo3(const_l_val_ref);     // type(expression) = const int  type(t) = int  type(param) = const int&
    std::cout << std::endl;

    int *int_ptr = &l_val;
    const int *const_int_ptr = &l_val;
    const int *const const_int_const_ptr = &l_val;
    // void foo2(T *arg) {
    std::cout << "foo2(): " << std::endl;
    foo2(int_ptr);             // type(T) = int
    foo2(const_int_ptr);       // type(T) = const int
    foo2(const_int_const_ptr); // type(T) = const int (not const int const because the pointer itself is a copy, so does not need to be const)
    std::cout << std::endl;

    // void foo4(const T* const arg) {
    std::cout << "foo4(): " << std::endl;
    foo4(int_ptr);             // type(T) = int
    foo4(const_int_ptr);       // type(T) = int
    foo4(const_int_const_ptr); // type(T) = int
    std::cout << std::endl;
    return 0;
}