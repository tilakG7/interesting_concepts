#include <iostream>
#include <vector>

template<typename T>
void add1AndPrintRange(T s, T e) {
    for(; s < e; s++) {
        typename std::iterator_traits<T>::value_type v = *s; // annoyingly long
        auto v2 = *s;
        std::cout << (v + 1) << ", ";
        std::cout << (v2 + 1) << ", "; // extremely simple!
    }
    std::cout << std::endl;
}
int main(int argc, char *argv[]) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};


    auto s = v.begin();
    auto e = v.end();

    add1AndPrintRange(s, e);
}