#include <iostream>
#include <optional>

using namespace std;

optional<int> create(bool b) {
    if(b) {
        return 2;
    }
    return {};
}

int main() {
    optional<int> foo = create(true);
    optional<int> bar = create(false);

    if(foo) {
        cout << "Foo contains a value " << *foo << endl;
    } else {
        cout << "Foo does not contain a value" << endl;
    }

    if(bar) {
        cout << "Bar contains a value" << *bar <<  endl;
    } else {
        cout << "Bar does not contain a value" << endl;
    }
}