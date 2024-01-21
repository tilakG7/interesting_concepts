/**
 * Simple program showing how template metaprogramming can be used to calculate
 * fibonacci sequence.
 * Sequence is: 0, 1, 1, 2, 3, 5, 8, 13...
 *
 * Base case for the sequence are at 0 and 1, where the sequence is given as:
 * F(0) = 0
 * F(1) = 1
 *
*/
#include <cstdint>
#include <iostream>

// define generic non-type template for calculating fibonacci sequence @ N
template<uint8_t N>
uint8_t fibonacci() {
    return fibonacci<N-1U>() + fibonacci<N-2U>();
}

// base case for fibonacci at N=0
template<>
uint8_t fibonacci<0U>() {
    return 0;
}

// base case for fibonacci at N=1
template<>
uint8_t fibonacci<1U>() {
    return 1;
}


int main(int argc, char *argv[]) {
    // NOTE: since templates are evaluated at compile time, this variable
    // must be a constexpr
    constexpr uint8_t kPos = 10;
    std::cout << "Fibonacci sequence at position " 
              << int(kPos) << " = " <<  fibonacci<kPos>() << std::endl;

}