#include <iostream>
#include <vector>

struct Foo {
    Foo(int i) : m_i{i} {
        std::cout << "Constructed a simpler foo" << std::endl;
    }
    Foo(int i, bool b, float f) :
    m_i{i}, m_b{b}, m_f{f}{
        std::cout << "Constructed a Foo. ";
        std::cout << "i: " << i << ", b: " << b << ", f: " << f;
        std::cout << std::endl;
    }
private:
    int m_i;
    bool m_b;
    float m_f;
};

struct Bar {
    template<typename ...Args>
    void addFoo(Args&& ...args) {
        m_v.emplace_back(std::forward<Args>(args)...);
    }

    template<typename T>
    void addSimpleFoo(T arg) {
        m_v.emplace_back(std::forward<T>(arg));
    }

private:
    std::vector<Foo> m_v;
};

int main(int argc, char *argv[]) {
    Bar b;
    b.addFoo(1, false, 3.f);
    b.addSimpleFoo(1);
}