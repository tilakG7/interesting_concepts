#include <iostream>
#include <boost/type_index.hpp>

auto foo() {
    static int b = 4;
    int &a = b;
    return a;
}

decltype(auto) foo2() {
    static int b = 4;
    int &a = b;
    return a;
}

decltype(auto) bar() {
    static int a = 3;
    return a;
}

decltype(auto) bar2() {
    static int a = 3;
    return (a);
}


int main(int argc, char *argv[]) {
    // as can be seen, the return types of auto and decltype(auto) make a cler 
    // difference
    //
    // auto type deduction in this case falls under case 3 -> to figure out the
    // type, ignore references and const/volatile qualifiers
    // decltype(auto) pretty much keeps the exact same type as value returned 
    // from the return statement
    std::cout << boost::typeindex::type_id_with_cvr<decltype(foo())>().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<decltype(foo2())>().pretty_name() << std::endl;

    // delctype returns the type for names, but for anything other than a simple
    // name, it ensures it returns an l-value reference.
    // this is why bar2 returns a type of int& instead of just int in bar
    std::cout << boost::typeindex::type_id_with_cvr<decltype(bar())>().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<decltype(bar2())>().pretty_name() << std::endl;
}