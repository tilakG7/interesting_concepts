#include <iostream>

// will not compile.
// auto is employing template type deduction, which does not 
// assume {} = initializer list
// auto foo() {
//     return {1, 2, 3, 4};
// }

// will not compile.
// auto is employing template type deduction, which does not 
// assume {} = initializer list
// decltype(auto) bar() {
//     return {1, 2, 3, 4};
// }

int main() {
    auto a{3};
    std::cout << typeid(a).name() << std::endl;

    auto b = {1, 2, 3, 4, 5};
    std::cout << typeid(b).name() << std::endl;

    // std::cout << typeid(foo()).name() << std::endl;

    // std::cout << typeid(bar()).name() << std::endl;
}