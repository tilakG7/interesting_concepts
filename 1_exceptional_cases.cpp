#include <iostream>
#include <cxxabi.h>
#include <typeinfo>

template<typename T>
void foo(T arg) {
    int status;
    char* demangled_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);

    if (status == 0) {
        std::cout << demangled_name << std::endl;
        free(demangled_name);
    } else {
        std::cerr << "Demangling failed" << std::endl;
    }
}

template<typename T>
void bar(T& arg) {
    int status;
    char* demangled_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);

    if (status == 0) {
        std::cout << demangled_name << std::endl;
        free(demangled_name);
    } else {
        std::cerr << "Demangling failed" << std::endl;
    }
}

void fuzzy(int a, int b) {
    a = b;
    return;
}

int main() {
    foo(fuzzy); // type(T) = void (*)(int, int)
    bar(fuzzy); // type(T) = void (&)(int, int)

    constexpr char my_str[7] = "hello!";
    foo(my_str);
    bar(my_str);
    return 0;
}