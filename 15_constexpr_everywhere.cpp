#include <iostream>

using namespace std;

constexpr int giveAConstexprInt(int a) {
    return a;
}


constexpr
double constexpr_pow(double base, double power) {
    double result = 1;
    for(size_t i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}
/**
* Main thing to remember is that using constexpr in functions will make 
* functions return constexpr only if their inputs are compile time constant!
*/
int main() {

    int b = 4;
    constexpr int b_constexpr = 4;
    // constexpr int a = giveAConstexprInt(b); // will not compile
    constexpr int a = giveAConstexprInt(b_constexpr); // will compile
    cout << "A constexpr int: " << a << endl;

    // this might take a while to compie
    constexpr double constexpr_res = constexpr_pow(1.0000001, 100000);
    cout << "Constexpr result = " << constexpr_res << endl;
}