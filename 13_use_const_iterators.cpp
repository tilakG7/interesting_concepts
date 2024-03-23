#include <iostream>
#include <algorithm>

using namespace std;

// write a function that is able to take any container as an input, and replace
// 1 occurence of a value int the container with a target value

template <typename C, typename T>
bool replace(C &c, const T& find_val, const T& replace_val) {
    auto it = find(cbegin(c), cend(c), find_val);
    if(it != cend(c)) {
        c.insert(it, replace_val);
        return true;
    }
    return false;
}

int main() {
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    if(replace(v, 11, 10)) {
        cout << "Replaced 11 with 10" << endl;
    }
    else {
        cout << "Couldn't replace 11. Not found." << endl;
    }

    std::for_each(v.cbegin(), v.cend(), [](int i) {
        cout << i << ", ";
    });
    cout << endl;

    if(replace(v, 2, 22)) {
        cout << "Replaced 2 with 22" << endl;
    }
    else {
        cout << "Couldn't replace 2. Not found" << endl;
    }

    std::for_each(v.cbegin(), v.cend(), [](int i) {
        cout << i << ", ";
    });
    cout << endl;
}