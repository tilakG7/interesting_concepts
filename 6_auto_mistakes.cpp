#include <iostream>

std::vector<bool> getVector(size_t capacity) {
    std::vector<bool> my_vec(capacity, true);
    return my_vec;
}

void printMyBool(bool b) {
    std::cout << "My bool = " << b << std::endl;
}


int main(int argc, char *argv[]) {
    bool foo = getVector(10)[1];
    printMyBool(foo);

    // Note: std::vector<bool> operator[] returns a type of std::vector<bool>::reference
    // this reference contains a pointer to a word + offset
    // since the vector is a temporary object, it destructs while bar is still
    // in scope. Thus, bar is left with a dangling reference. 
    // Results in undefined behaviour.
    auto bar = getVector(11)[4];
    printMyBool(bar);

    // better way to do this is to use
    // the explicitly typed initializer idiom
    auto foobar = static_cast<bool>(getVector(11)[4]);
    printMyBool(foobar);

    return 0;
}