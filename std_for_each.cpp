#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for_each(v.begin(), v.end(), [](int elem) {
        if(elem % 2) {
            cout << elem << ", ";
        }
    });
}