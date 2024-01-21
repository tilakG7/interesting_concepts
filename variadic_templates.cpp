/**
* Write a function which prints any number of arguments
*/
#include <iostream>

template<typename T>
void print(T arg) {
    std::cout << arg <<  std::endl;
    return;
}

// NOTE: Args... is a template parameter pack - meaning it holds a variable
// number of arguments (including none)
template<typename T, typename ...Args>
void print(T first, Args... args) {
    std::cout << first;
    print(args...);
}

template<typename T>
T sum(T val) {
    return val;
}

template<typename T, typename ...Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}


template<int N>
int factorial() {
    return N*factorial<N-1>();
}

template<>
int factorial<0>() {
    return 1;
}

void printReverse() {
    return;
}

template<typename T, typename ...Args>
void printReverse(T first, Args ...args) {
    printReverse(args...);
    std::cout << first << " ";
}



int main(int argc, char *argv[]) {
    print("THIS ", 1, " IS ", 54.5, " quite ", 'c', 'o', 'o', 'l', '.');
    std::cout << "\nSum = " << sum(0, 1, 2, 3, 4, 5, 6, 7, 8) << std::endl;
    std::cout << "Factorial for 10 = " << factorial<10>() << std::endl;
    printReverse("1", 2, "3", 4.0, 5);

    return 0;
}