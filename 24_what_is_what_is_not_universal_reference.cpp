#include <iostream>

// for a reference to be a universal reference:
// 1. it must have the form: T&& without any const/volatile qualitiers
// 2. Type deduction must not be taking place


template<typename T>
void foo(const T&& arg) {
    // NOTE: arg is a rvalue reference, not a universal reference!
    std::cout << "Arg = " << arg << std::endl;
}

int main() {
    int a = 1;
    // foo(a); // won't compile
    foo(std::move(a));
}