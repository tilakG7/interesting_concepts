#include <iostream>
#include <vector>

template<typename T>
void printVector(const T& v) {
    std::cout << "Size of vector: " << v.size() << std::endl;
    std::cout << "Capacity of vector: " << v.capacity() << std::endl;
    for(auto e: v) {
        std::cout << e << ", ";
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6}; // creates a vector of 6 elements
    printVector(v);

    // create vector w/ capaicty of 10
    std::vector<int> v2(10);
    printVector(v2);

    // create vector w/ capacity of 10 and initialize all elements to 3
    std::vector<int> v3(10, 3);
    printVector(v3);


    // note: using brace initializers uses initializer list as a parameter to the
    // constructor, thus creates a vector of size 2 (contents: 10, 3)
    std::vector<int> v4{10, 3};
    printVector(v4);

    // when are the size and capacity of a vector different?
    // - when the vector is resized
    v4.resize(20);
    printVector(v4);

    for(int i=0; i < 10; i++) {
        v4.push_back(i);
        printVector(v4);
    }

    std::cout << "\nReseizing vector to 20" << std::endl;
    v4.resize(20);
    printVector(v4);

    std::cout << "Clearing contents of vector v4: " << std::endl;
    v4.clear();
    printVector(v4);

    std::cout << "reserving vector to have 100 elements" << std::endl;
    v4.reserve(100);
    printVector(v4);

    std::cout << "reserving vector to have 20 elements" << std::endl;
    v4.reserve(20);
    printVector(v4);

}