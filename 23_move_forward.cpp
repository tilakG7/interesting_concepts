/**
* Notes on std::move and std::forward
* 
* 1. std::move does not MOVE, std::forward does not FORWARD
* 2. std::move and std::forward generate no executable code
* 
* * std::move is an unconditional cast to an r-value type
* * std::forward is a conditional cast
*/

#include <iostream>
#include <type_traits>

template<typename T>
std::remove_reference_t<T>&& tilak_move(T&& arg) {
    return static_cast<std::remove_reference_t<T&&>>(arg);
}

template<typename T>
typename std::remove_reference<T>::type&& tilak_move_c11(T&& arg) {
    return static_cast<typename std::remove_reference<T>::type>(arg);
}



void subprint(int& a) {
    std::cout << "void subprint(int& a){}" << std::endl;
}

void subprint(const int a) {
    std::cout << "void subprint(const int a){}" << std::endl;
}

void subprint(const int& a) {
    std::cout << "void subprint(const int& a){}" << std::endl;
} 

void subprint(int&& a) {
    std::cout << "void subprint(int&& a){}" << std::endl;
}

void subprint(const int&& a) {
    std::cout << "void subprint(const int&& a){}" << std::endl;
}

template<typename T>
void print(T&& arg) {
    subprint(std::forward<T>(arg));
}

int main(int argc, char *argv[]) {

    int a = 2;
    int &aa = a;
    int &&aaa = 3;
 
    std::cout << std::boolalpha;
    std::cout << "tilak_move(aa) is int&&? "
              << std::is_same<int&&, decltype(tilak_move(aa))>::value << '\n';
    std::cout << "tilak_move_c11(aa) is int&&? "
              << std::is_same<int&&, decltype(tilak_move_c11(aa))>::value << '\n';

    std::cout << "tilak_move(aaa) is int&&? "
              << std::is_same<int&&, decltype(tilak_move(aaa))>::value << '\n';
    std::cout << "tilak_move_c11(aaa) is int&&? "
              << std::is_same<int&&, decltype(tilak_move_c11(aaa))>::value << '\n';


    std::cout << "tilak_move(a) is int&&? "
              << std::is_same<int&&, decltype(tilak_move(a))>::value << '\n';
    std::cout << "tilak_move_c11(a) is int&&? "
              << std::is_same<int&&, decltype(tilak_move_c11(a))>::value << '\n';

    print(a);
    print(aa);
    print(std::move(aaa));

    const int b = 2;
    const int &bb = b;
    const int &&bbb = 4;

    print(b);
    print(bb);
    print(std::move(bbb));

    return 0;
}